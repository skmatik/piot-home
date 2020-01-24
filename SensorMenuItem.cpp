#include <iostream>
#include "SensorMenuItem.h"

SensorMenuItem::SensorMenuItem(Sensor *sensor)
        : StringMenuItem(""), sensor(sensor), itemText() {}

string & SensorMenuItem::getText() {
    unsigned int textSize = sensor->getName().size() + 1 + sensor->getFormattedValue().size();
    itemText.clear();
    itemText.append(sensor->getName())
    .append(":")
    .append(20 - textSize, ' ')
    .append(sensor->getFormattedValue());
    return itemText;
}
