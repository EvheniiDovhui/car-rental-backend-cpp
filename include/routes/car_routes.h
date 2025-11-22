#pragma once
#include "crow.h"
#include "controllers/CarController.h"

void registerCarRoutes(crow::SimpleApp& app, CarController& controller);
