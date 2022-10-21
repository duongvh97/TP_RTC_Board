#include "serial_command.h"

void SerialCommand::getSerialCommand()
{
    while (Serial.available() > 0)
    {
        char temp = Serial.read();
        countByte++;
        if (countByte > 2 && countByte < 13)
        {
            stringData += temp;
        }
        if (countByte >= 13)
            countByte = 0;

        switch (state)
        {
        case WAITING_START_BYTE:
            if (temp == START_BYTE)
            {
                state = WAITING_RECEIVE_DATA_BYTE;
            }
            break;

        case WAITING_RECEIVE_DATA_BYTE:
            if (temp == STOP_BYTE)
            {
                state = WAITING_STOP_BYTE;
                break;
            }
            buffer = temp;
            state = WAITING_STOP_BYTE;
            break;

        case WAITING_STOP_BYTE:
            if (temp == STOP_BYTE)
            {
                state = WAITING_START_BYTE;
                receiveDataDone = true;
            }
            break;
        }
    }
}

void SerialCommand::handleSerialCommand()
{
    if (receiveDataDone)
    {
        receiveDataDone = false;

        switch (buffer)
        {
        case CMD_RESET_PWR_USB:
            Serial.println("Reset PWR USB");
            GpioController::getInstance()->resetUSBRelay();
            countByte = 0;
            buffer = 0;
            stringData = "";
            break;
        case CMD_SET_CURRENT_TIME:
            RtcDs1307::getInstance()->setCurrentEpochTime(atoi(stringData.c_str()));
            Serial.print("Device response-> Set epoch time sucess: ");
            Serial.println(atoi(stringData.c_str()));
            stringData = "";
            buffer = 0;
            break;
        case CMD_GET_EPOCH_TIME:
            countByte = 0;
            buffer = 0;
            stringData = "";
            Serial.print(RtcDs1307::getInstance()->getCurrentEpochTime());
            break;
        default:
            break;
        }
    }
}

void SerialCommand::serialHandler()
{
    getSerialCommand();
    handleSerialCommand();
}

void SerialCommand::initSerial()
{
    Serial.begin(SERIAL_BAUD);
}