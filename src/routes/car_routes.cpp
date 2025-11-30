#include "routes/car_routes.h"
#include "crow/middlewares/cors.h"

void registerCarRoutes(crow::App<crow::CORSHandler> &app, CarController &controller)
{
    CROW_ROUTE(app, "/api/cars")
    ([&controller](const crow::request &req)
     { return controller.getCars(req); });

    CROW_ROUTE(app, "/api/cars/<int>")
    ([&controller](int id)
     { return controller.getCar(id); });
}