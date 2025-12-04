#pragma once
#include "OptionalAddon.h"

class GenericOptionalAddon : public OptionalAddon {
public:
    GenericOptionalAddon()
        : OptionalAddon(0, "", 0.0) {}

    GenericOptionalAddon(unsigned int id, const std::string &name, double pricePerDay)
        : OptionalAddon(id, name, pricePerDay) {}

    crow::json::wvalue getInfo() const override
    {
        crow::json::wvalue info;
        info["type"] = "GenericAddon";
        info["id"] = id;
        info["name"] = name;
        info["pricePerDay"] = price;
        return info;
    }
};
