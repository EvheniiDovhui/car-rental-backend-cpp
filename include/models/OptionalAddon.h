#pragma once
#include <string>
#include <crow/json.h>

class OptionalAddon {
protected:
    unsigned int id;
    std::string name;
    
    double price;

public:
    OptionalAddon() = default;
    OptionalAddon(unsigned int id, const std::string &name, double pricePerDay)
        : id(id), name(name), price(pricePerDay) {}

    virtual ~OptionalAddon() = default;

    unsigned int getId() const { return id; }
    const std::string &getName() const { return name; }
    double getPricePerDay() const { return price; }

    virtual crow::json::wvalue getInfo() const = 0;
};