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

    UserService userService(userRepository);
    initAuthRoutes(app, userService);

    CarRepository carRepo;
    carRepo.load();
    CarService carService(carRepo);
    CarController carController(carService);
    registerCarRoutes(app, carController);

    ReservationRepository reservationRepo;

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

            Reservation newRes;
            newRes.userId = userId;
            newRes.carId = carId;
            newRes.startDate = start;
            newRes.endDate = end;
            newRes.totalPrice = price;

            reservationRepo.add(newRes);

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
