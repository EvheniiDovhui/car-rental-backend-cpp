#include "repositories/ReservationRepository.h"
#include <fstream>
#include <iostream>
#include <algorithm> // для std::max і std::min якщо потрібно

ReservationRepository::ReservationRepository()
{
    load(); // Завантажуємо дані одразу при створенні
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

std::vector<Reservation> ReservationRepository::getAll()
{
    return reservations;
}

void ReservationRepository::save()
{
    std::ofstream file(DB_FILE);
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
    std::ifstream file(DB_FILE);
    if (!file.is_open())
        return;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

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

        // Обробка totalPrice (може бути int або double)
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

// 🔥 РЕАЛІЗАЦІЯ ПЕРЕВІРКИ
bool ReservationRepository::isCarAvailable(int carId, const std::string &newStart, const std::string &newEnd)
{
    for (const auto &r : reservations)
    {
        // Перевіряємо тільки бронювання тієї ж машини
        if (r.carId == carId)
        {
            // Логіка перетину:
            // (StartA <= EndB) && (StartB <= EndA)
            if (r.startDate <= newEnd && newStart <= r.endDate)
            {
                return false; // Є перетин, машина зайнята
            }
        }
    }
    return true; // Перетинів не знайдено, вільно
}