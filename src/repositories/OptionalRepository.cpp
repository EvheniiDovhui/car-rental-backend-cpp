#include "repositories/OptionalRepository.h"
#include "models/GenericOptionalAddon.h"
#include <crow/json.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
        throw runtime_error("Failed to open file for saving: " + filePath);

    file << arr.dump();
}

void OptionalRepository::load(const string &filePath)
{
    // Clean up existing addons before clearing the map
    for (auto &pair : optionalAddons) {
        delete pair.second;
    }
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

        // Create a concrete GenericOptionalAddon instance from loaded data
        OptionalAddon *addon = new GenericOptionalAddon(0, name, price);
        optionalAddons.emplace(reservationId, addon);
    }
}
