#pragma once
#include <string>
#include <vector>
#include <crow/json.h>

using namespace std;

class User
{
    int id;
    string name;
    string email;
    string password;
    vector<int> favorites;

public:
    User(int id, const string &name, const string &email, const string &password, vector<int> favorites = {});

    int getId() const { return id; }
    const string &getName() const { return name; }
    const string &getEmail() const { return email; }
    const string &getPasswordHash() const { return password; }

    const vector<int> &getFavorites() const { return favorites; }

    void setName(const string &newName) { name = newName; }
    void setEmail(const string &newEmail) { email = newEmail; }
    void setPassword(const string &newPass) { password = newPass; }

    void setFavorites(const vector<int> &newFavs) { favorites = newFavs; }

    crow::json::wvalue toJSON() const;

    void fromJSON(const crow::json::rvalue &json);
};