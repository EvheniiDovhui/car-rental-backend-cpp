#include "routes/car_routes.h"

// Тут реалізація
void registerCarRoutes(crow::App<crow::CORSHandler> &app, CarController &controller)
{
    // 1. Отримання ВСІХ авто (передаємо req для фільтрів)
    CROW_ROUTE(app, "/api/cars")
    ([&controller](const crow::request &req)
     { return controller.getCars(req); });

    // 2. ОТРИМАННЯ ОДНОГО АВТО (потрібно для бронювання)
    CROW_ROUTE(app, "/api/cars/<int>")
    ([&controller](int id)
     { return controller.getCar(id); });
}