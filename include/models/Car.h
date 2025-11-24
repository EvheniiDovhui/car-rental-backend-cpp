#pragma once
#include <string>
#include <crow.h>

using namespace std;

class Car
{
private:
    int id;
    string brand;
    string model;
    int year;
    double pricePerDay;

    // 🔥 НОВІ ПОЛЯ
    string transmission;
    string fuel;
    string engine;
    string description;
    string image;

public:
    Car();
    // Можна розширити конструктор, але не обов'язково, якщо є сеттери

    // Геттери
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

    // JSON методи
    crow::json::wvalue toJSON() const;
    void fromJSON(const crow::json::rvalue &json);
};