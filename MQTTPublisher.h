//
// Created by martin.maliska on 9/29/2019.
//

#ifndef HOMEPI_MQTTPUBLISHER_H
#define HOMEPI_MQTTPUBLISHER_H

#include <string>
#include <vector>
#include "3party/MQTTClient.h"
#include "TimeConstants.h"
#include "MQTTFeedAware.h"
#include "Sensor.h"

using namespace std;


class MQTTPublisher {

private:
    constexpr static const char *const CLIENT_ID = "Home PI";
    constexpr static const char *const FEED_PREFIX = "skmatik/feeds/";
    static const int QOS = 1;
    static const long TIMEOUT = 10000L;
    constexpr static const char *const ADDRESS = "tcp://io.adafruit.com:1883";
    static const long INTERVAL = 5 * ONE_MINUTE_IN_SECONDS * ONE_SECOND_IN_MILLISECONDS;
    static const int KEEP_ALIVE_IN_SECONDS = 20;

    MQTTClient client;
    vector<Sensor *> *sensors;
public:
    MQTTPublisher(vector<Sensor *> *sensors);

    bool connect();
    int publish();
    void disconnect();
    void operator()();
    virtual ~MQTTPublisher();
};


#endif //HOMEPI_MQTTPUBLISHER_H
