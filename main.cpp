#include <iostream>
#include <sys/utsname.h>
#include "RotaryEncoder.hpp"
#include "Menu.h"
#include "i2cControl.hpp"
#include "lcdDriver.hpp"
#include "TemperatureSensor.h"
#include <atomic>
#include <thread>
#include "SerialCommunicator.h"
#include "ArduinoTerminalReportBuilder.h"
#include "MQTTPublisher.h"
#include "MQTTFeedAware.h"

#define lcdAdd 0x3f // I2C device address

int main() {
    auto *i2c = new I2cControl(0);
    auto *lcd = new LcdDriver((char) lcdAdd, i2c);
    lcd->lcdSendCommand(LCD_BEG_LINE_1);

    struct utsname name{};
    if (uname(&name)) {
        exit(-1);
    }
    std::cout << name.sysname << " " << name.release << "\n";
    auto rotaryEncoder = RotaryEncoder();

    vector<string> items = {"item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9"};
    auto *menu = new Menu(items, 4, lcd);

    menu->printMenu();
    TemperatureSensor temperatureSensor("28-011591ac3fff");
    temperatureSensor.readCurrentValue();
    cout << "Found: " << temperatureSensor.isFound() << " temp: " << temperatureSensor.getTemperature();
    cout.flush();

    atomic_bool ab;
    cout << "\n AB lock free: " << ab.is_lock_free() << "\n";
    cout.flush();

    ArduinoTerminalReportBuilder reportBuilder = ArduinoTerminalReportBuilder();
    thread serialCommunicatorThread((SerialCommunicator(reportBuilder)));
    vector<MQTTFeedAware *> feedAware = vector<MQTTFeedAware *>();
    feedAware.push_back(&temperatureSensor);
    thread mqttPublisher((MQTTPublisher(feedAware)));

    while (true) {
        if (rotaryEncoder.triggered()) {
            std::cout << "Switch: " << rotaryEncoder.getSwitched();
            std::cout << " Direction: " << rotaryEncoder.getDirection();
            std::cout << " Counter: " << rotaryEncoder.getCounter();
            std::cout << " item: " << menu->getCurrentItemIndex();
            rotaryEncoder.resetSwitch();
            if (rotaryEncoder.getDirection() == Direction::LEFT) {
                menu->previous();
                menu->printMenu();
            } else if (rotaryEncoder.getDirection() == Direction::RIGHT) {
                menu->next();
                menu->printMenu();
            }
            std::cout.flush();
            std::cout << "\n";
        }
    }
    return 0;
}


