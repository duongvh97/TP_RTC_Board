#include "gpio_controller.h"

void GpioController::turnOnAccRelay()
{
    digitalWrite(ACC_RELAY_PIN, 1);
    relayACCState = true;
    turnOnUSBRelay();
}

void GpioController::turnOffAccRelay()
{
    digitalWrite(ACC_RELAY_PIN, 0);
    relayACCState = false;
    turnOffUSBRelay();
}

void GpioController::turnOnUSBRelay()
{
    digitalWrite(PWR_USB_RELAY_PIN, 1);
    relayUSBState = true;
}

void GpioController::turnOffUSBRelay()
{
    digitalWrite(PWR_USB_RELAY_PIN, 0);
    relayUSBState = false;
}

bool GpioController::getRelayACCState()
{
    return relayACCState;
}

bool GpioController::readAccSignal()
{
    if (digitalRead(ACC_SIGNAL_PIN) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GpioController::resetUSBRelay()
{
    if(relayUSBState)
    {
        turnOffUSBRelay();
        delay(1000);
        turnOnUSBRelay();
    }
    else
    {
        turnOnUSBRelay();
        delay(1000);
        turnOffUSBRelay();
    }
}

void GpioController::initGpio()
{
    pinMode(PWR_USB_RELAY_PIN, OUTPUT);
    pinMode(ACC_RELAY_PIN, OUTPUT);
    pinMode(ACC_SIGNAL_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(PWR_USB_RELAY_PIN, 0);
    digitalWrite(ACC_RELAY_PIN, 0);
    m_ticker.attach(1, blinkLed);
}

void GpioController::setRelayACC(bool state)
{
    if (relayACCState != state)
    {
        relayACCState = state;
    }
}

void blinkLed()
{
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
