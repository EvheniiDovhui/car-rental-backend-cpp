#include "services/CarService.h"
#include "repositories/CarRepository.h"
#include <stdexcept>
#include <algorithm>
#include <string>

CarService::CarService(CarRepository &repository)
    : repo(repository) {}

std::vector<Car> CarService::getAllCars()
{
    return repo.getAllCars();
}

void CarService::addCar(const Car &car)
{
    repo.addCar(car);
    repo.save();
}

// --- РЕАЛІЗАЦІЯ НОВИХ МЕТОДІВ ---

// 1. Отримання авто по ID (для бронювання)
Car CarService::getCarById(int id)
{
    // Беремо всі машини з репозиторія
    std::vector<Car> cars = repo.getAllCars();

    // Шукаємо потрібну
    for (const auto &car : cars)
    {
        if (car.getId() == id)
        {
            return car;
        }
    }

    // Якщо не знайшли - кидаємо помилку (Controller перехопить її і поверне 404)
    throw std::runtime_error("Car not found");
}

// 2. Фільтрація (для пошуку)
std::vector<Car> CarService::getCars(const std::string &brand, double maxPrice)
{
    std::vector<Car> allCars = repo.getAllCars();

    // Якщо фільтри пусті — повертаємо все
    if (brand.empty() && maxPrice <= 0)
    {
        return allCars;
    }

    std::vector<Car> filteredCars;
    std::string targetBrand = brand;

    // Переводимо шуканий бренд в нижній регістр для зручності
    std::transform(targetBrand.begin(), targetBrand.end(), targetBrand.begin(), ::tolower);

    for (const auto &car : allCars)
    {
        bool matchBrand = true;
        bool matchPrice = true;

        // Перевірка бренду
        if (!brand.empty())
        {
            std::string carBrand = car.getBrand();
            std::transform(carBrand.begin(), carBrand.end(), carBrand.begin(), ::tolower);
            // Шукаємо підрядок (наприклад "bmw" знайде "BMW X5")
            if (carBrand.find(targetBrand) == std::string::npos)
            {
                matchBrand = false;
            }
        }

        // Перевірка ціни
        if (maxPrice > 0)
        {
            if (car.getPricePerDay() > maxPrice)
            {
                matchPrice = false;
            }
        }

        if (matchBrand && matchPrice)
        {
            filteredCars.push_back(car);
        }
    }

    return filteredCars;
}