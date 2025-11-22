#pragma once
#include <string>

class Car {
private:
    int id;
    std::string brand;
    std::string model;
    int year;
    double pricePerDay;

public:
    Car(int id, std::string brand, std::string model, int year, double pricePerDay);

    int getId() const;
    std::string getBrand() const;
    std::string getModel() const;
    int getYear() const;
    double getPricePerDay() const;
};
