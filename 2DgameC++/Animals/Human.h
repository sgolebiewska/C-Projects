#pragma once
#include "../Animal.h"
#include<conio.h>
#include<cwchar>
#include<sstream>
#define KEY_PRESSED 224
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define SPECIAL_ABILITY 'A'
#define PASS 'P'

#define HUMAN_ICON '@'
#define HUMAN_STRENGTH 5
#define HUMAN_INITIATIVE 4

#define ABILITY_TIME 5 
#define ABILITY_COOL_DOWN 5 

#define MAGICAL_POTION_BUFF 10 

class Human : public Animal {
private:
    int abilityWorkTime, abilityCoolDown;

public:
    Human(World& world, const Position& position, const int& strength, const int& abilityWorkTime, const int& abilityCoolDown)
        : Animal(world, strength, HUMAN_INITIATIVE, position, HUMAN_ICON), abilityWorkTime(abilityWorkTime), abilityCoolDown(abilityCoolDown)
    {}

    bool sameSpecies(Organism* org) {
        return dynamic_cast<Human*>(org) != nullptr;
    }

    int getDirection() {
        int directions;
        int firstKey = _getwch();
        switch (firstKey) {
        case KEY_PRESSED: {
            int secondKey = _getwch();
            switch (secondKey) {
            case KEY_UP: {
                directions = Position::UP;
                break;
            }
            case KEY_DOWN: {
                directions = Position::DOWN;
                break;
            }
            case KEY_RIGHT: {
                directions = Position::RIGHT;
                break;
            }
            case KEY_LEFT: {
                directions = Position::LEFT;
                break;
            }
            default: {}
            }
            break;
        }
        case SPECIAL_ABILITY: {
            if (abilityCoolDown == 0 && abilityWorkTime == 0) {
                abilityCoolDown = ABILITY_COOL_DOWN;
                abilityWorkTime = ABILITY_TIME + 1;
            }
            directions = Position::STAY;
            break;
        }
        case PASS: {
            directions = Position::STAY;
            break;
        }
        default: {}
        }

        return directions;
    }

    Organism* clone(const Position& position) {
        return new Human(this->world, position, HUMAN_STRENGTH, 0, 0);
    }

    void action() {
        Animal::action();
        if (abilityWorkTime > 0) {
            if (abilityWorkTime == ABILITY_TIME + 1) {
                this->world.Narrator().Ability(this);
                this->setStrength(MAGICAL_POTION_BUFF);
            }
            else if (abilityWorkTime > 0) {
                this->setStrength(this->getStrength() - 1);
            }
            abilityWorkTime--;
        }
        else if (abilityCoolDown > 0) {
            abilityCoolDown--;
        }
    }

    string getName() {
        return ("Human");
    }

    string save() const {
        stringstream ss;
        ss << Organism::save() << ' '
            << to_string(this->abilityWorkTime) << ' '
            << to_string(this->abilityCoolDown);
        return ss.str();
    }

    ~Human() {};
};

