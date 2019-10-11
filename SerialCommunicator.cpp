//
// Created by martin.maliska on 9/21/2019.
//

#include <cstring>
#include <iostream>
#include "SerialCommunicator.h"

SerialCommunicator::SerialCommunicator(ReportBuilder &reportBuilder) : reportBuilder(reportBuilder) {
}

void SerialCommunicator::operator()() {
    if (setupCommunication()) {
        while (true) {
            if (readCommand()) {
                cout << "Serial: " << command << endl;
                if (command == "get$") {
                    writeResponse();
                }
            }
        }
    } else {

    }

}

bool SerialCommunicator::setupCommunication() {
    bool result = true;
    if ((serialPortFileDescriptor = serialOpen(SERIAL_DEVICE, SPEED)) < 0) {
        cerr << "Unable to open serial device: " << strerror(errno) << endl;
        result = false;
    }

    if (wiringPiSetup() == -1) {
        cerr << "Unable to start wiringPi: " << strerror(errno) << endl;
        result = false;
    }
    cout << "Serial: initialized" << endl;
    return result;
}

bool SerialCommunicator::readCommand() {
    string text;
    while (serialDataAvail(serialPortFileDescriptor)) {
        int c = serialGetchar(serialPortFileDescriptor);
        text.push_back(c);
    }
    command = text;
    return !command.empty();
}

void SerialCommunicator::writeResponse() {
    const vector<string> report = reportBuilder.build();
    for (const auto& line: report) {
        serialPuts(serialPortFileDescriptor, line.c_str());
        serialPutchar(serialPortFileDescriptor, '$');
    }
    serialPutchar(serialPortFileDescriptor, '@');
    serialFlush(serialPortFileDescriptor);
    cout << "Serial: response send" << endl;
}
