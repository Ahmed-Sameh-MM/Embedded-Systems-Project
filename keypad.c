#include "keypad.h"
#include "DIO.h"

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

static void delay(int msec){
  int cnt=0;
  while (cnt < msec * 3100){cnt++;};
}

void keypad_init() {
  
  DIO_Init(PORTE, 1, OUT);
  DIO_Init(PORTE, 2, OUT);
  DIO_Init(PORTE, 3, OUT);
  DIO_Init(PORTE, 4, OUT);
  DIO_Init(PORTE, 5, OUT);
  
  DIO_Init(PORTC, 4, IN);
  DIO_Init(PORTC, 5, IN);
  DIO_Init(PORTC, 6, IN);
  DIO_Init(PORTC, 7, IN);
  
}

char keypad_read() {

  for(int i = 2; i < 6; i++) {
    DIO_WritePin(PORTE, i, 1);

    for(int j = 4; j < 8; j++) {
      if(DIO_ReadPin(PORTC, j)) {
        delay(25);
        if(DIO_ReadPin(PORTC, j)) {
          while(DIO_ReadPin(PORTC, j));
          return keys[i - 2][j - 4];
        }
      }
    }
    
    delay(50);
    DIO_WritePin(PORTE, i, 0);
  }
  return ' ';
}