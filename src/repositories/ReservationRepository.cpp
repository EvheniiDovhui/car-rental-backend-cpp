#include "repositories/ReservationRepository.h"
#include <fstream>
#include <iostream>
#include <algorithm>

ReservationRepository::ReservationRepository()
{
    load();
}

void ReservationRepository::add(const Reservation &res)
{
    Reservation newRes = res;
    if (reservations.empty())
    {
        newRes.id = 1;
        nextId = 2;
    }   
    else
    {
        newRes.id = reservations.back().id + 1;
        nextId = newRes.id + 1;
    }
    reservations.push_back(newRes);
    save();
}

vector<Reservation> ReservationRepository::getAll()
{
    return reservations;
}

vector<Reservation> ReservationRepository::getByUserId(int userId)
{
    vector<Reservation> result;
    for (const auto &r : reservations)
    {
        if (r.userId == userId)
        {
            result.push_back(r);
        }
    }
    return result;
}

void ReservationRepository::save()
{
    ofstream file(DB_FILE);
    if (!file.is_open())
        return;

    crow::json::wvalue jsonArray;
    for (size_t i = 0; i < reservations.size(); ++i)
    {
        jsonArray[i] = reservations[i].toJSON();
    }
    file << jsonArray.dump();
}

void ReservationRepository::load()
{
    ifstream file(DB_FILE);
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

    reservations.clear();
    for (const auto &item : json)
    {
        Reservation res;
        res.id = item["id"].i();
        res.userId = item["userId"].i();
        res.carId = item["carId"].i();
        res.startDate = item["startDate"].s();
        res.endDate = item["endDate"].s();

        if (item.has("totalPrice"))
        {
            if (item["totalPrice"].t() == crow::json::type::Number)
                res.totalPrice = item["totalPrice"].d();
            else if (item["totalPrice"].t() == crow::json::type::Number)
                res.totalPrice = (double)item["totalPrice"].i();
        }

        reservations.push_back(res);
    }

    if (!reservations.empty())
    {
        nextId = reservations.back().id + 1;
    }
}

bool ReservationRepository::isCarAvailable(int carId, const string &newStart, const string &newEnd)
{
    for (const auto &r : reservations)
    {
        if (r.carId == carId)
        {
            if (r.startDate <= newEnd && newStart <= r.endDate)
            {
                return false;
            }
        }
    }
    return true;
}