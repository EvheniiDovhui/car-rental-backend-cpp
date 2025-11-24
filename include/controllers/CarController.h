#pragma once
#include "crow.h"
#include "services/CarService.h"

class CarController
{
private:
    CarService &service;

public:
    CarController(CarService &service);

    // Оновлено: приймає запит (для фільтрів)
    crow::response getCars(const crow::request &req);

    // Додано: отримання одного авто по ID
    crow::response getCar(int id);
};