#pragma once
#include <vector>
#include <string>
#include "models/User.h"

class UserRepository {
public:
    UserRepository();

    void load();
    void save();

    void addUser(const User& user);
    const std::vector<User>& getAllUsers() const;
    int getNextId();

    // 🔥 перенесено в public
    std::vector<User>& getAllUsersRef();

private:
    std::vector<User> users;
};
