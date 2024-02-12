#pragma once
#include "../Plant.h"

#define HOGWEED_ICON 'H'
#define HOGWEED_STRENGTH 10
#define HOGWEED_SOW_POSIBILITY 20

using namespace std;

class Hogweed : public Plant {
public:
    Hogweed(World& world, const Position& position, const int& strength):Plant(world, position, HOGWEED_ICON, strength, HOGWEED_SOW_POSIBILITY)
    {
        toxic = true;
    }

    Organism* clone(const Position& position) {
        return new Hogweed(this->world, position, HOGWEED_STRENGTH);
    }

    void action() {
        Position pos0 = getPosition();
        vector<bool> vec(NUMBER_OF_DIRECTIONS, true);
        checkIfBorder(vec);
        for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
        {
            if (vec[i])
            {
                Organism* victim = world.getTail(relocate(i, pos0));
                if (victim != nullptr && isAnimal(victim))
                {
                    world.Narrator().Intoxication(victim, this);
                    dead(victim);
                }
            }
        }
        world.moveToQueue(this);//has completed task for this turn can move to another
    }

    string getName() {
        return ("Sosnowky's Hogweed");
    }

    ~Hogweed() {};
};
