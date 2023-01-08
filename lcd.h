#define RS 0x01				 	        //RS -> PB0 (0x01)
#define RW 0x02                         //RW -> PB1 (0x02)
#define EN 0x04  		 	 	        //EN -> PB2 (0x04)
#define LCD_DIR GPIO_PORTB_DIR_R
#define LCD_DEN GPIO_PORTB_DEN_R
#define LCD_DATA GPIO_PORTB_DATA_R
#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7

void delayUs(int);   				                    //Delay in Micro Seconds
void delayMs(int);   					                //Delay in Milli Seconds
void LCD4bits_Init(void);				                //Initialization of LCD Display
void LCD_Write4bits(unsigned char, unsigned char);      //Write data as (4 bits) on LCD
void LCD4bits_Cmd(unsigned char);		                //Write command
void LCD_Command(unsigned char c);                      //Send command
void LCD_Show(unsigned char d);                         //Show a char
void LCD_Clear(void);                                   //Clear the screen
void LCD_Print(char *s, char *d);                       //Print 2 lines
void LCD_Cursor(char x, char y);                        //Set cursor
