#pragma once
#include <vector>
#include <string>
#include "models/User.h"

using namespace std;

class UserRepository
{
    vector<User> users;

public:
    UserRepository();

    void load();
    void save();

    void addUser(const User &user);
    const vector<User> &getAllUsers() const;
    int getNextId();

    vector<User> &getAllUsersRef();
};
