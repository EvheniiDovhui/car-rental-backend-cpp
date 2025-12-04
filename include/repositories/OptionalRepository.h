#pragma once
#include "models/OptionalAddon.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class OptionalRepository {
    multimap<unsigned int, OptionalAddon*> optionalAddons;

public:
    OptionalRepository() = default;
    
    ~OptionalRepository() {
        // Clean up all allocated addons
        for (auto &pair : optionalAddons) {
            delete pair.second;
        }
        optionalAddons.clear();
    }

    void addOptionalAddon(unsigned int reservationId, OptionalAddon *addon)
    {
        optionalAddons.emplace(reservationId, addon);
    }

    vector<OptionalAddon *> getAddonsForReservation(unsigned int reservationId) const
    {
        vector<OptionalAddon *> result;
        auto range = optionalAddons.equal_range(reservationId);
        for (auto it = range.first; it != range.second; ++it)
        {
            result.push_back(it->second);
        }
        return result;
    }

    void save(const string &filePath) const;
    void load(const string &filePath);
};