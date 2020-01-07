//
// Created by martin.maliska on 9/14/2019.
//

#include "TemperatureSensor.h"
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

void TemperatureSensor::read() {

    ifstream sensorFile;
    string sensorPath = "/sys/bus/w1/devices/" + address + "/w1_slave";
    sensorFile.open(sensorPath.c_str());
    if (sensorFile) {
        found = true;
        string encodedTemperature;
        stringstream buffer;
        buffer << sensorFile.rdbuf();
        encodedTemperature = buffer.str();
        sensorFile.close();
        encodedTemperature = encodedTemperature.substr(encodedTemperature.find("t=") + 2);
        temperature = stod(encodedTemperature) / 1000;
        updateTemperatureString();
    }
}

TemperatureSensor::TemperatureSensor(string address, string feedName, string name) : address(std::move(address)),
                                                                                     found(false),
                                                                                     temperature(0),
                                                                                     feedName(std::move(feedName)),
                                                                                     formattedValue(""),
                                                                                     name(std::move(name)) {
}

bool TemperatureSensor::isFound() const {
    return found;
}

double TemperatureSensor::getTemperature() const {
    return temperature;
}

string &TemperatureSensor::getFeedValue() {
    return formattedValue;
}

string &TemperatureSensor::getFeedName() {
    return feedName;
}

void TemperatureSensor::updateTemperatureString() {
    std::ostringstream temperatureStringStream;
    temperatureStringStream << temperature;
    formattedValue = temperatureStringStream.str();
}

string &TemperatureSensor::getName() {
    return name;
}

string &TemperatureSensor::getFormattedValue() {
    return formattedValue;
}
