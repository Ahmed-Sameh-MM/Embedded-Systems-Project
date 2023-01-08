#include "variables.h"

// current mode
int mode = 0;

// previous mode
int previousMode = 0;

// the flag which if enabled, allows the LCD to print
bool printFlag = true;

// polling delay
void delay(int msec){
  int cnt = 0;
  while(cnt<=msec*3100){cnt++;};
}

// welcome message
void welcome(){
    LCD_Print("Welcome!!", "We are Team-> 13");
    delay(150);
    LCD_Print("Welcome!!", "We are Team-> ");
    delay(150);
    LCD_Print("Welcome!!", "We are Team-> 13");
    delay(150);
    LCD_Print("Welcome!!", "We are Team-> ");
    delay(150);
    LCD_Print("Welcome!!", "We are Team-> 13");
    delay(250);
    LCD_Print("Welcome!!", "Enjoy <3");
    delay(250);
}

// Calculator Variables
char opCode = 'A';
bool isOpEntered = false;
int x = 0; // first operand
int y = 0; // second operand
float z = 0; // result
char calculator[25] = {NULL};

// Timer & Stopwatch Variables
int TimerTime = 0;
int minutes_1 = 0;
int minutes_2 = 0;
int seconds_1 = 0;
int seconds_2 = 0;
char digit_place = '0';
char stopwatch[6] = {NULL};
char timer[6] = {NULL};

// Change Input/Output Modes {0 : Stopwatch, 1 : Calculator, 2 : Timer}
void ChangeMode(){
   while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4) == 0);
   if(mode == 2){mode=0;} // reseting the mode to the first one (0)
   else{mode++;} // incrementing the current mode to the next one
   minutes_1 = 0;
   minutes_2 = 0;
   seconds_1 = 0;
   seconds_2 = 0;
   x=0;y=0;z=0;isOpEntered = false;opCode = 'A';
   TimerDisable(TIMER1_BASE, TIMER_BOTH); // disabling Timer 1 (pausing the counting of the stopwatch)
   TimerIntClear(TIMER1_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT));
   TimerIntClear(TIMER0_BASE, (TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT)); // clearing the interrupt of Timer 0
   TimerTime = 0;
   digit_place= '0';
   GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
}


int main() {
  //PORT F Setup
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

  //Enabling Timer 0 & 1 Interrupts
  timerInit();
  stopwatchInit();
  __asm("CPSIE I");

  //Red Led Setup
  //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
  
  //Button Setup
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
  GPIOIntRegister(GPIO_PORTF_BASE, ChangeMode);
  GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
  Set_Bit(GPIO_PORTF_PUR_R, 4);

  //KeyPad Setup
  keypad_init();

  //LCD Setup
  LCD4bits_Init();		 //Initialization of LCD
  LCD4bits_Cmd(0x01);	        //Clear the display
  LCD4bits_Cmd(0x80);           //Force the cursor to beginning of 1st line
  delayMs(500);			//delay 500 ms for LCD (MCU is faster than LCD)

  //Welcome
  welcome();

  while(1){
    if(mode != previousMode) {
      printFlag = true;
      previousMode = mode;
    }
    if(mode == 0){
      GetCalculatorInput();
      if(printFlag){
        if(calculator[0])LCD_Print("Calculator:", calculator);
        else LCD_Print("Calculator:", "....................");
        printFlag=false;
      }
    }
    else if(mode == 1){
      GetTimerInput();
      if(printFlag){sprintf(timer, "%d%d:%d%d", minutes_2, minutes_1, seconds_2, seconds_1);LCD_Print("Timer:", timer);printFlag=false;}
    }
    else if(mode == 2){
      GetStopWatchInput();
      if(printFlag){sprintf(stopwatch, "%d%d:%d%d", minutes_2, minutes_1, seconds_2, seconds_1);LCD_Print("StopWatch:", stopwatch);printFlag=false;}
    }
  }
}