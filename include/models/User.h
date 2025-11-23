#pragma once
#include <string>
#include <crow/json.h>
using std::string;

class User {
private:
    int id;
    string name;
    string email;
    string password; // hashed

public:
    User(int id, const string& name, const string& email, const string& password);

    // --- GETTERS ---
    int getId() const { return id; }
    const string& getName() const { return name; }
    const string& getEmail() const { return email; }
    const string& getPasswordHash() const { return password; }

    // --- SETTERS (потрібні для редагування профілю) ---
    void setName(const string& newName) { name = newName; }
    void setEmail(const string& newEmail) { email = newEmail; }
    void setPassword(const string& newPass) { password = newPass; }

    // --- JSON ---
    crow::json::wvalue toJSON() const;
};
