#include "Car.h"

Car::Car(int id, std::string brand, std::string model, int year, double pricePerDay)
    : id(id), brand(brand), model(model), year(year), pricePerDay(pricePerDay) {}

int Car::getId() const { return id; }
std::string Car::getBrand() const { return brand; }
std::string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
double Car::getPricePerDay() const { return pricePerDay; }

void Car::setId(const int& id) { this->id = id; }
void Car::setBrand(const std::string& brand) { this->brand = brand; }
void Car::setModel(const std::string& model) { this->model = model; }
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

    if (json.has("id")) this->id = json["id"].i();
    if (json.has("brand")) this->brand = json["brand"].s();
    if (json.has("model")) this->model = json["model"].s();
    if (json.has("year")) this->year = json["year"].i();
    if (json.has("pricePerDay")) this->pricePerDay = json["pricePerDay"].d();
}