#pragma once
#include "crow.h"
#include "crow/middlewares/cors.h" // Потрібно для типу CORSHandler
#include "controllers/CarController.h"

// Тільки оголошення функції! Ніяких templates і реалізації тут.
void registerCarRoutes(crow::App<crow::CORSHandler> &app, CarController &controller);