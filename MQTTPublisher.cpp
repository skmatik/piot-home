#include <cstring>
#include <wiringPi.h>
#include <iostream>
#include "MQTTPublisher.h"
#include "config.h"

void MQTTPublisher::connect() {

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    cout << "Connecting to MQTT" << endl;
    cout.flush();
    MQTTClient_create(&client, ADDRESS, CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    conn_opts.keepAliveInterval = KEEP_ALIVE_IN_SECONDS;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        cout << "Failed to connect, return code: " << rc << endl;
        cout.flush();
        exit(EXIT_FAILURE);
    }
}

int MQTTPublisher::publish() {
    cout << "Publishing MQTT" << endl;
    cout.flush();
    MQTTClient_deliveryToken token;
    for (Sensor *sensor: *sensors) {
        if (auto *feedAware = dynamic_cast<MQTTFeedAware *>(sensor)) {
            if (sensor->isFound()) {
                disconnect();
                connect();
                MQTTClient_message message = MQTTClient_message_initializer;
                const char *value = feedAware->getFeedValue().c_str();
                message.payload = (void *) value;
                message.payloadlen = (int) strlen(value);
                message.qos = QOS;
                message.retained = 0;
                string feedTopic = string(FEED_PREFIX).append(feedAware->getFeedName());
                int rc;
                cout << "publishing: " << value << " to feed: " << feedTopic << endl;
                cout.flush();
                if ((rc = MQTTClient_publishMessage(client, feedTopic.c_str(), &message, &token)) != MQTTCLIENT_SUCCESS) {
                    cout << "Failed to publish message, return code: " << rc << endl;
                    cout.flush();
                }
            }
        }
    }
    return 0;
}

void MQTTPublisher::disconnect() {
    cout << "Disconnecting MQTT" << endl;
    cout.flush();
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

MQTTPublisher::MQTTPublisher(vector<Sensor *> *sensors) : sensors(sensors), client() {}
