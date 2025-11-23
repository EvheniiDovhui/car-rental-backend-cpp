#pragma once
#include <vector>
#include "Car.h"

using namespace std;

class CarRepository {
private:
    vector<Car> cars;

public:
    void addCar(const Car& car);
    Car findById(int& id);
    bool updateCar(const Car& updateCar);
    bool removeCar(int& id);
    vector<Car> getAllCars() const;
};
