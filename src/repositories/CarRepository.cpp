#include "repositories/CarRepository.h"

void CarRepository::addCar(const Car& car) {
    cars.push_back(car);
}

std::vector<Car> CarRepository::getAllCars() const {
    return cars;
}
