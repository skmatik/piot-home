//
// Created by martin.maliska on 9/29/2019.
//

#ifndef HOMEPI_MQTTFEEDAWARE_H
#define HOMEPI_MQTTFEEDAWARE_H

#include "3party/MQTTClient.h"
#include <string>

using namespace std;

class MQTTFeedAware {
public:
    virtual string getFeedValue() = 0;
    virtual string getFeedName() = 0;
};


#endif //HOMEPI_MQTTFEEDAWARE_H
