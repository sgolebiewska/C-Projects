#pragma once
#include<iostream>
#include "Organism.h"

#define NORMAL_SOWING_PROBABILITY 10 
#define PLANT_INITIATIVE 0
#define PLANT_STRENGTH 0
#define UNREACHABLE -1

class Plant : public Organism {
private:
    double sowingProbability;
protected:
    int sowing = 1;

    double getSowingProbability() const {
        return sowingProbability;
    }

    void sow(const Position& position) {
        this->world.addRandomOrganism(position, this->clone(position));
        world.Narrator().Sowing(this, this->clone(position));
    }

public:
    Plant(World& world, Position position, const char& icon, const int& strength, double sowing_probability)
        :Organism(world, strength, PLANT_INITIATIVE, position, icon), sowingProbability(sowing_probability)
    {}

    int getSowing() const {
        return sowing;
    }

    void action() {
        if (!isAlive()) return;
        for (int i = 0; i < getSowing(); i++) {
            Position newPosition = newEmptyPosition();
            if (newPosition.x == UNREACHABLE || newPosition.y == UNREACHABLE) return;
            if (rand() % 100 < getSowingProbability()) sow(newPosition);
        }
        world.moveToQueue(this);
    }

    bool collision(Organism* organism) {
        Organism::dead(organism);
        return true;
    }

    ~Plant() {};
};
