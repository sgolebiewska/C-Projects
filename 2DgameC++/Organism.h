#pragma once
#include "World.h"
#include<iostream>

using namespace std;

#define NUTRICITY 3 
#define NUMBER_OF_DIRECTIONS 4 

class World;

class Organism {
protected:
    char character;
    bool alive = true;
    bool shield = false;
    bool nutrient = false;
    bool toxic = false;
    int age = 1;
    int escapeChance = 0;
    int strength;
    int initiative;
    Position position;
    World &world;
    virtual int getDirection();
    int getEmptyDirection();
public:
    Organism(World &world, int strength, const int & initiative, Position & position, const char & character);
    virtual Organism * clone(const Position & position) = 0;
    virtual bool collision(Organism * organism) = 0;
    virtual string getName() = 0;
    virtual void action() = 0;
    char getCharacter() const;
    int getStrength() const;
    int getInitiative() const;
    int getAge() const;
    int getEscapeChance() const;
    Position getPosition() const;
    void setPosition(const Position & position);
    void setAge(int age);
    void setStrength(int strength);
    void setInitiative(int initiative);
    bool isAlive() const;
    bool isNutrient() const;
    bool isToxic() const;
    static bool isPlant (Organism * org);
    static bool isAnimal (Organism * org);
    virtual bool getShield(Organism * attacker) const;
    vector<bool> & checkIfBorder (vector<bool> & windRose);
    vector<bool> & checkIfEmpty (vector<bool> & windRose);
    static Position relocate(const int & direction, Position &new_pos);
    Position newPosition();
    Position newEmptyPosition();
    void dead(Organism * organism);
    void draw(const int & y, const int & x) const;
    virtual string save() const;
    virtual ~Organism();
};