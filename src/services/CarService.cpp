#include "services/CarService.h"

CarService::CarService() {
    repo.addCar(Car(1, "Toyota", "Camry", 2020, 45.0));
    repo.addCar(Car(2, "BMW", "X5", 2019, 80.0));
    repo.addCar(Car(3, "Honda", "Civic", 2021, 40.0));
}

std::vector<Car> CarService::getAllCars() {
    return repo.getAllCars();
}
