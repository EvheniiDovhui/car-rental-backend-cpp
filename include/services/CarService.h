#pragma once
#include <vector>
#include <string>
#include "models/Car.h"
#include "repositories/CarRepository.h"

using namespace std;

class CarService
{
    CarRepository &repo;

public:
    CarService(CarRepository &repository);

    // Базові методи
    vector<Car> getAllCars();
    void addCar(const Car &car);

    // --- ДОДАНО ЦІ ДВА МЕТОДИ ---
    Car getCarById(int id);
    vector<Car> getCars(const string &brand = "", double maxPrice = 0.0);
};