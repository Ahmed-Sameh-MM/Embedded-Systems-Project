
#include "variables.h"

// polling delay
void delay_t(int msec){
  int cnt = 0;
  while(cnt<=msec*3100){cnt++;};
}

// Seconds to MM:SS format
int get_seconds(){
  return (seconds_1 + (seconds_2 * 10) + (minutes_1 * 60) + (minutes_2 *600));
}

// MM:SS format to Seconds
void seconds_to_format(int seconds){
  int min = seconds/60;
  int sec = (seconds - (min*60));
  if(min < 10){
    minutes_1 = min;
    minutes_2 = 0;
  }
  else{
    minutes_1 = min%10;
    minutes_2 = (min/10)%10;
  }
  if(sec < 10){
    seconds_1 = sec;
    seconds_2 = 0;
  }
  else{
    seconds_1 = sec%10;
    seconds_2 = (sec/10)%10;
  }
}

// Start Timer One shot with 1 seconds
void Timerdelay() {
  TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 16000000 - 1);
  TimerEnable(TIMER0_BASE, TIMER_BOTH);
}

// Timer Input
void GetTimerInput(){
  char temp = keypad_read();
  if(temp != ' '){
    if(temp == 'D'){
        TimerTime = get_seconds();
        Timerdelay();
        printFlag = true;
        return;
    }
    if(digit_place == '0'){digit_place = '1'; seconds_1 = (temp - '0');printFlag = true;}
    else if(digit_place == '1'){digit_place = '2'; seconds_2 = (temp - '0');printFlag = true;}
    else if(digit_place == '2'){digit_place = '3'; minutes_1 = (temp - '0');printFlag = true;}
    else if(digit_place == '3'){digit_place = '0'; minutes_2 = (temp - '0');printFlag = true;}
  }
}

// Timer One shot Timeout Function
void toggle_Buzzer(){
  if(TimerTime > 0){
    TimerIntClear(TIMER0_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT));
    TimerTime--;
    seconds_to_format(TimerTime);
    Timerdelay();
  }
  else{
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning on the buzzer
    delay_t(250);
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning off the buzzer
    delay_t(250);
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning oon the buzzer
    delay_t(250);
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning off the buzzer
    delay_t(250);
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning on the buzzer
    delay_t(250);
    Toggle_Bit(GPIO_PORTE_DATA_R, 1); // turning off the buzzer
    TimerIntClear(TIMER0_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT)); // clearing the interrupt of Timer 0
    TimerTime = 0;
    minutes_1 = 0;
    minutes_2 = 0;
    seconds_1 = 0;
    seconds_2 = 0;
    digit_place= '0';
  }
  printFlag = true;
}

void timerInit() {
  //Timer 0 Setup
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
  TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
  
  //Enabling Timer 0 Interrupts
  TimerIntEnable(TIMER0_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT));
  TimerIntRegister(TIMER0_BASE, TIMER_BOTH, toggle_Buzzer);
}