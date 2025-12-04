#pragma once
#include "OptionalAddon.h"

class Navigator : public OptionalAddon {
public:
    Navigator()
        : OptionalAddon(0, "Навігатор", 3.0) {}

    Navigator(unsigned int id, double pricePerDay)
        : OptionalAddon(id, "Навігатор", pricePerDay) {}

    crow::json::wvalue getInfo() const override
    {
        crow::json::wvalue info;
        info["type"] = "Navigator";
        info["id"] = id;
        info["name"] = name;
        info["pricePerDay"] = price;
        return info;
    }
};