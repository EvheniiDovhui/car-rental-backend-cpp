#pragma once
#include <vector>
#include "Car.h"

class CarRepository {
private:
    std::vector<Car> cars;

public:
    void addCar(const Car& car);
    std::vector<Car> getAllCars() const;
};
