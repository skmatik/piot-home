#include "LcdMenu.h"

#include <iostream>

bool LcdMenu::next() {
    if (currentItemIndex < (items->size() - rowsVisible - 1)) {
        ++currentItemIndex;
        return true;
    }
    return false;
}

bool LcdMenu::previous() {
    if (currentItemIndex > 0) {
        --currentItemIndex;
        return true;
    }
    return false;
}

int LcdMenu::getCurrentItemIndex() const {
    return currentItemIndex;
}

void LcdMenu::printMenu() {
    cout << "Printing menu!" << endl;
    cout.flush();
    int firstItemIndex = getCurrentItemIndex();
    for (int i = 0; i < 4; i++) {
        lcdDriver->setCursorPositionRowCol(i + 1, 0);
        LcdMenuItem *item = items->operator[](i + firstItemIndex);
        item->display(lcdDriver);
    }
}

LcdMenu::~LcdMenu() {
    delete (lcdDriver);
    delete (i2CControl);
    delete(items);
}

LcdMenu::LcdMenu(vector<LcdMenuItem *> *items, int rowsVisible) : items(items),
                                                                  rowsVisible(rowsVisible),
                                                                  currentItemIndex(0) {
    i2CControl = new I2cControl(0);
    lcdDriver = new LcdDriver((char) lcdAdd, i2CControl);
    lcdDriver->lcdSendCommand(LCD_BEG_LINE_1);
}
