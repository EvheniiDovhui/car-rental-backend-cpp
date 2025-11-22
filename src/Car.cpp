#include "Car.h"

Car::Car(int id, std::string brand, std::string model, int year, double pricePerDay)
    : id(id), brand(brand), model(model), year(year), pricePerDay(pricePerDay) {}

int Car::getId() const { return id; }
std::string Car::getBrand() const { return brand; }
std::string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
double Car::getPricePerDay() const { return pricePerDay; }
