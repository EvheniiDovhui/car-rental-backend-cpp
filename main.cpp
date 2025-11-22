#include "crow.h"

#include "services/CarService.h"
#include "controllers/CarController.h"
#include "routes/car_routes.h"


int main() {
    crow::SimpleApp app;

    CarService service;
    CarController controller(service);

    registerCarRoutes(app, controller);

    app.port(8080).multithreaded().run();
}
