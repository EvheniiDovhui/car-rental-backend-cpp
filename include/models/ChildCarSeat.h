#pragma once
#include "OptionalAddon.h"

class ChildCarSeat : public OptionalAddon {
    bool isIsofix;
    bool isRearFacing;

public:
    ChildCarSeat()
        : OptionalAddon(0, "Дитяче крісло", 5.0),
          isIsofix(false),
          isRearFacing(false) {}

    ChildCarSeat(unsigned int id,
                 double pricePerDay,
                 bool isIsofix,
                 bool isRearFacing)
        : OptionalAddon(id, "Дитяче крісло", pricePerDay),
          isIsofix(isIsofix),
          isRearFacing(isRearFacing) {}

    crow::json::wvalue getInfo() const override
    {
      crow::json::wvalue info;
      info["type"] = "ChildCarSeat";
      info["id"] = id;
      info["name"] = name;
      info["pricePerDay"] = price;
      info["isIsofix"] = isIsofix;
      info["isRearFacing"] = isRearFacing;
      return info;
    }
};