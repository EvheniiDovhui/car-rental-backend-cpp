#pragma once
#include <string>
#include <optional>
#include "repositories/UserRepository.h"
#include "models/User.h"
#include <vector>

using namespace std;

class UserService
{
    UserRepository &repository;

public:
    UserService(UserRepository &repo) : repository(repo) {}

    bool registerUser(const string &name, const string &email, const string &password);
    bool loginUser(const string &email, const string &password);

    optional<User> findUserByCredentials(const string &email, const string &password);
    optional<User> updateUser(int id, const string &name, const string &email, const string &password);
    vector<int> toggleFavorite(int userId, int carId);
};
