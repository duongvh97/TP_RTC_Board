#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#define DELAY_TURN_OFF_ACC 5 //5s
#define TIME_TO_CHECK_ACC 0.5 //0.5s

#define PWR_USB_RELAY_PIN 12
#define ACC_RELAY_PIN 14
#define ACC_SIGNAL_PIN 13
#define LED_PIN 2

#define ON 1
#define OFF 0

#define CMD_RESET_PWR_USB 'D'
#define CMD_GET_EPOCH_TIME 'E'
#define CMD_SET_CURRENT_TIME 'F'

#define START_BYTE 'A'
#define STOP_BYTE 'B'

#define DEBUG
#define SERIAL_BAUD 115200

enum SERIAL_STATE {
  WAITING_START_BYTE = 0,
  WAITING_RECEIVE_DATA_BYTE,
  WAITING_STOP_BYTE
};

#endif
