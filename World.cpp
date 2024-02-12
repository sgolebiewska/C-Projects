#include "World.h"
#include "Animals/Wolf.h"
#include "Animals/Sheep.h"
#include "Animals/Fox.h"
#include "Animals/Turtle.h"
#include "Animals/Antelope.h"
#include "Plants/Grass.h"
#include "Plants/Guarana.h"
#include "Plants/Sow_thistle.h"
#include "Plants/Belladonna.h"
#include "Plants/Hogweed.h"
#include "Animals/Human.h"
#include<iostream>
#include<list>

#define NUMBER_OF_ORGANISMS 10

using namespace std;

World::World(const int& width, const int& height, const int& turn, const double& density)
    : width(width), heigth(height), turn(turn), narrator(), map(height, vector<Organism*>(width, nullptr))
{
    createWorld(width, height, false, density);
}

Narrator& World::Narrator() {
    return this->narrator;
}

int World::getHeigth() const
{
    return heigth;
}

int World::getWidth() const
{
    return width;
}

void World::createWorld(const int& width, const int& heigth, const bool& loading, const double& density, const int& turn)
{
    this->width = width;
    this->heigth = heigth;
    this->turn = turn;

    map.resize(heigth);
    for (auto& row : map) {
        row.resize(width, nullptr);
    }

    if (!loading)createOrganism(density);
    else return;

}

void World::printStartMessage()
{
    cout << "Sandra Golebiewska, 193198 " << endl;
    cout << "Turn no: " << this->turn << "." << endl;
    if (this->turn == 0) {
        cout << "Welcome:) This is round 0! Right now you can see how the board is constructed and what animals and plants are on a board. If you are ready for a real round just type 'T'."<<
            endl<<"But now let me show you a little legend of all characters:" <<
            endl << "'@' -> that's you;" <<
            endl << "'W' -> wolf, better be careful!;" <<
            endl << "'S' -> sheep;" <<
            endl << "'F' -> fox,  he likes to run away!;" <<
            endl << "'T' -> turtle, he reflects attacks!!;" <<
            endl << "'A' -> antelope;" <<
            endl << "'#' -> grass;" <<
            endl << "'&' -> sow thistle;" <<
            endl << "'G' -> guarana, eat them to be strong!;" <<
            endl << "'B' -> belladona, don't eat it, unless you wanna be dead!;" <<
            endl << "'H' -> sosnowky's hogweed, him and belladona are best friends if you know what I mean, hehe;"<<endl;
    }
}

void World::createOrganism(const double& density) {
    // Create a new Human at a random position
    Position position = { rand() % heigth, rand() % width };
    addRandomOrganism(position, new Human(*this, position, HUMAN_STRENGTH, 0, 0));

    // Generate and place the remaining organisms
    for (int i = 0; i < floor(heigth * width * density) - 1; i++) {
        bool placed = false;
        while (!placed) {
            // Generate a random position
            Position position = { rand() % heigth, rand() % width };

            // Check if the position is empty
            if (map[position.y][position.x] == nullptr) {
                // Generate a random organism and add it to the map
                Organism* organism = generateRandomOrganism(position);
                map[position.y][position.x] = organism;
                organismsCreated.push_back(organism);
                placed = true;
            }
        }
    }
}

void World::makeTurn()
{
    for (Organism*& organism : turnL) {
        //for every organism in turn queue that is not on the death queue make a move
        if (find(deathList.begin(), deathList.end(), organism) != deathList.end()) continue;
        organism->action();
    }
    this->createNewTurn();
    ++turn;
}

void World::drawWorld()
{
    this->printStartMessage();
    cout << string(width + 2, '*') << endl;
    for (int y = 0; y < heigth; ++y) {
        cout << '*';
        for (int x = 0; x < width; ++x) {
            cout << (map[y][x] ? map[y][x]->getCharacter() : ' ');
        }
        cout << '*' << endl;
    }
    cout << string(width + 2, '*') << endl;
}

void World::createNewGame(const int &width, const int &heigth, const bool & loading, const int & turn, const double &density) //clear all the queues
{
    this->turnL.clear();
    this->moves.clear();
    this->organismsCreated.clear();
    this->deathList.clear();
    this->map.clear();
    createWorld(width, heigth, loading, density, turn);
}

void World::moveToQueue(Organism * toMove)
{
    moves.push_back(toMove);
}

void World::addRandomOrganism(const Position& position, Organism* organism) {
    Organism* org = organism != nullptr ? organism : generateRandomOrganism(position);
    map[position.y][position.x] = org;
    organismsCreated.emplace_back(org);
}

Organism* World::generateRandomOrganism(const Position& position) {
    Organism* organism = nullptr;
    const int organismIndex = rand() % NUMBER_OF_ORGANISMS;
    switch (organismIndex) {
    case 0: organism = new Wolf(*this, position, WOLF_STRENGTH); break;
    case 1: organism = new Sheep(*this, position, SHEEP_STRENGTH); break;
    case 2: organism = new Fox(*this, position, FOX_STRENGTH); break;
    case 3: organism = new Turtle(*this, position, TURTLE_STRENGTH); break;
    case 4: organism = new Antelope(*this, position, ANTELOPE_STRENGTH); break;
    case 5: organism = new Grass(*this, position, GRASS_STRENGTH); break;
    case 6: organism = new Guarana(*this, position, GUARANA_STRENGTH); break;
    case 7: organism = new Sow_thistle(*this, position, SOW_THISTLE_STRENGTH); break;
    case 8: organism = new Belladonna(*this, position, BELLADONNA_STRENGTH); break;
    case 9: organism = new Hogweed(*this, position, HOGWEED_STRENGTH); break;
    default: return nullptr;
    }
    return organism;
}

Organism *World::getTail(const Position &pos)
{
    return map[pos.y][pos.x];
}

void World::createNewTurn()
{
    // combine moves and organismsCreated vectors and remove duplicates
    turnL = moves;
    turnL.insert(turnL.end(), organismsCreated.begin(), organismsCreated.end());
    turnL.erase(unique(turnL.begin(), turnL.end()), turnL.end());

    // sort organisms based on initiative
    stable_sort(turnL.begin(), turnL.end(), whosInitiative);

    // clear moves, organismsCreated and deathList vectors
    moves.clear();
    organismsCreated.clear();
    deathList.clear();
}

bool World::whosInitiative(Organism *organism, Organism *secondOrganism)
{
    if (organism->getInitiative() > secondOrganism->getInitiative()) return true;
    else if (organism->getInitiative() == secondOrganism->getInitiative()) return organism->getAge() > secondOrganism->getAge();
    else return false;
}

void World::relocate(const Position &from, const Position &to)
{
    Organism* organismFrom = map[from.y][from.x];
    Organism* organismTo = map[to.y][to.x];
    map[from.y][from.x] = organismTo;
    map[to.y][to.x] = organismFrom;
}

void World::unalive(Organism *corpse)
{
    deathList.push_back(corpse);
    map[corpse->getPosition().y][corpse->getPosition().x] = nullptr;
}

//point 5
void World::save(const string& name) {
    ofstream inputFile(name + ".txt");
    inputFile << turn << ' ' << width << ' ' << heigth << '\n';
    for (const auto& organism : turnL) {
        if (find(deathList.begin(), deathList.end(), organism) != deathList.end() || !organism->isAlive()) continue;
        inputFile << organism->save() << '\n';
    }
    inputFile.close();
}

void World::load(const string& name) {
    ifstream inputFile(name + ".txt");
    int width, height, turn;
    Organism* organism = nullptr;
    inputFile >> turn >> width >> height;
    createNewGame(width, height, true, turn);
    while (inputFile >> ws, inputFile.peek() != EOF) {
        char icon;
        int age, x, y, strength, abilityTime, abilityCoolDown;

        inputFile >> icon >> age >> x >> y >> strength;
        Position position = { y, x };

        switch (icon) {
        case HUMAN_ICON: {
            inputFile >> abilityTime >> abilityCoolDown;
            organism = new Human(*this, position, strength, abilityTime, abilityCoolDown);
            break;
        }
        case WOLF_ICON:
            organism = new Wolf(*this, position, strength);
            break;
        case SHEEP_ICON:
            organism = new Sheep(*this, position, strength);
            break;
        case FOX_ICON:
            organism = new Fox(*this, position, strength);
            break;
        case TURTLE_ICON:
            organism = new Turtle(*this, position, strength);
            break;
        case ANTELOPE_ICON:
            organism = new Antelope(*this, position, strength);
            break;
        case GRASS_ICON:
            organism = new Grass(*this, position, strength);
            break;
        case GUARANA_ICON:
            organism = new Guarana(*this, position, strength);
            break;
        case SOW_THISTLE_ICON:
            organism = new Sow_thistle(*this, position, strength);
            break;
        case BELLADONNA_ICON:
            organism = new Belladonna(*this, position, strength);
            break;
        case HOGWEED_ICON:
            organism = new Hogweed(*this, position, strength);
            break;
        default:
            organism = nullptr;
            break;
        }
        if (organism != nullptr) addRandomOrganism(organism->getPosition(), organism);
    }
    inputFile.close();
    createNewTurn();
}

World::~World() {};








