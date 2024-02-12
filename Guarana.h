#pragma once
#include "../Plant.h"

#define GUARANA_ICON 'G'
#define GUARANA_STRENGTH 0
#define GUARANA_SOW_POSILIBITY 20

using namespace std;

class Guarana : public Plant {
public:
    Guarana(World& world, const Position& position, const int& strength)
        : Plant(world, position, GUARANA_ICON, GUARANA_STRENGTH, GUARANA_SOW_POSILIBITY)
    {
        nutrient = true;
    }

    Organism* clone(const Position& position) {
        return new Guarana(this->world, position, GUARANA_STRENGTH);
    }

    string getName() {
        return "Guarana";
    }

    ~Guarana() {};
};
