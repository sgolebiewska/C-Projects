#pragma once
#include "../Animal.h"

#define SHEEP_ICON 'S'
#define SHEEP_STRENGTH 4
#define SHEEP_INITIATIVE 4

using namespace std;

class Sheep : public Animal{
public:
    Sheep(World& world, const Position& position, const int& strength)
        : Animal(world, strength, SHEEP_INITIATIVE, position, SHEEP_ICON)
    {}

    string getName() {
        return ("Sheep");
    }

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Sheep*>(org) != nullptr;
    }

    Organism* clone(const Position& position) {
        return new Sheep(this->world, position, SHEEP_STRENGTH);
    }

    ~Sheep() {};
};
