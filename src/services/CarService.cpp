#include "services/CarService.h"

CarService::CarService(CarRepository& repository)
    : repo(repository) {}

std::vector<Car> CarService::getAllCars() {
    return repo.getAllCars();
}

void CarService::addCar(const Car& car) {
    repo.addCar(car);
    repo.save();
}
