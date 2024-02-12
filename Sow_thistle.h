#pragma once
#include "../Plant.h"

#define SOW_THISTLE_SOWING_TRIES 3
#define SOW_THISTLE_ICON '&'
#define SOW_THISTLE_STRENGTH 0
#define SOW_THISTLE_SOW_POSILIBITY 20

using namespace std;

class Sow_thistle : public Plant {
public:
    Sow_thistle(World& world, const Position& position, const int& strength)
        : Plant(world, position, SOW_THISTLE_ICON, SOW_THISTLE_STRENGTH, SOW_THISTLE_SOW_POSILIBITY)
    {
        sowing = SOW_THISTLE_SOWING_TRIES;
    }

    Organism* clone(const Position& position) {
        return new Sow_thistle(this->world, position, SOW_THISTLE_STRENGTH);
    }

    string getName() {
        return ("Sow Thistle");
    }

    ~Sow_thistle() {};
};
