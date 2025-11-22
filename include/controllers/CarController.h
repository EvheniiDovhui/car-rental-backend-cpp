#pragma once
#include "services/CarService.h"
#include "crow.h"

class CarController {
private:
    CarService& service;

public:
    CarController(CarService& service);
    crow::response getCars();
};
