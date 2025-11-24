#include "services/UserService.h"
#include <optional>

bool UserService::registerUser(const std::string &name, const std::string &email, const std::string &password)
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

std::optional<User> UserService::findUserByCredentials(const std::string &email, const std::string &password)
{
    const auto &users = repository.getAllUsers();

    for (const auto &user : users)
    {
        if (user.getEmail() == email && user.getPasswordHash() == password)
        {
            return user;
        }
    }

    return std::nullopt;
}

std::optional<User> UserService::updateUser(int id, const std::string &name, const std::string &email, const std::string &password)
{
    auto &users = repository.getAllUsersRef(); // 🔥 важливо: посилання!

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

    return std::nullopt;
}

std::vector<int> UserService::toggleFavorite(int userId, int carId)
{
    auto &users = repository.getAllUsersRef(); // Беремо посилання на вектор юзерів

    for (auto &user : users)
    {
        if (user.getId() == userId)
        {
            std::vector<int> favs = user.getFavorites();

            // Перевіряємо, чи є вже це авто в списку
            auto it = std::find(favs.begin(), favs.end(), carId);

            if (it != favs.end())
            {
                // ВЖЕ Є -> ВИДАЛЯЄМО
                favs.erase(it);
            }
            else
            {
                // НЕМАЄ -> ДОДАЄМО
                favs.push_back(carId);
            }

            user.setFavorites(favs); // Оновлюємо юзера
            repository.save();       // Зберігаємо у файл
            return favs;
        }
    }
    throw std::runtime_error("User not found");
}