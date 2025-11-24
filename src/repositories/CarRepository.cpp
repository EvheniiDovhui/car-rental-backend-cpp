#include "repositories/CarRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

const std::vector<Car> &CarRepository::getAllCars() const
{
    return cars;
}

using namespace std;

void CarRepository::addCar(const Car &car)
{
    cars.push_back(car);
}

// поки зберігаємо простий json, як у UserRepository
void CarRepository::save()
{
    std::ofstream file("data/cars.json");
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
    std::ifstream file("data/cars.json");

    // Якщо файлу немає (перший запуск), просто виходимо
    if (!file.is_open())
    {
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Якщо файл порожній
    if (content.empty())
        return;

    // Парсимо JSON за допомогою Crow
    auto json = crow::json::load(content);

    // Перевіряємо, чи це валідний JSON і чи це список (масив)
    if (!json || json.t() != crow::json::type::List)
    {
        std::cerr << "Error: Invalid JSON format in cars.json" << std::endl;
        return;
    }

    cars.clear(); // Очищаємо поточний список перед завантаженням

    for (const auto &item : json)
    {
        Car car;
        // Передбачається, що у класі Car є метод fromJSON
        // Якщо його немає, треба реалізувати або заповнювати поля вручну:
        // car.setId(item["id"].i());
        // car.setBrand(item["brand"].s()); ...
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