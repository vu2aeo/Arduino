#include <LiquidCrystal.h>
#define LCD_ROWS 2
#define LCD_COLS 16
#define DELAY 100

LiquidCrystal lcd(2,3,4,5,6,7);

byte myCharQ[8]=
{
  B0100,
  B0010,
  B0001,
  B0010,
  B0100,
  B0100,
  B0100,
  B0100};

void setup()
{
  lcd.begin(LCD_COLS,LCD_ROWS);
  lcd.setCursor(0,0);
  lcd.print("Hello!!");
  lcd.createChar(1,myCharQ);
}

void loop()
{
  lcd.print("               ");
   for (int i = 0; i < LCD_COLS; i++)
   {
     //set the cursor on the second row and ith column
     lcd.setCursor(i,1);
     lcd.write(1);//write char 1 to lcd
     
     lcd.setCursor(i,0);
     lcd.print("Aswan");
     delay(DELAY);
     lcd.setCursor(0,0);
     lcd.print("                ");
     
     
   } 
   //clear the second row completely
   lcd.setCursor(0,1);
   lcd.print("                ");
   
   for (int i = LCD_COLS; i > 0; i--)
   {
     //set the cursor on the second row and ith column
     lcd.setCursor(i,1);
     lcd.write(1);//write char 1 to lcd
     
     lcd.setCursor(i,0);
     lcd.print("Aswan");
     delay(DELAY);
     lcd.setCursor(0,0);
     lcd.print("                ");
     
   } 
 
}




