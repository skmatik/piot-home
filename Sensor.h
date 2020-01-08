#ifndef HOMEPI_SENSOR_H
#define HOMEPI_SENSOR_H

#include <string>
using namespace std;

class Sensor {
public:
    virtual string & getName() = 0;
    virtual string & getFormattedValue() = 0;
    virtual void read() = 0;
    virtual bool isFound() = 0;
};

#endif //HOMEPI_SENSOR_H
