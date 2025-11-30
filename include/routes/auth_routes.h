#pragma once
#include "crow.h"
#include "services/UserService.h"

using namespace std;

template <typename App>
void initAuthRoutes(App &app, UserService &service)
{
    CROW_ROUTE(app, "/api/login").methods("POST"_method)([&service](const crow::request &req)
                                                         {
        auto data = crow::json::load(req.body);
        if(!data)
            return crow::json::wvalue({ {"status", "error"}, {"error", "Invalid JSON"} });

        string email = data["email"].s();
        string password = data["password"].s();

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
        }); });

    CROW_ROUTE(app, "/api/register").methods("POST"_method)([&service](const crow::request &req)
                                                            {
        auto data = crow::json::load(req.body);
        if(!data)
            return crow::json::wvalue({ {"status", "error"}, {"error", "Invalid JSON"} });

        string name = data["name"].s();
        string email = data["email"].s();
        string password = data["password"].s();

        bool ok = service.registerUser(name, email, password);

        if(!ok)
            return crow::json::wvalue({ {"status", "error"}, {"error", "User already exists"} });

        return crow::json::wvalue({
            {"status", "success"},
            {"message", "User registered"}
        }); });

    CROW_ROUTE(app, "/api/profile").methods("PUT"_method)([&service](const crow::request &req)
                                                          {
    auto data = crow::json::load(req.body);
    if (!data)
        return crow::json::wvalue({{"status", "error"}, {"error", "Invalid JSON"}});

    int id = data["id"].i();

    string name = data["name"].s();
    string email = data["email"].s();
    string password = data["password"].s();

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
    }); });
}
