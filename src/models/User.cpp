#include "models/User.h"

User::User(int id, const string &name, const string &email, const string &password, vector<int> favorites)
    : id(id), name(name), email(email), password(password), favorites(favorites) {}

crow::json::wvalue User::toJSON() const
{
    crow::json::wvalue json;
    json["id"] = id;
    json["name"] = name;
    json["email"] = email;
    json["password"] = password;

    crow::json::wvalue favList;
    for (size_t i = 0; i < favorites.size(); ++i)
    {
        favList[i] = favorites[i];
    }
    json["favorites"] = move(favList);

    return json;
}

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