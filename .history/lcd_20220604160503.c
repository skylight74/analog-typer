#include "Includes.h"
#include "lcd.h"

void Pulse(void){
    LCD_EN = 1;
    __delay_us(LCD_PULSE);
    LCD_EN = 0;
    __delay_us(LCD_PULSE);
}

void InitLCD(void) {
    __delay_ms(20);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(6);
    PORTD = 0x30;
    Pulse();
    
    __delay_us(300);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(2);
    PORTD = 0x20;
    Pulse();
        
    LcdCmd(0x2C);
    LcdCmd(0x0C);
    LcdClear();
}

void LcdCmd(uint8_t cmd){
    // Send 'cmd' as a command to the LCD.
    LCD_EN = 0;
    LCD_RS = 0;
    LCD_PORT = cmd;
    Pulse();
}
void LcdData(uint8_t data){
    // Send 'data' as data to the LCD.
    LCD_EN = 0;
    LCD_RS = 1;
    LCD_PORT = data;
    Pulse();
    LCD_RS = 0;
}

void CreateChar(uint8_t addr, uint8_t charmap[]) {
  addr &= 0x7; // we only have 8 locations 0-7
  LcdCmd(0x40 | (addr << 3)); // Set the address for custom char.
  for (int i=0; i<8; i++) {
    LcdData(charmap[i]); // Write char data.
  }
}

void LcdStr(char *buf){
    // Send 'buf' to the LCD.
    // Prints up to 16 characters. 
    // If more than 16 characters are sent,
    // the string will be cycled. from the beginning.
    uint8_t i = 0;
    while(buf[i] != '\0'){
        LcdData(buf[i]);
        i++;
        if(i == 16){
            i = 0;
        }
    }
}
