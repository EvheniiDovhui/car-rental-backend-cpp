#pragma once
#include <vector>
#include "models/Car.h"

using namespace std;

class CarRepository
{
    vector<Car> cars;

public:
    const vector<Car> &getAllCars() const;
    void addCar(const Car &car);

    void save();
    void load();
    Car findById(int &id);
    bool removeCar(int &id);
};
