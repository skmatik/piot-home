//
// Created by martin.maliska on 9/29/2019.
//

#include <cstring>
#include <wiringPi.h>
#include <iostream>
#include <utility>
#include "MQTTPublisher.h"
#include "config.h"

void MQTTPublisher::connect() {

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    cout << "Connecting to MQTT" << endl;
    MQTTClient_create(&client, ADDRESS, CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    conn_opts.keepAliveInterval = KEEP_ALIVE_IN_SECONDS;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        cout << "Failed to connect, return code: " << rc << endl;
        exit(EXIT_FAILURE);
    }
}

int MQTTPublisher::publish() {
    if (!MQTTClient_isConnected(client)) {
        disconnect();
        connect();
    }
    cout << "Publishing MQTT" << endl;
    MQTTClient_deliveryToken token;
    for (auto &feedAware: messageBuilders) {
        MQTTClient_message message = MQTTClient_message_initializer;
        const char *value = feedAware->getFeedValue().c_str();
        message.payload = (void *) value;
        message.payloadlen = (int) strlen(value);
        message.qos = QOS;
        message.retained = 0;
        string feedTopic = string(FEED_PREFIX).append(feedAware->getFeedName());
        int rc;
        cout << "publishing: " << value << " to feed: " << feedTopic << endl;
        if ((rc = MQTTClient_publishMessage(client, feedTopic.c_str(), &message, &token)) != MQTTCLIENT_SUCCESS) {
            cout << "Failed to publish message, return code: " << rc << endl;
        }
        if ((rc= MQTTClient_waitForCompletion(client, token, TIMEOUT)) != MQTTCLIENT_SUCCESS) {
            cout << "Failed to wait for completion, return code: " << rc << endl;
        }
    }
    return 0;
}

void MQTTPublisher::disconnect() {
    cout << "Disconnecting MQTT" << endl;
    MQTTClient_disconnect(client, TIMEOUT);
}

MQTTPublisher::~MQTTPublisher() {
    MQTTClient_destroy(&client);
}

void MQTTPublisher::operator()() {
    unsigned int nextTime = millis() + INTERVAL;
    publish();
    while (true) {
        if (millis() >= nextTime) {
            nextTime = millis() + INTERVAL;
            publish();
        }
    }

}

MQTTPublisher::MQTTPublisher(const vector<MQTTFeedAware *> & messageBuilders) : messageBuilders(messageBuilders), client() {}
