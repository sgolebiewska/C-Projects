#include "World.h"
#include<cstdlib>
#include<Windows.h>
#include<ctime>
#include<iostream>

#define END_GAME 'Q'
#define LOAD_GAME 'L'
#define SAVE_GAME 'S'
#define NEW_TURN 'T'

using namespace std;

int main() {
    srand(time(nullptr));
    int width, height;
    cout << "Welcome to the game!:) Before you will get to know anything just enter the dimensions of your board: " << endl;
    cin >> width >> height;
    World world(width, height);
    world.Narrator().announceStart();
    while(true)
    {
        system("cls");
        world.drawWorld();
        world.Narrator().announceAll();
        char command;
        cin >> command;
        switch (command) {
            case NEW_TURN: {
                world.makeTurn();
                break;
            }
            case SAVE_GAME: {
                string fileName;
                cout << "Enter the name of the file (action: save): ";
                cin >> fileName;
                world.save(fileName);
                break;
            }
            case LOAD_GAME: {
                string fileName;
                cout << "Enter the name of the file (action: load): ";
                cin >> fileName;
                world.load(fileName);
                break;
            }
            case END_GAME: {
                system("cls");
                world.Narrator().announceStats();
                return 0;
            }
            default: {
                break;
            }
        }
    }
}
