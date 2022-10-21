#ifndef SERIAL_COMMAND_H
#define SERIAL_COMMAND_H

#include "common.h"
#include <iostream>
#include "rtc_ds1307.h"
#include "gpio_controller.h"

class SerialCommand
{
private:
    uint8_t countByte;
    SERIAL_STATE state = WAITING_START_BYTE;
    std::string stringData;
    bool receiveDataDone;
    char buffer;

public:
    static SerialCommand* getInstance()
    {
        static SerialCommand obj;
        return &obj;
    }
    void getSerialCommand();
    void handleSerialCommand();
    void serialHandler();
    void initSerial();
};

#endif