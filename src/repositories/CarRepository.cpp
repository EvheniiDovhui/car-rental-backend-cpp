#include "repositories/CarRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

const std::vector<Car>& CarRepository::getAllCars() const {
    return cars;
}

using namespace std;

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

Car CarRepository::findById(int& id){

    for(auto car : cars){
        if(car.getId() == id) return car;
    }

    return;
}

bool CarRepository::removeCar(int& id){
    for(size_t i = 0; i < cars.size(); i++){
        if(cars[i].getId() == id){
            cars.erase(cars.begin() + i);
            return true;
        }
    }
    
    return false;
}