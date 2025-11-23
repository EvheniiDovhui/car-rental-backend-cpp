#pragma once
#include <vector>
#include "models/Car.h"
#include "repositories/CarRepository.h"

class CarService {
private:
    CarRepository& repo;

public:
    CarService(CarRepository& repository);
    std::vector<Car> getAllCars();
    void addCar(const Car& car);
};
