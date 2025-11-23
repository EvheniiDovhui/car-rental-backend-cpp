#pragma once
#include "crow.h"
#include "services/CarService.h"

class CarController {
private:
    CarService& service;

public:
    CarController(CarService& service);
    crow::response getCars();
};
