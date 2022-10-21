#include "serial_command.h"
#include "check_acc_signal.h"

void printCurrentEpochTime();
Ticker m_ticker;

void setup()
{
  m_ticker.attach(1, printCurrentEpochTime);
  SerialCommand::getInstance()->initSerial();
  CheckAccSignal::getInstance()->checkAccSignalWhenStartup();
}

void loop()
{
  SerialCommand::getInstance()->serialHandler();
}

void printCurrentEpochTime()
{
  Serial.println(RtcDs1307::getInstance()->getCurrentEpochTime());
}