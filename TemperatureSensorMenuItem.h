//
// Created by martin.maliska on 10/27/2019.
//

#ifndef HOMEPI_TEMPERATURESENSORMENUITEM_H
#define HOMEPI_TEMPERATURESENSORMENUITEM_H


#include "TemperatureSensor.h"
#include "3party/lcd/lcdDriver.hpp"
#include "LcdMenuItem.h"
#include "StringMenuItem.h"
#include <string>
using namespace std;

class TemperatureSensorMenuItem: public StringMenuItem {

private:
    TemperatureSensor *temperatureSensor;
    string itemText;
public:
    explicit TemperatureSensorMenuItem(TemperatureSensor *temperatureSensor);
    string &getText() override;
};


#endif //HOMEPI_TEMPERATURESENSORMENUITEM_H
