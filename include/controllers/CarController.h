#pragma once
#include "crow.h"
#include "services/CarService.h"

class CarController
{
    CarService &service;

public:
    CarController(CarService &service);
    crow::response getCars(const crow::request &req);
    crow::response getCar(int id);
};