#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item
{
private:
    string description;
    string longDescription;
    int weightGrams;
    float value;
    bool weaponCheck;
public:
    Item (string description, int inWeight, float inValue);
    Item (string description);
    string getShortDescription();
    string getLongDescription();
    int getWeight();
    void setWeight(int weightGrams);
    float getValue();
    void setValue(float value);
};

#endif // ITEM_H
