#include <ostream>
#include "RotaryEncoder.hpp"
#include <map>

volatile bool RotaryEncoder::switched;
volatile bool RotaryEncoder::firstPin;
volatile bool RotaryEncoder::secondPin;
volatile bool RotaryEncoder::changed;
volatile bool RotaryEncoder::inStep;
volatile Direction RotaryEncoder::direction = Direction::UNKNOWN;

RotaryEncoder::RotaryEncoder() {
    wiringPiSetup();
    pinMode(SWITCH_PIN, INPUT);
    pinMode(DATA_PIN, INPUT);
    pinMode(CLOCK_PIN, INPUT);
    pullUpDnControl(SWITCH_PIN, PUD_UP);
    pullUpDnControl(DATA_PIN, PUD_UP);
    pullUpDnControl(CLOCK_PIN, PUD_UP);
    wiringPiISR(SWITCH_PIN, INT_EDGE_FALLING, RotaryEncoder::switchInterrupt);
    wiringPiISR(DATA_PIN, INT_EDGE_BOTH, RotaryEncoder::encoderInterrupt);
    wiringPiISR(CLOCK_PIN, INT_EDGE_BOTH, RotaryEncoder::encoderInterrupt);
};

void RotaryEncoder::encoderInterrupt() {
    firstPin = digitalRead(DATA_PIN);
    secondPin = digitalRead(CLOCK_PIN);
    if (!secondPin) {
        if (!inStep) {
            direction = firstPin ? Direction::LEFT : Direction::RIGHT;
            inStep = true;
            if (Direction::LEFT == direction) {
                counter--;
            } else {
                counter++;
            }
        }
    } else {
        if (firstPin) {
            inStep = false;
            changed = true;
        }
    }
}

void RotaryEncoder::switchInterrupt() {
    switched = true;
    changed = true;
    direction = Direction::UNKNOWN;
}

bool RotaryEncoder::triggered() {
    return changed;
}

void RotaryEncoder::resetSwitch() {
    switched = false;
    changed = false;
}

volatile bool RotaryEncoder::getSwitched() {
    return switched;
}

volatile Direction RotaryEncoder::getDirection() {
    return direction;
}

std::ostream& operator << (std::ostream& os, const Direction direction)
{
    switch(direction){
        case Direction::LEFT: os << "left";
            break;
        case Direction::RIGHT: os << "right";
            break;
        case Direction::UNKNOWN: os << "unknown";
            break;
        default:
            os.setstate(std::ios_base::failbit);
    }
    return os;
}

volatile int RotaryEncoder::getCounter() {
    return counter;
}

volatile int RotaryEncoder::counter;
