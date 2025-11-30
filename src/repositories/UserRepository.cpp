#include "repositories/UserRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

UserRepository::UserRepository() {}

void UserRepository::addUser(const User &user)
{
    users.push_back(user);
}

const vector<User> &UserRepository::getAllUsers() const
{
    return users;
}

int UserRepository::getNextId()
{
    return users.size() + 1;
}

vector<User> &UserRepository::getAllUsersRef()
{
    return users;
}

void UserRepository::save()
{
    ofstream file("data/users.json");
    file << "[\n";
    for (size_t i = 0; i < users.size(); i++)
    {
        auto json = users[i].toJSON();
        file << json.dump();
        if (i + 1 < users.size())
            file << ",";
    }
    file << "\n]";
}

void UserRepository::load()
{
    ifstream file("data/users.json");
    if (!file.is_open())
        return;

    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());

    auto arr = json::load(content);
    if (!arr)
        return;

    users.clear();
    for (size_t i = 0; i < arr.size(); i++)
    {
        auto u = arr[i];
        users.emplace_back(
            u["id"].i(),
            u["name"].s(),
            u["email"].s(),
            u["password"].s());
    }
}
