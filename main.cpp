#include "crow.h"
#include "crow/middlewares/cors.h"
#include "routes/auth_routes.h"
#include "services/UserService.h"
#include "repositories/UserRepository.h"

int main() {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .origin("http://localhost:5173")
        .allow_credentials()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .max_age(3600);

    // 🔥 ОДИН раз створюємо репозиторій
    UserRepository userRepository;
    userRepository.load(); // якщо load() існує

    UserService userService(userRepository);
    initAuthRoutes(app, userService);

    // Обробка preflight
    CROW_ROUTE(app, "/api/<path>").methods("OPTIONS"_method)
    ([](const crow::request&, crow::response& res, std::string){
        res.code = 200;
        res.add_header("Access-Control-Allow-Origin", "http://localhost:5173");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.end();
    });

    app.port(8080).multithreaded().run();
}
