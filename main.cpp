#include "crow.h"
#include "crow/middlewares/cors.h"
#include "routes/auth_routes.h"
#include "routes/car_routes.h"
#include "services/UserService.h"
#include "repositories/UserRepository.h"
#include "services/CarService.h"
#include "repositories/CarRepository.h"
#include "controllers/CarController.h"
#include "models/Reservation.h"
#include "repositories/ReservationRepository.h"
#include "repositories/OptionalRepository.h"
#include "models/GenericOptionalAddon.h"
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

int main()
{
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .origin("http://localhost:5173")
        .allow_credentials()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .max_age(3600);

    UserRepository userRepository;
    userRepository.load();

    ReservationRepository reservationRepo;

    UserService userService(userRepository, reservationRepo);
    initAuthRoutes(app, userService);

    CarRepository carRepo;
    carRepo.load();
    CarService carService(carRepo);
    CarController carController(carService);
    registerCarRoutes(app, carController);
    OptionalRepository optionalRepo;
    optionalRepo.load("data/reservation_addons.json");

    CROW_ROUTE(app, "/api/addons").methods("GET"_method)([]() {
        std::ifstream file("data/addons.json");
        if (!file.is_open())
        {
            return crow::response(500, "addons.json not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        auto json = crow::json::load(content);
        if (!json || json.t() != crow::json::type::List)
        {
            return crow::response(500, "Invalid addons.json format");
        }

        crow::json::wvalue res;
        res = json;
        return crow::response(200, res);
    });

    CROW_ROUTE(app, "/api/reserve").methods("POST"_method)([&](const crow::request &req)
                                                           {
        auto json = crow::json::load(req.body);
        if (!json) return crow::response(400, "Invalid JSON");

        if (!json.has("userId") || !json.has("carId") || 
            !json.has("startDate") || !json.has("endDate") || !json.has("totalPrice")) {
            return crow::response(400, "Missing required fields");
        }
        try {
            int userId = json["userId"].i();
            int carId = json["carId"].i();
            string start = json["startDate"].s();
            string end = json["endDate"].s();
            double price = 0.0;
            
            if (json["totalPrice"].t() == crow::json::type::Number)
                price = json["totalPrice"].d();
            else
                price = (double)json["totalPrice"].i();

            if (!reservationRepo.isCarAvailable(carId, start, end)) {
                crow::json::wvalue err;
                err["status"] = "error";
                err["error"] = "Авто вже заброньовано на обрані дати!";
                return crow::response(409, err);
            }

            // Calculate number of days for the reservation using proper date parsing
            std::tm startTm = {};
            std::tm endTm = {};
            std::istringstream startStream(start);
            std::istringstream endStream(end);
            
            startStream >> std::get_time(&startTm, "%Y-%m-%d");
            endStream >> std::get_time(&endTm, "%Y-%m-%d");
            
            // Convert to time_point for accurate day calculation
            auto startTime = std::chrono::system_clock::from_time_t(std::mktime(&startTm));
            auto endTime = std::chrono::system_clock::from_time_t(std::mktime(&endTm));
            
            // Calculate days difference
            auto duration = std::chrono::duration_cast<std::chrono::hours>(endTime - startTime);
            int days = duration.count() / 24;
            if (days < 1) days = 1; // At least 1 day
            
            // Start with base price from request
            double totalPrice = price;
            
            // Calculate addon costs if provided
            if (json.has("addons") && json["addons"].t() == crow::json::type::List)
            {
                for (const auto &a : json["addons"])
                {
                    if (!a.has("name") || !a.has("pricePerDay"))
                        continue;

                    double addonPrice = 0.0;
                    if (a["pricePerDay"].t() == crow::json::type::Number)
                        addonPrice = a["pricePerDay"].d();
                    else
                        addonPrice = (double)a["pricePerDay"].i();

                    // Add addon price * days to total
                    totalPrice += addonPrice * days;
                }
            }

            Reservation newRes;
            newRes.userId = userId;
            newRes.carId = carId;
            newRes.startDate = start;
            newRes.endDate = end;
            newRes.totalPrice = totalPrice;

            int createdId = reservationRepo.add(newRes);

            // Save addons if they were provided
            if (json.has("addons") && json["addons"].t() == crow::json::type::List && createdId > 0)
            {
                for (const auto &a : json["addons"])
                {
                    if (!a.has("name") || !a.has("pricePerDay"))
                        continue;

                    string addonName = a["name"].s();
                    double addonPrice = 0.0;
                    if (a["pricePerDay"].t() == crow::json::type::Number)
                        addonPrice = a["pricePerDay"].d();
                    else
                        addonPrice = (double)a["pricePerDay"].i();

                    GenericOptionalAddon *addon = new GenericOptionalAddon(0, addonName, addonPrice);
                    optionalRepo.addOptionalAddon((unsigned int)createdId, addon);
                }

                optionalRepo.save("data/reservation_addons.json");
            }
            
            // Update newRes with the created ID for response
            newRes.id = createdId;

            crow::json::wvalue res;
            res["status"] = "success";
            res["reservation"] = newRes.toJSON();

            return crow::response(200, res);

        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            return crow::response(400, "Invalid data");
        } });

    CROW_ROUTE(app, "/api/favorites").methods("POST"_method)([&userService](const crow::request &req)
                                                             {
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        int userId = x["userId"].i();
        int carId = x["carId"].i();

        try {
            auto newFavs = userService.toggleFavorite(userId, carId);
            
            crow::json::wvalue res;
            res["status"] = "success";
            
            crow::json::wvalue favArr;
            for(size_t i=0; i<newFavs.size(); ++i) favArr[i] = newFavs[i];
            res["favorites"] = move(favArr);

            return crow::response(200, res);
        } catch (...) {
            return crow::response(400, "Error updating favorites");
        } });

    app.port(8080).multithreaded().run();
}
