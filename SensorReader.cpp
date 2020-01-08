#include <wiringPi.h>
#include <iostream>
#include "SensorReader.h"

SensorReader::SensorReader(vector<Sensor *> *sensors) : sensors(sensors) {}

void SensorReader::operator()() {
    unsigned int nextTime = millis() + INTERVAL;
    readAllSensors();
    while (true) {
        if (millis() >= nextTime) {
            nextTime = millis() + INTERVAL;
            readAllSensors();
        }
    }

}

void SensorReader::readAllSensors() const {
    std::cout << "Reading all sensors!" << endl;
    std::cout.flush();
    for (Sensor *sensor: * sensors) {
        sensor->read();
    }
}
