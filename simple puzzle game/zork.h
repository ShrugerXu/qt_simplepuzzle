#ifndef ZORK_H
#define ZORK_H
#include "Room.h"
#include <iostream>
#include <string>
using namespace std;
class Zork
{private:
    //Parser parser;
        Room *currentRoom;
        void createRooms();
       // void printWelcome();
       // bool processCommand(Command command);
       // void printHelp();
        void goRoom(string direction);
      //  void createItems();
      //  void displayItems();


public:
    Zork();
    void run();
    string go(string direction);
};

#endif // ZORK_H
