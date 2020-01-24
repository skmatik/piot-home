
#include "RemoteSensor.h"
#include "TemperatureFormatter.h"

#include <utility>
#include <sstream>


void RemoteSensor::updateTemperatureString(string &newValue) {
    istringstream is(newValue.substr(2));
    is >> temperature;
    formattedValue = TemperatureFormatter::format(temperature);
}

RemoteSensor::RemoteSensor(string feedName, string name) : feedName(std::move(feedName)), name(std::move(name)), found(false), temperature(0.0) {

}

bool RemoteSensor::isFound() {
    return found;
}

double RemoteSensor::getTemperature() const {
    return temperature;
}

string &RemoteSensor::getFeedValue() {
    return formattedValue;
}

string &RemoteSensor::getFeedName() {
    return feedName;
}

string &RemoteSensor::getName() {
    return name;
}

string &RemoteSensor::getFormattedValue() {
    return formattedValue;
}

void RemoteSensor::read() {
    // nothing to do
}




