#pragma once
#include "../Plant.h"

#define BELLADONNA_ICON 'B'
#define BELLADONNA_STRENGTH 99
#define BELLADONA_SOW_POSIBILITY 20

using namespace std;

class Belladonna : public Plant {
public:
    
    Belladonna(World& world, const Position& position, const int& strength)
        : Plant(world, position, BELLADONNA_ICON, BELLADONNA_STRENGTH, BELLADONA_SOW_POSIBILITY)
    {
        toxic = true;
    }

    string getName() {
        return ("Belladonna");
    }

    Organism* clone(const Position& position) {
        return new Belladonna(this->world, position, BELLADONNA_STRENGTH);
    }

    ~Belladonna() {};
};
