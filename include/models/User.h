#pragma once
#include <string>
#include <vector> // Не забудь
#include <crow/json.h>

using std::string;
using std::vector;

class User
{
private:
    int id;
    string name;
    string email;
    string password;
    vector<int> favorites; // 🔥 Нове поле

public:
    // Оновлений конструктор
    User(int id, const string &name, const string &email, const string &password, vector<int> favorites = {});

    // --- GETTERS ---
    int getId() const { return id; }
    const string &getName() const { return name; }
    const string &getEmail() const { return email; }
    const string &getPasswordHash() const { return password; }

    // 🔥 Геттер для улюблених
    const vector<int> &getFavorites() const { return favorites; }

    // --- SETTERS ---
    void setName(const string &newName) { name = newName; }
    void setEmail(const string &newEmail) { email = newEmail; }
    void setPassword(const string &newPass) { password = newPass; }

    // 🔥 Сеттер для улюблених
    void setFavorites(const vector<int> &newFavs) { favorites = newFavs; }

    // --- JSON ---
    crow::json::wvalue toJSON() const;

    // 🔥 Додай цей метод, щоб полегшити читання в UserRepository
    void fromJSON(const crow::json::rvalue &json);
};