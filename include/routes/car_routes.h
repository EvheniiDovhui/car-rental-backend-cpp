#pragma once
#include "crow.h"
#include "controllers/CarController.h"

template <typename App>
void registerCarRoutes(App& app, CarController& controller) {

    // GET /api/cars — отримати всі авто
    CROW_ROUTE(app, "/api/cars").methods("GET"_method)
    ([&controller]() {
        return controller.getCars();
    });

    // ДОДАМО ПІЗНІШЕ:
    // POST /api/cars — додати авто
    // PUT /api/cars/<id> — редагувати
    // DELETE /api/cars/<id> — видалити
}
