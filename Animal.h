#pragma once
#include<iostream>
#include "Organism.h"

using namespace std;

class Animal : public Organism {
protected:
    int steps = 1;
    vector<Position> findKidTiles(Organism* parents);
    virtual bool sameSpecies(Organism * org) = 0;
    void makeKid(Organism * parents);
    bool chanceToMove(const Position & endPosition);
    bool escapeProtocol(Organism * organism, Organism * attacker);

public:
    Animal(World &world, int strength, const int & initiative, Position position, const char & icon);
    void action() override;
    static Position getEscapeTile(Organism * escaper);
    void escapeMotion(Organism * escaper, const Position & escapePosition);
    bool collision(Organism * organism) override;
    int getSteps() const;
    ~Animal() override;
};

