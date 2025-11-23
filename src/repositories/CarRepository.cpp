#include "repositories/CarRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

const std::vector<Car>& CarRepository::getAllCars() const {
    return cars;
}

void CarRepository::addCar(const Car& car) {
    cars.push_back(car);
}

// поки зберігаємо простий json, як у UserRepository
void CarRepository::save() {
    std::ofstream file("data/cars.json");
    file << "[\n";
    for (size_t i = 0; i < cars.size(); i++) {
        auto json = cars[i].toJSON();
        file << json.dump();
        if (i + 1 < cars.size()) file << ",";
    }
    file << "\n]";
}
