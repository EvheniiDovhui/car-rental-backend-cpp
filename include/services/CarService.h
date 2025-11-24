#pragma once
#include <vector>
#include <string>
#include "models/Car.h"
#include "repositories/CarRepository.h"

class CarService
{
private:
    CarRepository &repo;

public:
    CarService(CarRepository &repository);

    // Базові методи
    std::vector<Car> getAllCars();
    void addCar(const Car &car);

    // --- ДОДАНО ЦІ ДВА МЕТОДИ ---
    Car getCarById(int id);
    std::vector<Car> getCars(const std::string &brand = "", double maxPrice = 0.0);
};