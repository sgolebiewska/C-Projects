#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include<iostream>
#include<sstream>

using namespace std;

Organism::Organism(World &world, int strength, const int & initiative, Position &position, const char &character)
: world(world), strength(strength), initiative(initiative), position(position), character(character)
{}

char Organism::getCharacter() const {
    return character;
}

int Organism::getStrength() const {
    return strength;
}

int Organism::getInitiative() const {
    return initiative;
}

int Organism::getAge() const {
    return age;
}

bool Organism::getShield(Organism * attacker) const {
    return shield;
}

int Organism::getEscapeChance() const {
    return escapeChance;
}

bool Organism::isAlive() const {
    return alive;
}

Position Organism::getPosition() const {
    return position;
}

void Organism::setStrength(int strength){
    this->strength = strength;
}

void Organism::setInitiative(int initiative) {
    this->initiative = initiative;
}

void Organism::setPosition(const Position & position) {
    this->position = position;
}

void Organism::setAge(int age) {
    this->age = age;
}

void Organism::dead(Organism * organism) {
    organism->alive = false;
    world.unalive(organism);
}

void Organism::draw(const int & y, const int & x) const {
    cout << character;
}

bool Organism::isPlant(Organism *org) {
    return dynamic_cast<Plant*>(org) != nullptr;
}

bool Organism::isAnimal(Organism *org) {
    return dynamic_cast<Animal*>(org) != nullptr;
}

bool Organism::isToxic() const {
    return toxic;
}

bool Organism::isNutrient() const {
    return nutrient;
}

int Organism::getDirection()
{
    vector<bool> dirVect = { true, true, true, true };
    dirVect = checkIfBorder(dirVect);

    int directions;
    bool validDirection = false;

    while (!validDirection) {
        directions = Position::getDirection();
        if (dirVect[directions]) {
            validDirection = true;
        }
    }

    return directions;
}

int Organism::getEmptyDirection() {
    vector<int> emptyDirections;
    vector<bool> dirVect = { true, true, true, true };
    dirVect = checkIfBorder(dirVect);
    dirVect = checkIfEmpty(dirVect);
    for (int i = 0; i < 4; i++) {
        if (dirVect[i]) {
            emptyDirections.push_back(i);
        }
    }
    if (emptyDirections.empty()) {
        return -1;
    }
    int index = rand() % emptyDirections.size();
    return emptyDirections[index];
}

Position Organism::newPosition() //get new random position
{
    Position newPosition = this->getPosition();
    return relocate(this->getDirection(), newPosition);
}

Position Organism::newEmptyPosition() // get new random empty position
{
    Position newPosition = this->getPosition();
    return relocate(this->getEmptyDirection(), newPosition);
}

Position Organism::relocate(const int & direction, Position &new_pos)
{
    Position newPosition = new_pos;
    switch (direction) {
    case Position::UP:
        newPosition.y -= 1;
        break;
    case Position::RIGHT:
        newPosition.x += 1;
        break;
    case Position::DOWN:
        newPosition.y += 1;
        break;
    case Position::LEFT:
        newPosition.x -= 1;
        break;
    case Position::STAY:
        break;
    default:
        newPosition.x = UNREACHABLE;
        newPosition.y = UNREACHABLE;
        break;
    }
    return newPosition;
}

vector<bool> & Organism::checkIfBorder (vector<bool> & dirVect) //check if current position is touching the border of the board
{
    Position pos = this->getPosition();
    for (int i = 0; i < 4; i++) {
        if ((i == Position::UP && pos.y == 0) ||
            (i == Position::DOWN && pos.y == world.getHeigth() - 1) ||
            (i == Position::LEFT && pos.x == 0) ||
            (i == Position::RIGHT && pos.x == world.getWidth() - 1)) {
            dirVect[i] = false;
        }
    }
    return dirVect;
}

vector<bool>& Organism::checkIfEmpty(vector<bool>& dirVect) {
    Position pos = getPosition();
    for (int dir = 0; dir < dirVect.size(); dir++) {
        if (dirVect[dir]) {
            Position nextPos = pos;
            if (dir == Position::UP) nextPos.y--;
            else if (dir == Position::DOWN) nextPos.y++;
            else if (dir == Position::LEFT) nextPos.x--;
            else if (dir == Position::RIGHT) nextPos.x++;
            if (world.getTail(nextPos) != nullptr) dirVect[dir] = false;
        }
    }
    return dirVect;
}

string Organism::save() const {
    stringstream ss;
    ss << this->getCharacter() << ' '
        << this->getAge() << ' '
        << this->getPosition().x << ' '
        << this->getPosition().y << ' '
        << this->getStrength();
    return ss.str();
}

Organism::~Organism() {};