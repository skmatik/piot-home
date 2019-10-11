//
// Created by martin.maliska on 9/11/2019.
//

#ifndef HOMEPI_MENU_H
#define HOMEPI_MENU_H
#include <vector>
#include <string>
#include "i2cControl.hpp"
#include "lcdDriver.hpp"

using namespace std;

class Menu {
private:
    vector<string> items;
    int currentItemIndex;
    int rowsVisible;
    LcdDriver *lcdDriver;
public:
    Menu(vector<string> items, int rowsVisible, LcdDriver *lcdDriver);

    bool next();
    bool previous();
    string getCurrentItem();
    int getCurrentItemIndex() const;
    void setCurrentItemIndex(int currentItemIndex);
    void printMenu();
};


#endif //HOMEPI_MENU_H
