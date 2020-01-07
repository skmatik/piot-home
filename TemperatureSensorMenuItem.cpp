#include "TemperatureSensorMenuItem.h"

TemperatureSensorMenuItem::TemperatureSensorMenuItem(TemperatureSensor *temperatureSensor)
        : StringMenuItem(""), temperatureSensor(temperatureSensor), itemText() {}

string & TemperatureSensorMenuItem::getText() {
    itemText.clear();
    itemText.append(temperatureSensor->getName())
    .append(": ")
    .append(temperatureSensor->getFeedValue());
    return itemText;
}
