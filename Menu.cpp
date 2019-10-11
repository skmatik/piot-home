//
// Created by martin.maliska on 9/11/2019.
//

#include "Menu.h"

#include <utility>

bool Menu::next() {
    if (currentItemIndex < (items.size() - rowsVisible -1)) {
        ++currentItemIndex;
        return true;
    }
    return false;
}

bool Menu::previous() {
    if (currentItemIndex > 0) {
        --currentItemIndex;
        return true;
    }
    return false;
}

string Menu::getCurrentItem() {
    return items[currentItemIndex];
}

int Menu::getCurrentItemIndex() const {
    return currentItemIndex;
}

void Menu::setCurrentItemIndex(int newIndex) {
    currentItemIndex = newIndex;
}

Menu::Menu(vector<string> items, int rowsVisible, LcdDriver *lcdDriver) : items(std::move(items)), rowsVisible(rowsVisible),
                                                                                 lcdDriver(lcdDriver), currentItemIndex(0) {}

void Menu::printMenu() {
    int firstItemIndex = getCurrentItemIndex() + 1;
    for (int i = 0; i < 4; i++) {
        lcdDriver->setCursorPositionRowCol(i + 1, 0);
        const string &message = items[i + firstItemIndex];
        char cstr[message.size() + 1];
        message.copy(cstr, message.size() + 1);
        cstr[message.size()] = '\0';
        lcdDriver->lcdString(cstr);
    }
}
