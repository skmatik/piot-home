//
// Created by martin.maliska on 9/11/2019.
//

#ifndef HOMEPI_LCDMENU_H
#define HOMEPI_LCDMENU_H
#include <vector>
#include <string>
#include "3party/lcd/i2cControl.hpp"
#include "3party/lcd/lcdDriver.hpp"
#include "LcdMenuItem.h"

#define lcdAdd 0x3f

using namespace std;

class LcdMenu {
private:
    vector<LcdMenuItem *>* items;
    int currentItemIndex{};
    int rowsVisible;
    LcdDriver *lcdDriver;
    I2cControl *i2CControl;
public:
    LcdMenu(vector<LcdMenuItem *>* items, int rowsVisible);

    virtual ~LcdMenu();

    bool next();
    bool previous();
    int getCurrentItemIndex() const;
    void printMenu();
};


#endif //HOMEPI_LCDMENU_H
