#include "services/CarService.h"
#include "repositories/CarRepository.h"
#include <stdexcept>
#include <algorithm>
#include <string>

using namespace std;

CarService::CarService(CarRepository &repository)
    : repo(repository) {}

vector<Car> CarService::getAllCars()
{
    return repo.getAllCars();
}

void CarService::addCar(const Car &car)
{
    repo.addCar(car);
    repo.save();
}

Car CarService::getCarById(int id)
{
    vector<Car> cars = repo.getAllCars();

    for (const auto &car : cars)
    {
        if (car.getId() == id)
        {
            return car;
        }
    }

    throw runtime_error("Car not found");
}

vector<Car> CarService::getCars(const string &brand, double maxPrice)
{
    vector<Car> allCars = repo.getAllCars();

    if (brand.empty() && maxPrice <= 0)
    {
        return allCars;
    }

    vector<Car> filteredCars;
    string targetBrand = brand;

    transform(targetBrand.begin(), targetBrand.end(), targetBrand.begin(), ::tolower);

    for (const auto &car : allCars)
    {
        bool matchBrand = true;
        bool matchPrice = true;

        if (!brand.empty())
        {
            string carBrand = car.getBrand();
            transform(carBrand.begin(), carBrand.end(), carBrand.begin(), ::tolower);
            if (carBrand.find(targetBrand) == string::npos)
            {
                matchBrand = false;
            }
        }

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