#pragma once
#include<list>
#include<queue>
#include<cmath>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include "Narrator.h"
#include "Position.h"

using namespace std;

class Organism;

#define POPULATION 0.1 //percent of density of population

class World {
private:
    Narrator narrator;
    int width, heigth;
    int turn{};
    vector<vector<Organism*>> map;
    list<Organism*> moves;
    list<Organism*> organismsCreated;
    list<Organism*> deathList;
    list<Organism*> turnL;
    void printStartMessage();
    Organism * generateRandomOrganism(const Position & position);
    void createWorld(const int & width, const int & heigth,  const bool & loading = false, const double & density = POPULATION, const int & turn = 0);
    void createOrganism(const double & density);
    void createNewTurn();
    static bool whosInitiative(Organism * organism,  Organism * secondOrganism);
    
public:
    World(const int & width,const int & height, const int & turn = 0, const double & density = POPULATION);
    int getHeigth() const;
    int getWidth() const;
    void createNewGame(const int & width, const int & heigth, const bool & loading = false, const int & turn = 0, const double & density = POPULATION);
    Narrator &Narrator();
    void addRandomOrganism(const Position & position, Organism * organism);
    Organism * getTail(const Position & pos);
    void drawWorld();
    void makeTurn();
    void relocate(const Position &from, const Position &to);
    void moveToQueue(Organism * toMove);
    void unalive(Organism * corpse);
    void save(const string & name);
    void load(const string & name);

    ~World();
};

