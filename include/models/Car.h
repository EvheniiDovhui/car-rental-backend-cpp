#pragma once
#include <string>
#include <crow.h>

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

    void setId(const int&);
    void setBrand(const std::string&);
    void setModel(const std::string&);
    void setYear(const int&);
    void setPricePerDay(const double&);

    crow::json::wvalue toJSON() const;
    void fromJSON(const crow::json::rvalue& json);
};
