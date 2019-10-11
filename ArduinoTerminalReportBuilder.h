//
// Created by martin.maliska on 9/22/2019.
//

#ifndef HOMEPI_ARDUINOTERMINALREPORTBUILDER_H
#define HOMEPI_ARDUINOTERMINALREPORTBUILDER_H


#include "ReportBuilder.h"
#include <vector>
#include <string>

using namespace std;

class ArduinoTerminalReportBuilder: public ReportBuilder {

public:
    ArduinoTerminalReportBuilder();
    vector<string> build() override;

private:
    int counter;
};


#endif //HOMEPI_ARDUINOTERMINALREPORTBUILDER_H
