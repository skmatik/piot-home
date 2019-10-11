#ifndef HOMEPI_ROTARYENCODER_HPP
#define HOMEPI_ROTARYENCODER_HPP
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <atomic>
#include <wiringPi.h>

#define CLOCK_PIN 5
#define DATA_PIN 4
#define SWITCH_PIN 1

enum class Direction{LEFT, RIGHT, UNKNOWN};

class RotaryEncoder
{
private:
    static volatile bool switched;
    static volatile bool firstPin;
    static volatile bool secondPin;
    static volatile bool changed;
    static volatile bool inStep;
    static volatile Direction direction;
    static volatile int counter;
public:
    RotaryEncoder();
    void static switchInterrupt();
    void static encoderInterrupt();
    bool triggered();
    void resetSwitch();

    static volatile bool getSwitched();

    static volatile Direction getDirection();

    static volatile int getCounter();

};

std::ostream& operator << (std::ostream& os, Direction direction);

#endif //HOMEPI_ROTARYENCODER_HPP
