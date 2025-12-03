#pragma once
#include <string>
#include <optional>
#include "repositories/UserRepository.h"
#include "repositories/ReservationRepository.h"
#include "models/User.h"
#include <vector>

using namespace std;

class UserService
{
    UserRepository &repository;
    ReservationRepository &reservationRepository;

public:
    UserService(UserRepository &repo, ReservationRepository &resRepo)
        : repository(repo), reservationRepository(resRepo) {}

    bool registerUser(const string &name, const string &email, const string &password);
    bool loginUser(const string &email, const string &password);

    optional<User> findUserByCredentials(const string &email, const string &password);
    optional<User> updateUser(int id, const string &name, const string &email, const string &password);
    vector<int> toggleFavorite(int userId, int carId);

    vector<Reservation> getUserReservations(int userId);
};
