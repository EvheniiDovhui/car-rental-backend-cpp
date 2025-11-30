#include "repositories/CarRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

const vector<Car> &CarRepository::getAllCars() const
{
    return cars;
}

using namespace std;

void CarRepository::addCar(const Car &car)
{
    cars.push_back(car);
}

void CarRepository::save()
{
    ofstream file("data/cars.json");
    file << "[\n";
    for (size_t i = 0; i < cars.size(); i++)
    {
        auto json = cars[i].toJSON();
        file << json.dump();
        if (i + 1 < cars.size())
            file << ",";
    }
    file << "\n]";
}

void CarRepository::load()
{
    ifstream file("data/cars.json");

    if (!file.is_open())
    {
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    if (content.empty())
        return;

    auto json = crow::json::load(content);

    if (!json || json.t() != crow::json::type::List)
    {
        cerr << "Error: Invalid JSON format in cars.json" << endl;
        return;
    }

    cars.clear();

    for (const auto &item : json)
    {
        Car car;
        car.fromJSON(item);
        cars.push_back(car);
    }
}

Car CarRepository::findById(int &id)
{

    for (auto car : cars)
    {
        if (car.getId() == id)
            return car;
    }
    return Car();
}

bool CarRepository::removeCar(int &id)
{
    for (size_t i = 0; i < cars.size(); i++)
    {
        if (cars[i].getId() == id)
        {
            cars.erase(cars.begin() + i);
            return true;
        }
    }
    return false;
}