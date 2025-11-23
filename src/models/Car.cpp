#include "Car.h"
#include <string>

using namespace std;

Car::Car(int id, string brand, string model, int year, double pricePerDay)
    : id(id), brand(brand), model(model), year(year), pricePerDay(pricePerDay) {}

int Car::getId() const { return id; }
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
double Car::getPricePerDay() const { return pricePerDay; }

void Car::setId(const int& id) { this->id = id; }
void Car::setBrand(const string& brand) { this->brand = brand; }
void Car::setModel(const string& model) { this->model = model; }
void Car::setYear(const int& year) { this->year = year; }
void Car::setPricePerDay(const double& pricePerDay) { this->pricePerDay = pricePerDay; }


crow::json::wvalue Car::toJSON() const{
    crow::json::wvalue json;
    json["id"] = this->id;
    json["brand"] = this->brand;
    json["model"] = this->model;
    json["year"] = this->year;
    json["pricePerDay"] = this->pricePerDay;
    return json;
}

void Car::fromJSON(const crow::json::rvalue& json) {

    try {
        this->id = json["id"].i();
        this->brand = json["brand"].s();
        this->model = json["model"].s();
        this->year = json["year"].i();
        this->pricePerDay = json["pricePerDay"].d();
    } catch (const exception& e) {}
}