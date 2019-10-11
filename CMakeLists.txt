cmake_minimum_required(VERSION 3.13)
project(homepi)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_library(wiringPi_LIB wiringPi)
find_library(PAHO_C_LIB paho-mqtt3c)
add_executable(homepi main.cpp RotaryEncoder.cpp RotaryEncoder.hpp lcdDriver.cpp i2cControl.cpp Menu.cpp Menu.h
        TemperatureSensor.cpp TemperatureSensor.h SerialCommunicator.cpp SerialCommunicator.h ReportBuilder.h
        ArduinoTerminalReportBuilder.cpp ArduinoTerminalReportBuilder.h
        MQTTPublisher.cpp MQTTPublisher.h TimeConstants.h MQTTFeedAware.h)
target_link_libraries(homepi ${wiringPi_LIB} Threads::Threads ${PAHO_C_LIB})

