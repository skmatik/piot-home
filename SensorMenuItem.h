//
// Created by martin.maliska on 10/27/2019.
//

#ifndef HOMEPI_SENSORMENUITEM_H
#define HOMEPI_SENSORMENUITEM_H


#include "TemperatureSensor.h"
#include "3party/lcd/lcdDriver.hpp"
#include "LcdMenuItem.h"
#include "StringMenuItem.h"
#include <string>
using namespace std;

class SensorMenuItem: public StringMenuItem {

private:
    Sensor *sensor;
    string itemText;
public:
    explicit SensorMenuItem(Sensor *sensor);
    string &getText() override;
};


#endif //HOMEPI_SENSORMENUITEM_H
