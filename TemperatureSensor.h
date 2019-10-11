//
// Created by martin.maliska on 9/14/2019.
//

#ifndef HOMEPI_TEMPERATURESENSOR_H
#define HOMEPI_TEMPERATURESENSOR_H
static const char *const FEED_NAME = "room-temperature";

#include <string>
#include "MQTTFeedAware.h"

using namespace std;

class TemperatureSensor : public MQTTFeedAware {

private:
    string address;
    bool found{};
    double temperature;
    string getTemperatureAsString();
public:
    TemperatureSensor(const string &address);

    void readCurrentValue();

    bool isFound() const;

    double getTemperature() const;

    string getFeedValue() override;

    string getFeedName() override;
};


#endif //HOMEPI_TEMPERATURESENSOR_H
