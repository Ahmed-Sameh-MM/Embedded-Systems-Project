
#include "variables.h"

char getOp() {
  if(opCode == 'A') return '+';
  else if(opCode == 'B') return '-';
  else if(opCode == 'C') return '/';
  else if(opCode == '*') return 'x';
}

// Calculator Input
void GetCalculatorInput(){
  char input = keypad_read();
  if(input == ' '){return;}
  if (input == 'A' || input == 'B' || input == 'C' || input == '*'){
    opCode = input;
    sprintf(calculator, "%d%c", x, getOp());
    isOpEntered = true;
    printFlag = true;
  }
  else if(input == 'D'){
    if (opCode == 'A'){
      z = x + y;
    }
    else if (opCode == 'B'){
      z = x - y;
    }
    else if (opCode == 'C'){
      if(y != 0)
        z = (float)x / y;
    }
    else if(opCode == '*'){
      z = x * y;
    }
    sprintf(calculator, "= %.3f", z);
    x=0;y=0;z=0;isOpEntered = false;opCode = 'A';
    printFlag = true;
  }
  else{
    if(!isOpEntered){
      x *= 10;
      x += (input - '0');
      sprintf(calculator, "%d", x);
      printFlag = true;
    }
    else{
      y *= 10;
      y += (input - '0');
      sprintf(calculator, "%d%c%d", x, getOp(), y);
      printFlag = true;
    }
  }
}