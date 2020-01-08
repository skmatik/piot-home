#include "SensorMenuItem.h"

SensorMenuItem::SensorMenuItem(Sensor *sensor)
        : StringMenuItem(""), sensor(sensor), itemText() {}

string & SensorMenuItem::getText() {
    itemText.clear();
    itemText.append(sensor->getName())
    .append(": ")
    .append(sensor->getFormattedValue());
    return itemText;
}
