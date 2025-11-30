#pragma once
#include <string>
#include <crow.h>

using namespace std;

struct Reservation
{
    int id;
    int userId;
    int carId;
    string startDate;
    string endDate;
    double totalPrice;

    crow::json::wvalue toJSON() const
    {
        crow::json::wvalue json;
        json["id"] = id;
        json["userId"] = userId;
        json["carId"] = carId;
        json["startDate"] = startDate;
        json["endDate"] = endDate;
        json["totalPrice"] = totalPrice;
        return json;
    }
};