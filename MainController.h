#ifndef HOMEPI_MAINCONTROLLER_H
#define HOMEPI_MAINCONTROLLER_H


#include "RotaryEncoder.hpp"
#include "LcdMenu.h"
#include "Sensor.h"
#include "MQTTPublisher.h"
#include "ArduinoTerminalReportBuilder.h"
#include "SensorReader.h"
#include "SerialCommunicator.h"
#include <vector>
#include <thread>

using namespace std;

class MainController {

private:
    RotaryEncoder *rotaryEncoder;
    LcdMenu *menu;
    bool stopped;
    vector<Sensor *> *sensors;
    thread *sensorsReaderThread;
    thread *mqttPublisherThread;
    thread *serialCommunicatorThread;
    ArduinoTerminalReportBuilder *reportBuilder;
    vector<Sensor *> * initializeSensors();
    LcdMenu * initializeMenu(vector<Sensor *> *sensors);
    SensorReader *sensorReader;
    MQTTPublisher *mqttPublisher;
    SerialCommunicator *serialCommunicator;
    static const long MENU_REFRESH_INTERVAL_IN_MILLIS = 5 * ONE_SECOND_IN_MILLISECONDS;

public:
    void execute();
    explicit MainController();
    virtual ~MainController();
    void join();
};


#endif //HOMEPI_MAINCONTROLLER_H
