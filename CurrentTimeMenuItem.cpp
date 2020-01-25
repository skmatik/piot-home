
#include <chrono>
#include <iostream>
#include <iomanip>
#include "CurrentTimeMenuItem.h"

string &CurrentTimeMenuItem::getText() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    ostringstream os;
    os << "Cas: " << put_time(&tm, "%T %m-%d");
    itemText.clear();
    itemText.append(os.str());
    return itemText;
}

CurrentTimeMenuItem::CurrentTimeMenuItem() : StringMenuItem("") {

}
