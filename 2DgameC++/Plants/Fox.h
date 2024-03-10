#pragma once
#include "../Animal.h"

#define FOX_ICON 'F'
#define FOX_STRENGTH 3
#define FOX_INITIATIVE 7

using namespace std;

class Fox : public Animal{

public:
    Fox(World& world, const Position& position, const int& strength)
        :Animal(world, strength, FOX_INITIATIVE, position, FOX_ICON)
    {}

    string getName() {
        return ("Fox");
    }

    Organism* clone(const Position& position) {
        return new Fox(this->world, position, FOX_STRENGTH);
    }

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Fox*>(org) != nullptr;
    }

    bool collision(Organism* organism) {
        if (organism->getStrength() > this->getStrength()) return false;//strong smell
        return Animal::collision(organism);
    }

    ~Fox() {};
};
