#pragma once
#include "../Plant.h"

#define GRASS_ICON '#'
#define GRASS_STRENGTH 0
#define GRASS_SOWING_PROPABILITY 20

using namespace std;

class Grass : public Plant {
public:
    Grass(World& world, const Position& position, const int& strength): Plant(world, position, GRASS_ICON, GRASS_STRENGTH, GRASS_SOWING_PROPABILITY)
    {}

    string getName() {
        return ("Grass");
    }

    Organism* clone (const Position& position) {
        return new Grass(this->world, position, GRASS_STRENGTH);
    }

    ~Grass() {};
};

