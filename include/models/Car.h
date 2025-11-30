#pragma once
#include <string>
#include <crow.h>

using namespace std;

class Car
{
    int id;
    string brand;
    string model;
    int year;
    double pricePerDay;
    string transmission;
    string fuel;
    string engine;
    string description;
    string image;

public:
    Car();

    int getId() const;
    string getBrand() const;
    string getModel() const;
    int getYear() const;
    double getPricePerDay() const;

    string getTransmission() const;
    string getFuel() const;
    string getEngine() const;
    string getDescription() const;
    string getImage() const;

    crow::json::wvalue toJSON() const;
    void fromJSON(const crow::json::rvalue &json);
};