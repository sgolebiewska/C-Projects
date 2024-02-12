#pragma once
#include "../Animal.h"

#define ANTELOPE_ICON 'A'
#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4

#define ANTELOPE_ESCAPE_CHANCE 50
#define ANTELOPE_STEPS 2

using namespace std;

class Antelope : public Animal{
public:
    Antelope(World& world, const Position& position, const int& strength)
        : Animal(world, strength, ANTELOPE_INITIATIVE, position, ANTELOPE_ICON)
    {
        escapeChance = ANTELOPE_ESCAPE_CHANCE;
        steps = ANTELOPE_STEPS;
    }

    string getName() {
        return ("Antelope");
    }

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Antelope*>(org) != nullptr;
    }

    Organism* clone(const Position& position) {
        return new Antelope(this->world, position, ANTELOPE_STRENGTH);
    }

    ~Antelope() {};
};
