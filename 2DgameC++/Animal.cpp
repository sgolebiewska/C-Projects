#include "Animal.h"
#include<iostream>

using namespace std;

Animal::Animal(World &world, int strength, const int & initiative, Position position, const char & icon): Organism(world, strength, initiative, position, icon)
{}

vector<Position> Animal::findKidTiles(Organism* parents) // Find a tail neighbouring parents for their kid
{
    vector<Position> tiles;
    Position parent1Pos = this->getPosition();
    Position parent2Pos = parents->getPosition();

    // Check if parents are on the same row or column
    if (parent1Pos.y == parent2Pos.y)
    {
        // Add tiles above and below parents
        tiles.push_back({ parent1Pos.y - 1, parent1Pos.x });
        tiles.push_back({ parent2Pos.y - 1, parent2Pos.x });
        tiles.push_back({ parent1Pos.y + 1, parent1Pos.x });
        tiles.push_back({ parent2Pos.y + 1, parent2Pos.x });
    }
    else if (parent1Pos.x == parent2Pos.x)
    {
        // Add tiles to the left and right of parents
        tiles.push_back({ parent1Pos.y, parent1Pos.x - 1 });
        tiles.push_back({ parent2Pos.y, parent2Pos.x - 1 });
        tiles.push_back({ parent1Pos.y, parent1Pos.x + 1 });
        tiles.push_back({ parent2Pos.y, parent2Pos.x + 1 });
    }

    // Remove tiles that are outside the board
    if (parent1Pos.y == 0 && parent2Pos.y == 0) tiles.erase(tiles.begin(), tiles.begin() + 2);
    else if (parent1Pos.y == world.getHeigth() - 1 && parent2Pos.y == world.getHeigth() - 1)  tiles.erase(tiles.end() - 2, tiles.end());
    else if (parent1Pos.x == 0 && parent2Pos.x == 0) tiles.erase(tiles.begin(), tiles.begin() + 2);
    else if (parent1Pos.x == world.getWidth() - 1 && parent2Pos.x == world.getWidth() - 1) tiles.erase(tiles.end() - 2, tiles.end());

    return tiles;
}

void Animal::action() {
    bool isDone = false;
    setAge(getAge() + 1); 
    for (int step = 0; step < getSteps() && isAlive() && !isDone; ++step) {
        isDone = chanceToMove(newPosition());
    }
}

bool Animal::chanceToMove(const Position & endPosition)
{
    Position startingPosition = getPosition();
    world.moveToQueue(this);
    if (endPosition.x == startingPosition.x && endPosition.y == startingPosition.y) return false;
    if (sameSpecies(world.getTail(endPosition))) // Encountered a mate
    {
        makeKid(world.getTail(endPosition));
        return true;
    }
    if (world.getTail(endPosition) == nullptr) // Tile is empty
    {
        setPosition(endPosition);
        world.relocate(startingPosition, endPosition);
        return false;
    }
    if (collision(world.getTail(endPosition))) // Fights
    {
        setPosition(endPosition);
        world.relocate(startingPosition, endPosition);
        return true;
    }

    return true;
}

bool Animal::escapeProtocol(Organism* organism, Organism* attacker) {
    // Calculate the chance for the organism and the attacker to escape
    int chanceToEscapeOrganism = organism->getEscapeChance();
    int chanceToEscapeAttacker = attacker->getEscapeChance();
    int totalChanceToEscape = chanceToEscapeOrganism + chanceToEscapeAttacker;

    // Generate a random number between 0 and 99
    int randomNum = rand() % 100;

    if (randomNum >= totalChanceToEscape) {
        // Neither the organism nor the attacker escaped
        return false;
    }

    Position attackerPos = attacker->getPosition();
    Position escapeTile = getEscapeTile(organism);
    bool escaped = !(escapeTile.y == -1 || escapeTile.x == -1); // if there are no free tiles to escape

    if (escaped) {
        if (randomNum < chanceToEscapeOrganism) {
            // Organism escaped
            attacker->setPosition(organism->getPosition());
            escapeMotion(organism, escapeTile);
            world.relocate(attackerPos, attacker->getPosition());
        }
        else {
            // Attacker escaped
            escapeMotion(attacker, escapeTile);
        }
    }

    return escaped;
}

Position Animal::getEscapeTile(Organism * escaper)
{
    if (escaper->newEmptyPosition().x == -1 || escaper->newEmptyPosition().y == -1) return {-1, -1};
    return escaper->newEmptyPosition();
}

void Animal::escapeMotion(Organism *escaper, const Position & escapePosition)
{
    world.relocate(escaper->getPosition(), escapePosition);
    escaper->setPosition(escapePosition);
}

bool Animal::collision(Organism* organism)
{
    bool escaped = escapeProtocol(organism, this); // Check if the attacker or organism escaped
    if (escaped || organism->getShield(this)) return false;

    if (isPlant(organism)){
        world.Narrator().Eaten(organism);
        if (organism->isNutrient()) this->setStrength(this->getStrength() + NUTRICITY);
        else if (organism->isToxic()){
            world.Narrator().Poisoning(this, organism);
            this->dead(this);
            return false;
        }
        this->dead(organism);
        return true;
    }
    else if (this->getStrength() >= organism->getStrength()){
        world.Narrator().Death(organism);
        this->dead(organism);
        return true;
    }
    else{
        world.Narrator().Death(this);
        this->dead(this);
        return false;
    }
}

void Animal::makeKid(Organism* parents)
{
    vector<Position> possibleTiles = findKidTiles(parents);
    if (possibleTiles.empty()) return;
    int index;
    do
    {
        index = rand() % possibleTiles.size(); //produce a random tile from possible ones
        Position pos = possibleTiles[index];
        Organism* org = world.getTail(pos);
        if (org == nullptr)
        {
            Organism* kid = clone(pos);
            world.addRandomOrganism(pos, kid);
            world.Narrator().Birth(this, parents, kid);
            break;
        }
    } while (true);
}

int Animal::getSteps() const // return how many moves the animal have
{
    return steps;
}

Animal::~Animal() = default;