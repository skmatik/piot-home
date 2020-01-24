#include "TemperatureSensor.h"
#include "TemperatureFormatter.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <iomanip>

using namespace std;

void TemperatureSensor::read() {

    ifstream sensorFile;

    sensorFile.open(sensorPath.c_str());
    if (sensorFile) {
        string encodedTemperature;
        stringstream buffer;
        buffer << sensorFile.rdbuf();
        encodedTemperature = buffer.str();
        sensorFile.close();
        encodedTemperature = encodedTemperature.substr(encodedTemperature.find("t=") + 2);
        temperature = stod(encodedTemperature) / 1000;
        updateTemperatureString();
        found = true;
    }
}

TemperatureSensor::TemperatureSensor(const string& address, string feedName, string name) : sensorPath("/sys/bus/w1/devices/" + address + "/w1_slave"),
                                                                                     found(false),
                                                                                     temperature(0),
                                                                                     feedName(std::move(feedName)),
                                                                                     formattedValue("0.0"),
                                                                                     name(std::move(name)) {
}

bool TemperatureSensor::isFound() {
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
    formattedValue = TemperatureFormatter::format(temperature);
}

string &TemperatureSensor::getName() {
    return name;
}

string &TemperatureSensor::getFormattedValue() {
    return formattedValue;
}
