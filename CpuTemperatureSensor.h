#ifndef HOMEPI_CPUTEMPERATURESENSOR_H
#define HOMEPI_CPUTEMPERATURESENSOR_H


#include "Sensor.h"

class CpuTemperatureSensor : public Sensor {
private:
    string name = "Rpi teplota";
    string formattedValue;
    bool found;
    double temperature;
    void updateTemperatureString();
    string sensorPath = "/sys/class/thermal/thermal_zone0/temp";

public:
    string &getName() override;

    string &getFormattedValue() override;

    void read() override;

    bool isFound() override;

    CpuTemperatureSensor();
};


#endif //HOMEPI_CPUTEMPERATURESENSOR_H
