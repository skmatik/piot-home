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

using namespace std;

static const char *const CLIENT_ID = "Home PI";
static const char *const FEED_PREFIX = "skmatik/feeds/";
static const char *const PAYLOAD = "22.33";
static const int QOS = 1;
static const long TIMEOUT = 10000L;
static const char *const ADDRESS = "tcp://io.adafruit.com:1883";
static const long INTERVAL = 5 * ONE_MINUTE_IN_SECONDS * ONE_SECOND_IN_MILLISECONDS;

static const int KEEP_ALIVE_IN_SECONDS = 20;

class MQTTPublisher {

private:
    MQTTClient client;
    vector<MQTTFeedAware *> messageBuilders;
public:
    MQTTPublisher(const vector<MQTTFeedAware *> & messageBuilders);

    void connect();
    int publish();
    void disconnect();
    void operator()();
    virtual ~MQTTPublisher();
};


#endif //HOMEPI_MQTTPUBLISHER_H
