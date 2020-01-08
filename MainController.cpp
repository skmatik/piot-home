#include <iostream>
#include "MainController.h"
#include "TemperatureSensor.h"
#include "SensorReader.h"
#include "StringMenuItem.h"
#include "ArduinoTerminalReportBuilder.h"
#include "SerialCommunicator.h"
#include "MQTTPublisher.h"
#include "SensorMenuItem.h"
#include "CpuTemperatureSensor.h"

void MainController::execute() {
    unsigned int nextTime = millis() + MENU_REFRESH_INTERVAL_IN_MILLIS;
    menu->printMenu();
    do {
        if (millis() >= nextTime) {
            nextTime = millis() + MENU_REFRESH_INTERVAL_IN_MILLIS;
            menu->printMenu();
        }

        if (rotaryEncoder->triggered()) {
            std::cout << "Switch: " << rotaryEncoder->getSwitched();
            std::cout << " Direction: " << rotaryEncoder->getDirection();
            std::cout << " Counter: " << rotaryEncoder->getCounter();
            std::cout << " item: " << menu->getCurrentItemIndex();
            rotaryEncoder->resetSwitch();
            if (rotaryEncoder->getDirection() == Direction::LEFT) {
                menu->previous();
                menu->printMenu();
            } else if (rotaryEncoder->getDirection() == Direction::RIGHT) {
                menu->next();
                menu->printMenu();
            }
            std::cout.flush();
            std::cout << "\n";
        }
    } while (!stopped);

}

MainController::MainController() {
    stopped = false;
    this->rotaryEncoder = new RotaryEncoder();
    sensors = initializeSensors();
    sensorReader = new SensorReader(sensors);
    sensorsReaderThread = new thread((*sensorReader));
    menu = initializeMenu(sensors);
    mqttPublisher = new MQTTPublisher(sensors);
    mqttPublisherThread = new thread((*mqttPublisher));
    reportBuilder = new ArduinoTerminalReportBuilder(sensors);
    serialCommunicator = new SerialCommunicator(reportBuilder);
    serialCommunicatorThread = new thread((*serialCommunicator));
}

MainController::~MainController() {
    delete (serialCommunicatorThread);
    delete (serialCommunicator);
    delete (reportBuilder);
    delete (mqttPublisherThread);
    delete (mqttPublisher);
    delete (menu);
    delete (rotaryEncoder);
    delete (sensorsReaderThread);
    delete (sensorReader);
    sensors->clear();
    delete (sensors);
}

vector<Sensor *> *MainController::initializeSensors() {
    auto *sensorList = new vector<Sensor *>();

    sensorList->push_back(new TemperatureSensor("28-0000062718bd", "kotol", "Kotol"));
    sensorList->push_back(new TemperatureSensor("28-000006083434", "bojler", "Bojler"));
    sensorList->push_back(new TemperatureSensor("28-00000607fcab", "spiatocka", "Spiatocka"));
    sensorList->push_back(new CpuTemperatureSensor());
    return sensorList;
}

LcdMenu *MainController::initializeMenu(vector<Sensor *> *sensorsToAddToMenu) {
    auto *menuItems = new vector<LcdMenuItem *>();
    for (Sensor *sensor : *sensorsToAddToMenu) {
        menuItems->push_back(new SensorMenuItem(sensor));
    }
    menuItems->push_back(new StringMenuItem("item0"));
    menuItems->push_back(new StringMenuItem("item1"));
    menuItems->push_back(new StringMenuItem("item2"));
    menuItems->push_back(new StringMenuItem("item3"));
    menuItems->push_back(new StringMenuItem("item4"));
    menuItems->push_back(new StringMenuItem("item5"));
    menuItems->push_back(new StringMenuItem("item6"));
    menuItems->push_back(new StringMenuItem("item7"));
    menuItems->push_back(new StringMenuItem("item8"));
    return new LcdMenu(menuItems, 4);
}

void MainController::join() {
    cout << "controller join" << endl;
    cout.flush();
    sensorsReaderThread->join();
    cout << "sensorsReaderThread join" << endl;
    cout.flush();
    mqttPublisherThread->join();
    cout << "mqttPublisherThread join" << endl;
    cout.flush();
    serialCommunicatorThread->join();
    cout << "serialCommunicatorThread join" << endl;
    cout.flush();
}
