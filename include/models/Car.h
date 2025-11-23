#pragma once
#include <string>
#include <crow.h>

using namespace std;

class Car {
private:
    int id;
    string brand;
    string model;
    int year;
    double pricePerDay;

public:
    Car(int id, string brand, string model, int year, double pricePerDay);

    int getId() const;
    string getBrand() const;
    string getModel() const;
    int getYear() const;
    double getPricePerDay() const;

    void setId(const int&);
    void setBrand(const string&);
    void setModel(const string&);
    void setYear(const int&);
    void setPricePerDay(const double&);

    crow::json::wvalue toJSON() const;
    void fromJSON(const crow::json::rvalue& json);
};
