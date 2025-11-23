#include "repositories/UserRepository.h"
#include <fstream>
#include <crow/json.h>

using namespace crow;

UserRepository::UserRepository() {}

// --- ADD USER ---
void UserRepository::addUser(const User& user) {
    users.push_back(user);
}

// --- GET ALL USERS ---
const std::vector<User>& UserRepository::getAllUsers() const {
    return users;
}

// --- GENERATE NEXT ID ---
int UserRepository::getNextId() {
    return users.size() + 1;
}

std::vector<User>& UserRepository::getAllUsersRef() {
    return users;
}


// --- SAVE TO JSON ---
void UserRepository::save() {
    std::ofstream file("data/users.json");
    file << "[\n";
    for (size_t i = 0; i < users.size(); i++) {
        auto json = users[i].toJSON();
        file << json.dump();
        if (i + 1 < users.size()) file << ",";
    }
    file << "\n]";
}

// --- LOAD FROM JSON ---
void UserRepository::load() {
    std::ifstream file("data/users.json");
    if (!file.is_open()) return;

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    auto arr = json::load(content);
    if (!arr) return;

    users.clear();
    for (size_t i = 0; i < arr.size(); i++) {
        auto u = arr[i];
        users.emplace_back(
            u["id"].i(),
            u["name"].s(),
            u["email"].s(),
            u["password"].s()
        );
    }
}
