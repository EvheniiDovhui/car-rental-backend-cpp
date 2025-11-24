#pragma once
#include "../models/Reservation.h"
#include <vector>
#include <string>

class ReservationRepository
{
    std::vector<Reservation> reservations;
    int nextId = 1;
    const std::string DB_FILE = "data/reservations.json";

public:
    ReservationRepository(); // Конструктор для завантаження даних

    void add(const Reservation &res);
    std::vector<Reservation> getAll();
    void save();
    void load();

    // 🔥 НОВИЙ МЕТОД
    bool isCarAvailable(int carId, const std::string &start, const std::string &end);
};