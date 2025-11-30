#include "models/Car.h"

Car::Car() : id(0), year(0), pricePerDay(0.0) {}

int Car::getId() const { return id; }
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
double Car::getPricePerDay() const { return pricePerDay; }

string Car::getTransmission() const { return transmission; }
string Car::getFuel() const { return fuel; }
string Car::getEngine() const { return engine; }
string Car::getDescription() const { return description; }
string Car::getImage() const { return image; }

crow::json::wvalue Car::toJSON() const
{
    crow::json::wvalue json;
    json["id"] = id;
    json["brand"] = brand;
    json["model"] = model;
    json["year"] = year;
    json["pricePerDay"] = pricePerDay;

    json["transmission"] = transmission;
    json["fuel"] = fuel;
    json["engine"] = engine;
    json["description"] = description;
    json["image"] = image;

    return json;
}

void Car::fromJSON(const crow::json::rvalue &json)
{
    try
    {
        id = json["id"].i();
        brand = json["brand"].s();
        model = json["model"].s();
        year = json["year"].i();
        pricePerDay = json["pricePerDay"].d();

        if (json.has("transmission"))
            transmission = json["transmission"].s();
        if (json.has("fuel"))
            fuel = json["fuel"].s();
        if (json.has("engine"))
            engine = json["engine"].s();
        if (json.has("description"))
            description = json["description"].s();
        if (json.has("image"))
            image = json["image"].s();
    }
    catch (...)
    {
    }
}