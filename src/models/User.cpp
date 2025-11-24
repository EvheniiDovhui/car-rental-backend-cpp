#include "models/User.h"

// Оновлений конструктор
User::User(int id, const string &name, const string &email, const string &password, vector<int> favorites)
    : id(id), name(name), email(email), password(password), favorites(favorites) {}

crow::json::wvalue User::toJSON() const
{
    crow::json::wvalue json;
    json["id"] = id;
    json["name"] = name;
    json["email"] = email;
    json["password"] = password;

    // 🔥 Зберігаємо масив favorites
    crow::json::wvalue favList;
    for (size_t i = 0; i < favorites.size(); ++i)
    {
        favList[i] = favorites[i];
    }
    json["favorites"] = std::move(favList);

    return json;
}

// Додай цей метод (або онови логіку в UserRepository::load)
void User::fromJSON(const crow::json::rvalue &json)
{
    try
    {
        if (json.has("favorites"))
        {
            favorites.clear();
            for (const auto &item : json["favorites"])
            {
                favorites.push_back(item.i());
            }
        }
    }
    catch (...)
    {
    }
}