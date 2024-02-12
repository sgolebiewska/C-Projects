#include "Narrator.h"
#include "Organism.h"
#include<Windows.h>
#include<iostream>
#include<list>

using namespace std;

/* This class is responsible for making announcements about the state of the game, 
it also gives some additional ifo about the game to the user.
It pushes all announcements from 1 turn into vector and then announcements them all in next turn. */

Narrator::Narrator(){};

list<string> Narrator::getAnnouncements() {
    return messages;
}

void Narrator::Birth(Organism *parent2, Organism *parent1, Organism *kid) {
    messages.push_back(parent2->getName() + "(" + to_string(parent2->getPosition().y) + "," + to_string(parent2->getPosition().x) + ") with "
        + parent1->getName() + "(" + to_string(parent1->getPosition().y) + "," + to_string(parent1->getPosition().x) + ") had a kid "
        + kid->getName() + "(" + to_string(kid->getPosition().y) + "," + to_string(kid->getPosition().x) + ")");
}

void Narrator::Sowing(Organism *sower, Organism *kid) {
    messages.push_back(sower->getName() + "(" + to_string(sower->getPosition().y) + "," + to_string(sower->getPosition().x)
        + ") spread " + kid->getName() + "(" + to_string(kid->getPosition().y) + "," + to_string(kid->getPosition().x) + ")");
}

void Narrator::Death(Organism *corpse) {
    messages.push_back(corpse->getName() + " lies dead at (" + to_string(corpse->getPosition().y)
        + "," + to_string(corpse->getPosition().x) + ")");
}

void Narrator::Eaten(Organism *corpse) {
    messages.push_back(corpse->getName() + " was eaten at (" + to_string(corpse->getPosition().y)
        + "," + to_string(corpse->getPosition().x) + ")");
}

void Narrator::Poisoning(Organism *victim, Organism *poison) {
    messages.push_back(victim->getName() + " tried to eat " + poison->getName() + " at (" + to_string(poison->getPosition().y)
        + "," + to_string(poison->getPosition().x) + ") and died from poisoning");
}

void Narrator::Intoxication(Organism *victim, Organism *poison) {
    messages.push_back(poison->getName() + "(" + to_string(poison->getPosition().y) + "," + to_string(poison->getPosition().x)
        + ") poisoned " + victim->getName() + " at (" + to_string(victim->getPosition().y) + "," + to_string(victim->getPosition().x) + ")");
}

void Narrator::Ability(Organism *player) {
    messages.push_back(player->getName() + "(" + to_string(player->getPosition().y) + "," + to_string(player->getPosition().x)
        + ") has activated special ability");
}

void Narrator::announceStart() {
    cout << "Dear player," << endl << "just imagine yourself in a very dangerous forest with all kinds of vicious plants and animals." 
        << endl << "What would you do?" << endl << "Would you be scared or maybe killed them all?" << endl
        << "Amazing news! You can find out!:)" << endl << "This game is a single-player console game, good luck!;)" << endl;
    cout << "Here are some rules: " << endl
        << "You can always quit your game - just type 'Q'. The goal of this game is not to be killed:) Your character is denoted by '@'. Before every move you have to type 'T' - it allows you to turn the next round. After that just choose side with an arrow:) If you want to use special ability type 'R'. You have an option to save('S') and load('L') a game from a file." <<
        endl << "Good luck!" << endl;
    cout << "Press any key to continue..." << endl;
    _getch();
}

void Narrator::announceStats() {
    cout << "Dear player," << endl << "the game has ended but I'm not sure how you did. Did you die?"<< endl 
        <<"Hmm, either way good job playing the game! Thanks!!:)" << endl;
    cout << "Press any key to continue..." << endl;
    _getch();
}

void Narrator::announceAll() {
    cout << "Announcement log:" << endl;
    for (string & message : getAnnouncements())
    {
        cout << message << endl;
    }
    messages.clear();
    cout << endl << "What is your next move, player?" << endl;
}

Narrator::~Narrator() {};