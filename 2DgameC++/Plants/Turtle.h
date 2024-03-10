#pragma once
#include "../Animal.h"

#define TURTLE_ICON 'T'
#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1
#define TURTLE_CHANCE_TO_STAY 75
#define TURTLE_REFLECT_ABILITY 5

using namespace std;

class Turtle : public Animal{
public:
    Turtle(World& world, const Position& position, const int& strength)
        : Animal(world, strength, TURTLE_INITIATIVE, position, TURTLE_ICON)
    {
        shield = true;
    }

    string getName() {
        return ("Turtle");
    }

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Turtle*>(org) != nullptr;
    }

    Organism* clone(const Position& position) {
        return new Turtle(this->world, position, TURTLE_STRENGTH);
    }

    void action() {
        if ((rand() % 100) <= TURTLE_CHANCE_TO_STAY) 
        {
            this->setAge(this->getAge() + 1); 
            world.moveToQueue(this);
            return;
        }
        Animal::action();
    }

    bool getShield(Organism* attacker) const {
        if (attacker->getStrength() < TURTLE_REFLECT_ABILITY) return true;
        return false;
    }

    ~Turtle() {};
};
