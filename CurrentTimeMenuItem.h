
#ifndef HOMEPI_CURRENTTIMEMENUITEM_H
#define HOMEPI_CURRENTTIMEMENUITEM_H

#include "StringMenuItem.h"

class CurrentTimeMenuItem : public StringMenuItem {
private:
    string itemText;

public:
    string & getText() override;

    CurrentTimeMenuItem();
};


#endif //HOMEPI_CURRENTTIMEMENUITEM_H
