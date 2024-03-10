#pragma once
#include "../Animal.h"

#define WOLF_ICON 'W'
#define WOLF_STRENGTH 9
#define WOLF_INITIATIVE 5

using namespace std;

class Wolf : public Animal{
public:
    Wolf(World& world, const Position& position, const int& strength)
        : Animal(world, strength, WOLF_INITIATIVE, position, WOLF_ICON)
    {}

    string getName() {
        return ("Wolf");
    }

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Wolf*>(org) != nullptr;
    }

    Organism* clone(const Position& position) {
        return new Wolf(this->world, position, WOLF_STRENGTH);
    }

    ~Wolf(){};
};

