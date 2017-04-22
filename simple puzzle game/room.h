#ifndef ROOM_H
#define ROOM_H
#include "item.h"
#include <map>
#include <string>
#include <vector>
using namespace std;
using std::vector;

class Room
{
private:
    string description;
    map<string, Room*> exits;
    string exitString();
    vector <Item> itemsInRoom;
    int roomLicense;
public:
    int numberOfItems();
        Room(string description, int licence);
        void setExits(Room *north, Room *east, Room *south, Room *west);
        string shortDescription();
        string longDescription();
        Room* nextRoom(string direction);
        void addItem(Item *inItem);
        string displayItem(unsigned int x);
        int isItemInRoom(string inString);
        void removeItemFromRoom(int location);
        int itemSize();
        bool checkRoomLicense();
        void openRoomLicense();
};
#endif // ROOM_H
