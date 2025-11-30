#pragma once
#include "../models/Reservation.h"
#include <vector>
#include <string>

using namespace std;

class ReservationRepository
{
    vector<Reservation> reservations;
    int nextId = 1;
    const string DB_FILE = "data/reservations.json";

public:
    ReservationRepository();

    void add(const Reservation &res);
    vector<Reservation> getAll();
    void save();
    void load();

    bool isCarAvailable(int carId, const string &start, const string &end);
};