#pragma once
#include "repositories/CarRepository.h"

class CarService {
private:
    CarRepository repo;

public:
    CarService();
    std::vector<Car> getAllCars();
};
