//
// Created by martin.maliska on 9/22/2019.
//

#include <sstream>
#include <utility>
#include "ArduinoTerminalReportBuilder.h"

vector<string> ArduinoTerminalReportBuilder::build() {
    vector<string> report = vector<string>();
    for (int i = 0 ; i < sensors->size() ; i++) {
        string line = string(sensors->operator[](i)->getName());
        line.append("-");
        line.append(sensors->operator[](i)->getFormattedValue());
        report.push_back(line);
    }
    return report;
}

ArduinoTerminalReportBuilder::ArduinoTerminalReportBuilder(vector<Sensor *>  *sensors) : sensors(sensors) {}
