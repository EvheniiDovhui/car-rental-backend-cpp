#pragma once
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "controllers/CarController.h"

void registerCarRoutes(crow::App<crow::CORSHandler> &app, CarController &controller);