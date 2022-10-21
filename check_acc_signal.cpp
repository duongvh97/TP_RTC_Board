#include "check_acc_signal.h"

void CheckAccSignal::checkAcc()
{
    if(GpioController::getInstance()->readAccSignal() == false)
    {
        _count++;
        if(_count == 3)
        {
            _count = 0;
            isHaveAccSignal = true;
            isStarted = true;
        }
    }
    else
    {
        isHaveAccSignal = false;
    }
    //if have ACC signal fisrt after lost ACC signal
    // Will delay a some seconds then turn of ACC relay
    if(!isHaveAccSignal && isStarted)
    {
        if(!mTickerIsRunning)
        {
            m_ticker_1.attach(DELAY_TURN_OFF_ACC, callBackFunc);
            isTurnOnAccRelay = false;
            isStarted = false;
            mTickerIsRunning = true;
            isDetachTicker = false;
        }
    }

    if(isHaveAccSignal)
    {
        if(!isTurnOnAccRelay)
        {
            GpioController::getInstance()->turnOnAccRelay();
            mTickerIsRunning = false;
            isTurnOnAccRelay = true;
        }
    }

    if(GpioController::getInstance()->getRelayACCState() == false && isDetachTicker == false)
    {
        m_ticker_1.detach();
        isDetachTicker = true;
    }
}

void callBackFunc()
{
    GpioController::getInstance()->turnOffAccRelay();
    GpioController::getInstance()->turnOffUSBRelay();
    GpioController::getInstance()->setRelayACC(false);
}

void check_acc()
{
    CheckAccSignal::getInstance()->checkAcc();
}

void CheckAccSignal::checkAccSignalWhenStartup()
{
    if(GpioController::getInstance()->readAccSignal() == false)
    {
        delay(500);
        if(GpioController::getInstance()->readAccSignal() == false)
        {
            GpioController::getInstance()->turnOnAccRelay();
            GpioController::getInstance()->turnOnUSBRelay();
        }
    }
}