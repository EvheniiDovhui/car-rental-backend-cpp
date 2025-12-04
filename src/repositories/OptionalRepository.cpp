#include "repositories/OptionalRepository.h"
#include <crow/json.h>
#include <fstream>
#include <sstream>

using namespace std;

void OptionalRepository::save(const string &filePath) const
{
    crow::json::wvalue arr;

    size_t i = 0;
    for (const auto &entry : optionalAddons)
    {
        unsigned int reservationId = entry.first;
        OptionalAddon *addon = entry.second;
        if (!addon)
            continue;

        crow::json::wvalue item;
        item["reservationId"] = reservationId;
        item["name"] = addon->getName();
        item["price"] = addon->getPricePerDay();

        arr[i++] = std::move(item);
    }

    ofstream file(filePath);
    if (!file.is_open())
        return;

    file << arr.dump();
}

void OptionalRepository::load(const string &filePath)
{
    optionalAddons.clear();

    ifstream file(filePath);
    if (!file.is_open())
        return;

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    if (content.empty())
        return;

    auto json = crow::json::load(content);
    if (!json || json.t() != crow::json::type::List)
        return;

    for (const auto &item : json)
    {
        unsigned int reservationId = item["reservationId"].i();
        string name = item["name"].s();
        double price = 0.0;

        if (item["price"].t() == crow::json::type::Number)
            price = item["price"].d();
        else
            price = (double)item["price"].i();

        // OptionalAddon is abstract; do not instantiate it directly.
        // Replace nullptr with an instance of a concrete subclass when available.
        OptionalAddon *addon = nullptr;
        optionalAddons.emplace(reservationId, addon);
    }
}
