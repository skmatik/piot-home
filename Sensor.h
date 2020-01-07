//
// Created by martin.maliska on 10/27/2019.
//

#ifndef HOMEPI_SENSOR_H
#define HOMEPI_SENSOR_H

#include <string>
using namespace std;

class Sensor {
public:
    virtual string & getName() = 0;
    virtual string & getFormattedValue() = 0;
    virtual void read() = 0;
};

#endif //HOMEPI_SENSOR_H
