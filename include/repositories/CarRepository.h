#pragma once
#include <vector>
#include "models/Car.h"

class CarRepository {
private:
    std::vector<Car> cars;

public:
    const std::vector<Car>& getAllCars() const;
    void addCar(const Car& car);

    void save();  // ⬅ додай
    void load();  // необов’язково, але логічно
};
