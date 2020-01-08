#include <fstream>
#include <sstream>
#include <iostream>
#include "CpuTemperatureSensor.h"

string &CpuTemperatureSensor::getName() {
    return name;
}

string &CpuTemperatureSensor::getFormattedValue() {
    return formattedValue;
}

void CpuTemperatureSensor::read() {
    ifstream sensorFile;
    ;
    sensorFile.open(sensorPath.c_str());
    if (sensorFile) {
        found = true;
        string encodedTemperature;
        stringstream buffer;
        buffer << sensorFile.rdbuf();
        encodedTemperature = buffer.str();
        sensorFile.close();
        temperature = stod(encodedTemperature) / 1000;
        updateTemperatureString();
    }
}

void CpuTemperatureSensor::updateTemperatureString() {
    std::ostringstream temperatureStringStream;
    temperatureStringStream << temperature;
    formattedValue = temperatureStringStream.str();
    cout << " CPU temp: " << formattedValue << endl;
}

bool CpuTemperatureSensor::isFound() {
    return found;
}

CpuTemperatureSensor::CpuTemperatureSensor() : formattedValue("0.0"), found(false), temperature(0) {}
