#pragma once
#include "crow.h"
#include "services/UserService.h"

template <typename App>
void initAuthRoutes(App& app, UserService& service) {

    // --- LOGIN ---
    CROW_ROUTE(app, "/api/login").methods("POST"_method)
    ([&service](const crow::request& req){
        auto data = crow::json::load(req.body);
        if(!data)
            return crow::json::wvalue({ {"status", "error"}, {"error", "Invalid JSON"} });

        std::string email = data["email"].s();
        std::string password = data["password"].s();

        auto userOpt = service.findUserByCredentials(email, password);

        if (!userOpt.has_value())
            return crow::json::wvalue({ {"status", "error"}, {"error", "Wrong credentials"} });

        auto user = userOpt.value();

        return crow::json::wvalue({
            {"status", "success"},
            {"token", "dummyToken123"},
            {"user", {
                {"id", user.getId()},
                {"name", user.getName()},
                {"email", user.getEmail()}
            }}
        });
    });

    // --- REGISTER ---
    CROW_ROUTE(app, "/api/register").methods("POST"_method)
    ([&service](const crow::request& req){
        auto data = crow::json::load(req.body);
        if(!data)
            return crow::json::wvalue({ {"status", "error"}, {"error", "Invalid JSON"} });

        std::string name = data["name"].s();
        std::string email = data["email"].s();
        std::string password = data["password"].s();

        bool ok = service.registerUser(name, email, password);

        if(!ok)
            return crow::json::wvalue({ {"status", "error"}, {"error", "User already exists"} });

        return crow::json::wvalue({
            {"status", "success"},
            {"message", "User registered"}
        });
    });

    // --- UPDATE PROFILE ---
CROW_ROUTE(app, "/api/profile").methods("PUT"_method)
([&service](const crow::request& req){
    auto data = crow::json::load(req.body);
    if (!data)
        return crow::json::wvalue({{"status", "error"}, {"error", "Invalid JSON"}});

    int id = data["id"].i(); // 🔥 тимчасово так, потім через токен

    std::string name = data["name"].s();
    std::string email = data["email"].s();
    std::string password = data["password"].s();

    auto userOpt = service.updateUser(id, name, email, password);

    if (!userOpt.has_value())
        return crow::json::wvalue({{"status", "error"}, {"error", "Update failed"}});

    auto user = userOpt.value();

    return crow::json::wvalue({
        {"status", "success"},
        {"user", {
            {"id", user.getId()},
            {"name", user.getName()},
            {"email", user.getEmail()}
        }}
    });
});

}
