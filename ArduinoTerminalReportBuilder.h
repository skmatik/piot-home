//
// Created by martin.maliska on 9/22/2019.
//

#ifndef HOMEPI_ARDUINOTERMINALREPORTBUILDER_H
#define HOMEPI_ARDUINOTERMINALREPORTBUILDER_H


#include "ReportBuilder.h"
#include "TemperatureSensor.h"
#include <vector>
#include <string>

using namespace std;

class ArduinoTerminalReportBuilder: public ReportBuilder {

public:
    explicit ArduinoTerminalReportBuilder(vector<Sensor*>  *sensors);

    vector<string> build() override;

private:
    vector<Sensor *> *sensors;
};


#endif //HOMEPI_ARDUINOTERMINALREPORTBUILDER_H
