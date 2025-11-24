#pragma once
#include <string>
#include <optional>
#include "repositories/UserRepository.h"
#include "models/User.h"
#include <vector>

class UserService
{
private:
    UserRepository &repository;

public:
    UserService(UserRepository &repo) : repository(repo) {}

    bool registerUser(const std::string &name, const std::string &email, const std::string &password);
    bool loginUser(const std::string &email, const std::string &password);

    std::optional<User> findUserByCredentials(const std::string &email, const std::string &password);
    std::optional<User> updateUser(int id, const std::string &name, const std::string &email, const std::string &password);
    std::vector<int> toggleFavorite(int userId, int carId);
};
