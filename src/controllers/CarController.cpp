#include "controllers/CarController.h"
#include "services/CarService.h"
#include "models/Car.h"

using namespace std;

CarController::CarController(CarService &service) : service(service) {}

crow::response CarController::getCars(const crow::request &req)
{
    const char *brandParam = req.url_params.get("brand");
    const char *priceParam = req.url_params.get("maxPrice");

    string brand = brandParam ? brandParam : "";
    double maxPrice = priceParam ? stod(priceParam) : 0.0;

    auto cars = service.getCars(brand, maxPrice);

    crow::json::wvalue json;
    for (size_t i = 0; i < cars.size(); i++)
    {
        json[i] = cars[i].toJSON();
    }

    return crow::response(json);
}

crow::response CarController::getCar(int id)
{
    try
    {
        Car car = service.getCarById(id);
        return crow::response(car.toJSON());
    }
    catch (...)
    {
        return crow::response(404, "Car not found");
    }
}