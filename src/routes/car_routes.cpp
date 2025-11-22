#include "routes/car_routes.h"

void registerCarRoutes(crow::SimpleApp& app, CarController& controller) {
    CROW_ROUTE(app, "/api/cars")([&controller]() {
        return controller.getCars();
    });

    CROW_ROUTE(app, "/api/cars").methods("OPTIONS"_method)([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        return res;
    });
}
