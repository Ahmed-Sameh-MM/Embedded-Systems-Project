#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DIO.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "keypad.h"
#include "lcd.h"
#include "calculator.h"
#include "timer.h"
#include "stopwatch.h"

#include "inc/hw_memmap.h"

// the flag which if enabled, allows the LCD to print
extern bool printFlag;

// Calculator Variables
extern char opCode;
extern bool isOpEntered;
extern int x; // first operand
extern int y; // second operand
extern float z; // result
extern char calculator[25];

// Timer & Stopwatch Variables
extern int TimerTime;
extern int minutes_1;
extern int minutes_2;
extern int seconds_1;
extern int seconds_2;
extern char digit_place;
extern char stopwatch[6];
extern char timer[6];