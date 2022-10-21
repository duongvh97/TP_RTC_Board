#ifndef RTC_DS1307_H
#define RTC_DS1307_H

#include "RTClib.h"
#include "common.h"

class RtcDs1307
{
private:
    uint32_t epochTime;
    DateTime m_dateTime;
    RTC_DS1307 m_rtc;
public:
    static RtcDs1307* getInstance()
    {
        static RtcDs1307 obj;
        return &obj;
    }
    RtcDs1307()
    {
        initRTC();
    }
    void initRTC();
    uint32_t getCurrentEpochTime();
    void setCurrentEpochTime(uint32_t epoch);  
};

#endif