//
// Created by martin.maliska on 9/14/2019.
//

#include "TemperatureSensor.h"
#include <fstream>
#include <sstream>

using namespace std;

void TemperatureSensor::readCurrentValue() {

    ifstream sensorFile;
    string sensorPath = "/sys/bus/w1/devices/" + address + "/w1_slave";
    sensorFile.open(sensorPath.c_str());
    if (sensorFile) {
        found = true;
        string temperatureString;
        stringstream buffer;
        buffer << sensorFile.rdbuf();
        temperatureString = buffer.str();
        sensorFile.close();
        temperatureString = temperatureString.substr(temperatureString.find("t=") + 2);
        temperature = stod(temperatureString) / 1000;
    }
}

TemperatureSensor::TemperatureSensor(const string &address) : address(address), found(false), temperature(0) {

}

bool TemperatureSensor::isFound() const {
    return found;
}

double TemperatureSensor::getTemperature() const {
    return temperature;
}

string TemperatureSensor::getFeedValue() {
    return getTemperatureAsString();
}

string TemperatureSensor::getFeedName() {
    return FEED_NAME;
}

string TemperatureSensor::getTemperatureAsString() {
    std::ostringstream temperatureString;
    temperatureString << temperature;
    return temperatureString.str();
}
