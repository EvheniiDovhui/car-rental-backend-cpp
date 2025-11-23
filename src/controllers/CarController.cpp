#include "controllers/CarController.h"

CarController::CarController(CarService& service)
    : service(service) {}

crow::response CarController::getCars() {
    auto cars = service.getAllCars();
    crow::json::wvalue json;

    for (size_t i = 0; i < cars.size(); i++) {
        json[i]["id"] = cars[i].getId();
        json[i]["brand"] = cars[i].getBrand();
        json[i]["model"] = cars[i].getModel();
        json[i]["year"] = cars[i].getYear();
        json[i]["pricePerDay"] = cars[i].getPricePerDay();
    }

    return json; // Crow сам підготує response
}
