#include "models/User.h"

User::User(int id, const string& name, const string& email, const string& password)
    : id(id), name(name), email(email), password(password) {}

crow::json::wvalue User::toJSON() const {
    crow::json::wvalue json;
    json["id"] = id;
    json["name"] = name;
    json["email"] = email;
    return json;
}
