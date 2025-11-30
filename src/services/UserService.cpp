#include "services/UserService.h"
#include <optional>

using namespace std;

bool UserService::registerUser(const string &name, const string &email, const string &password)
{
    const auto &users = repository.getAllUsers();
    for (const auto &user : users)
    {
        if (user.getEmail() == email)
        {
            return false;
        }
    }

    User newUser(repository.getNextId(), name, email, password);

    repository.addUser(newUser);
    repository.save();

    return true;
}

optional<User> UserService::findUserByCredentials(const string &email, const string &password)
{
    const auto &users = repository.getAllUsers();

    for (const auto &user : users)
    {
        if (user.getEmail() == email && user.getPasswordHash() == password)
        {
            return user;
        }
    }

    return nullopt;
}

optional<User> UserService::updateUser(int id, const string &name, const string &email, const string &password)
{
    auto &users = repository.getAllUsersRef();

    for (auto &user : users)
    {
        if (user.getId() == id)
        {
            user.setName(name);
            user.setEmail(email);

            if (!password.empty())
                user.setPassword(password);

            repository.save();
            return user;
        }
    }

    return nullopt;
}

vector<int> UserService::toggleFavorite(int userId, int carId)
{
    auto &users = repository.getAllUsersRef();

    for (auto &user : users)
    {
        if (user.getId() == userId)
        {
            vector<int> favs = user.getFavorites();
            auto it = find(favs.begin(), favs.end(), carId);

            if (it != favs.end())
            {
                favs.erase(it);
            }
            else
            {
                favs.push_back(carId);
            }

            user.setFavorites(favs);
            repository.save();
            return favs;
        }
    }
    throw runtime_error("User not found");
}