#include "LiquidCrystal_I2C.h"
#include  "Wire.h"
#include <Encoder.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
Encoder myEnc(15, 16);
char buffer[3];

const int DB1 = 2;
const int DB2 = 3;
const int DB4 = 3;
const int DB8 = 5;
const int DB16 = 6;
const int DB20 = 7;

const int LOW_ATTEN = 0;
const int HIGH_ATTEN = 51;
int attenValue = 0;

void setup() {
   //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  // put your setup code here, to run once:

  //pinMode(DB1, OUTPUT);
  


    // tell the screen to write on the top row
  lcd.setCursor(0,0);
  // tell the screen to write “hello, from” on the top  row
  lcd.print("Attenuation");

}

long oldPosition  = -999;

void loop() {

    long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    if (newPosition > oldPosition) {
      attenValue++;
    } else {
      attenValue--;
    }
    if (attenValue > HIGH_ATTEN) attenValue = HIGH_ATTEN;
    if (attenValue < LOW_ATTEN) attenValue = LOW_ATTEN;
    oldPosition = newPosition;
    
  }
    lcd.setCursor(0, 1);
    sprintf(buffer,"%02d", attenValue);
    lcd.print(buffer);

    // Action Attend Value on Relays
    if (attenValue > 20) {
      digitalWrite(DB20, HIGH);
    } else {
      digitalWrite(DB20, LOW);
    }
    if ((attenValue & 1) == 1) {
            digitalWrite(DB1, HIGH);
    } else {
      digitalWrite(DB1, LOW);
    }
    if ((attenValue & 2) == 2) {
            digitalWrite(DB2, HIGH);
    } else {
      digitalWrite(DB2, LOW);
    }
    if ((attenValue & 4) == 4) {
            digitalWrite(DB4, HIGH);
    } else {
      digitalWrite(DB4, LOW);
    }
    if ((attenValue & 8) == 8) {
            digitalWrite(DB8, HIGH);
    } else {
      digitalWrite(DB8, LOW);
    }
    if ((attenValue & 16) == 16) {
            digitalWrite(DB16, HIGH);
    } else {
      digitalWrite(DB16, LOW);
    }

}
