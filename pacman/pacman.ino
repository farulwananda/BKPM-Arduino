#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27(Cooperate with 3 short circuit caps) for a 16 chars and 2 line display


int backlightState = LOW;
long previousMillis = 0;
long interval = 1000;
  
// make some custom characters:

byte pac1Def[8] = {
B00000,
B01110,
B11011,
B11111,
B11111,
B01110,
B00000,
B00000
};
byte pac2Def[8] = {
B00000,
B01110,
B10100,
B11000,
B11100,
B01110,
B00000,
B00000
};
byte pillDef[8] = {
B00000,
B00000,
B00000,
B01100,
B01100,
B00000,
B00000,
B00000
};
 
const byte pac1 = 0x0;
const byte pac2 = 0x1;
const byte pill = 0x2;
const int del = 250;
 
int x = 0;
int y = 0;
int px = 0;
int py = 0;
 
void setup() {

lcd.init();                      // initialize the lcd 
lcd.backlight();
  
lcd.home();

// create a new character
lcd.createChar(0, pac1Def);
// create a new character
lcd.createChar(1, pac2Def);
// create a new character
lcd.createChar(2, pillDef);
// set up the lcd's number of columns and rows:

lcd.begin(16, 2);
// fill the display
fill();
}
 
void loop() {
anim();
x++;
if(x>15 && y == 0)
{
x = 0;
y = 1;
}
else if(x>15 && y == 1)
{
x = 0;
y = 0;
fill();
}

}
 
// Initial display fill
void fill()
{
lcd.setCursor(0,0);
lcd.write(0); //pac1
for(int j=0;j<7;j++)
{
lcd.print(" ");
lcd.write(2); //pill
}
lcd.setCursor(0,1);
lcd.write(2); //pill
for(int j=0;j<7;j++)
{
lcd.print(" ");
lcd.write(2); //pill
}
}
 
// character animation
void anim()
{
lcd.setCursor(px,py);
lcd.print(" ");
lcd.setCursor(x,y);
lcd.write(1);  //pac2
delay(del);
lcd.setCursor(x,y);
lcd.write(0);  //pac1
delay(del);
px = x;
py = y;
}
