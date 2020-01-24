
#ifndef HOMEPI_REMOTESENSOR_H
#define HOMEPI_REMOTESENSOR_H


#include "Sensor.h"
#include "MQTTFeedAware.h"

class RemoteSensor : public Sensor, MQTTFeedAware {
    string feedName;
    string name;
    bool found;
    double temperature;
    string formattedValue;
public:
    RemoteSensor(string feedName, string name);

    bool isFound() override;

    double getTemperature() const;

    string & getFeedValue() override;

    string & getFeedName() override;

    string &getName() override;

    string &getFormattedValue() override;

    void read() override;

    void updateTemperatureString(string & newValue);
};


#endif //HOMEPI_REMOTESENSOR_H
