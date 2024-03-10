#pragma once
#include "Position.h"
#include<string>
#include<list>
#include<iostream>

using namespace std;

class Organism;

class Narrator {
private:
    list<string> messages;

public:
    Narrator();
    list<string> getAnnouncements();
    void Birth(Organism * parent2, Organism * parent1, Organism * kid);
    void Sowing(Organism * sower, Organism * kid);
    void Death(Organism * corpse);
    void Eaten(Organism * corpse);
    void Poisoning(Organism * victim, Organism * poison);
    void Intoxication(Organism * victim, Organism * toxic);
    void Ability(Organism *player);
    void announceStart();
    void announceStats();
    void announceAll();
    ~Narrator();
};


