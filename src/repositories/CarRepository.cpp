#include "repositories/CarRepository.h"

using namespace std;

void CarRepository::addCar(const Car& car) {
    cars.push_back(car);
}

vector<Car> CarRepository::getAllCars() const {
    return cars;
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

bool CarRepository::updateCar(const Car& updateCar){
    for (auto& car : cars) {
        if (car.getId() == updateCar.getId()) {
            car = updateCar; 
            return true;    
        }
    }
    return false;
}