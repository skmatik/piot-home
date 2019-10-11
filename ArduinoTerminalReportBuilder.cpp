//
// Created by martin.maliska on 9/22/2019.
//

#include <sstream>
#include "ArduinoTerminalReportBuilder.h"

ArduinoTerminalReportBuilder::ArduinoTerminalReportBuilder(): counter(0) {}

vector<string> ArduinoTerminalReportBuilder::build() {
    vector<string> report = vector<string>();
    ostringstream reportLine;
    reportLine << "XResponse: " << counter++ << "$";
    report.push_back(reportLine.str());
    return report;
}
