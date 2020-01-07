#include "StringMenuItem.h"

#include <utility>

void StringMenuItem::display(LcdDriver *lcdDriver) {
    string textToDisplay = getText();
    unsigned int textSize = textToDisplay.size();
    textToDisplay.resize(20);
    fill(textToDisplay.begin() + textSize, textToDisplay.end(), ' ');
    lcdDriver->lcdString(textToDisplay.c_str());
}

StringMenuItem::StringMenuItem(string text) : text(std::move(text)) {}

string &StringMenuItem::getText() {
    return text;
}
