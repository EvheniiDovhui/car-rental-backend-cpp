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

