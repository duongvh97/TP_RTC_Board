#ifndef GPIO_CONTROLLER_H
#define GPIO_CONTROLLER_H

#include "common.h"
#include <Ticker.h>
#include <Arduino.h>

class GpioController
{
private:
    bool relayACCState;
    bool relayUSBState;
    Ticker m_ticker;
public:
    static GpioController* getInstance()
    {
        static GpioController obj;
        return &obj;
    }
    GpioController()
    {
        relayACCState = false;
        relayUSBState = false;
        initGpio();
    }
    void initGpio();
    void turnOnAccRelay();
    void turnOffAccRelay();
    void turnOnUSBRelay();
    void turnOffUSBRelay();
    void resetUSBRelay();
    bool readAccSignal();

    bool getRelayACCState();
    void setRelayACC(bool state);
};

void blinkLed();
#endif