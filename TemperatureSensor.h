//
// Created by martin.maliska on 9/14/2019.
//

#ifndef HOMEPI_TEMPERATURESENSOR_H
#define HOMEPI_TEMPERATURESENSOR_H

#include <string>
#include "MQTTFeedAware.h"
#include "Sensor.h"

using namespace std;

class TemperatureSensor : public MQTTFeedAware, public Sensor {

private:
    string address;
    string feedName;
    string name;
    bool found{};
    double temperature;
    string formattedValue;
    void updateTemperatureString();
public:
    TemperatureSensor(string address, string feedName, string name);

    bool isFound() const;

    double getTemperature() const;

    string & getFeedValue() override;

    string & getFeedName() override;

    string &getName() override;

    string &getFormattedValue() override;

    void read() override;
};


#endif //HOMEPI_TEMPERATURESENSOR_H
