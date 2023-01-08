
#include "variables.h"

// Stopwatch Input
void GetStopWatchInput(){
  char input = keypad_read();
  if(input == ' '){return;}
  if (input == 'A'){
    TimerLoadSet(TIMER1_BASE, TIMER_BOTH, 16000000 - 1); // loading 1 second into Timer 1
    TimerEnable(TIMER1_BASE, TIMER_BOTH); // enabling Timer 1 to start counting
    printFlag = true;
  }
  else if (input == 'B'){
    TimerDisable(TIMER1_BASE, TIMER_BOTH); // disabling Timer 1 (pausing the counting of the stopwatch)
    printFlag = true;
  }
  else if (input == 'C'){
    // clearing the digits (reseting the stopwatch)
    minutes_1 = 0;
    minutes_2 = 0;
    seconds_1 = 0;
    seconds_2 = 0;

    TimerDisable(TIMER1_BASE, TIMER_BOTH); // disabling Timer 1 (pausing the counting of the stopwatch)
    printFlag = true;
  }
}

// Stopwatch Timeout Function
void toggle_StopWatch(){
  if(seconds_1 <= 9){
    seconds_1++;
    if ( seconds_1 == 10){
      seconds_1 = 0;
      seconds_2++;
      if ( seconds_2 == 6){
        minutes_1++;
        seconds_2 = 0;
        if ( minutes_1 == 10){
          minutes_1 = 0;
          minutes_2++;
          if ( minutes_2 == 6){
           minutes_2 = 0;
          }
        }
      }
    }
  }
  printFlag = true;
  TimerIntClear(TIMER1_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT));
}

void stopwatchInit() {
  //Timer 1 Setup
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  
  //Enabling Timer 1 Interrupts
  TimerIntEnable(TIMER1_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT));
  TimerIntRegister(TIMER1_BASE, TIMER_BOTH, toggle_StopWatch);
}