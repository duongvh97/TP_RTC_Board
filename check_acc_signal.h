#ifndef CHECK_ACC_SIGNAL_H
#define CHECK_ACC_SIGNAL_H

#include "gpio_controller.h"
#include <Ticker.h>

void callBackFunc();
void check_acc();

class CheckAccSignal
{
private:
    Ticker m_ticker_1;
    Ticker m_ticker_2;

    bool mTickerIsRunning;
    bool isHaveAccSignal;
    bool isStarted;
    bool isTurnOnAccRelay;
    uint8_t _count;
    bool isDetachTicker;

public:
    static CheckAccSignal* getInstance()
    {
        static CheckAccSignal obj;
        return &obj;
    }
    CheckAccSignal()
    {
        isHaveAccSignal = false;
        mTickerIsRunning = false;
        isStarted = false;
        isDetachTicker = false;
        bool isTurnOnAccRelay = false;
        _count = 0;
        m_ticker_2.attach(TIME_TO_CHECK_ACC, check_acc);
    }
    void checkAcc();
    void checkAccSignalWhenStartup();
};


#endif