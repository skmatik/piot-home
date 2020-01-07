//
// Created by martin.maliska on 9/21/2019.
//

#ifndef HOMEPI_SERIALCOMMUNICATOR_H
#define HOMEPI_SERIALCOMMUNICATOR_H

static const char *const SERIAL_DEVICE = "/dev/ttyAMA0";

static const int SPEED = 115200;

#include <wiringPi.h>
#include <wiringSerial.h>
#include <thread>
#include "ReportBuilder.h"
#include "TimeConstants.h"

using namespace std;

class SerialCommunicator {

private:
    int serialPortFileDescriptor{};
    string command;
    ReportBuilder *reportBuilder;

    bool setupCommunication();
    bool readCommand();
    void writeResponse();
public:
    explicit SerialCommunicator(ReportBuilder *reportBuilder);
    void operator()();

};


#endif //HOMEPI_SERIALCOMMUNICATOR_H
