#ifndef HOMEPI_LCDMENUITEM_H
#define HOMEPI_LCDMENUITEM_H

#include "3party/lcd/lcdDriver.hpp"

class LcdMenuItem {
public:
    virtual void display(LcdDriver *lcdDriver) = 0;
};

#endif //HOMEPI_LCDMENUITEM_H
