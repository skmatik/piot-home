
#include <sstream>
#include <iomanip>
#include "TemperatureFormatter.h"

string TemperatureFormatter::format(double temperature) {
    std::ostringstream temperatureStringStream;
    temperatureStringStream << std::setprecision(2);
    temperatureStringStream << std::fixed;
    temperatureStringStream << temperature;
    temperatureStringStream << " C";
    return temperatureStringStream.str();
}
