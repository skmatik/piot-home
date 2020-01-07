//
// Created by martin.maliska on 10/27/2019.
//

#ifndef HOMEPI_STRINGMENUITEM_H
#define HOMEPI_STRINGMENUITEM_H

#include "LcdMenuItem.h"
#include "3party/lcd/lcdDriver.hpp"
#include <string>

using namespace std;

class StringMenuItem : public LcdMenuItem {

    string text;
public:
    void display(LcdDriver *lcdDriver) override;
    explicit StringMenuItem(string text);

    virtual string &getText();
};


#endif //HOMEPI_STRINGMENUITEM_H
