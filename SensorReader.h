//
// Created by martin.maliska on 11/8/2019.
//

#ifndef HOMEPI_SENSORREADER_H
#define HOMEPI_SENSORREADER_H


#include "Sensor.h"
#include "TimeConstants.h"
#include <vector>
using namespace std;


class SensorReader {

private:
    static const long INTERVAL = 5 *  ONE_SECOND_IN_MILLISECONDS;
    vector<Sensor *> * sensors;
    void readAllSensors() const;

public:
    void operator()();

    explicit SensorReader(vector<Sensor *> * sensors);

};


#endif //HOMEPI_SENSORREADER_H
