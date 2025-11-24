#include "controllers/CarController.h"
#include "services/CarService.h"
#include "models/Car.h"

CarController::CarController(CarService &service)
    : service(service) {}

// Отримання списку (з фільтрацією)
crow::response CarController::getCars(const crow::request &req)
{
    // Зчитуємо параметри з URL (?brand=BMW&maxPrice=100)
    const char *brandParam = req.url_params.get("brand");
    const char *priceParam = req.url_params.get("maxPrice");

    std::string brand = brandParam ? brandParam : "";
    double maxPrice = priceParam ? std::stod(priceParam) : 0.0;

    // Викликаємо сервіс (який ми оновили раніше)
    auto cars = service.getCars(brand, maxPrice);

    crow::json::wvalue json;
    for (size_t i = 0; i < cars.size(); i++)
    {
        json[i] = cars[i].toJSON(); // Використовуємо метод моделі
    }

    return crow::response(json);
}

// Отримання одного авто (для сторінки бронювання)
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