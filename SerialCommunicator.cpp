//
// Created by martin.maliska on 9/21/2019.
//

#include <cstring>
#include <iostream>
#include "SerialCommunicator.h"

SerialCommunicator::SerialCommunicator(ReportBuilder *reportBuilder, RemoteSensor *remoteSensor) : reportBuilder(reportBuilder), commandComplete(false), remoteSensor(remoteSensor) {
}

void SerialCommunicator::operator()() {
    if (setupCommunication()) {
        while (true) {
            if (readCommand()) {
                cout << "Serial: " << command << endl;
                if (command == "{S@") {
                    writeResponse();
                    commandComplete = false;
                    command.clear();
                } else if (command.substr(0, 2) == "}T") {
                    if (commandComplete) {
                        cout << " temp from arduino: " << command.substr(2) << endl;
                        cout.flush();
                        remoteSensor->updateTemperatureString(command);
                        commandComplete = false;
                        command.clear();
                    }
                } else {
                    commandComplete = false;
                    command.clear();
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
        if (c == '@') {
            commandComplete = true;
            break;
        }
    }
    command.append(text);
    return !command.empty();
}

void SerialCommunicator::writeResponse() {
    const vector<string> report = reportBuilder->build();
    for (const auto& line: report) {
        serialPuts(serialPortFileDescriptor, line.c_str());
        cout << line;
        serialPutchar(serialPortFileDescriptor, '$');
        cout << '$' << endl;
        serialFlush(serialPortFileDescriptor);
        delay(100);
    }
    serialPutchar(serialPortFileDescriptor, '@');
    cout << '@';
    serialFlush(serialPortFileDescriptor);
    cout << "Serial: response send" << endl;
}
