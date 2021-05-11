
//#define ENCODER_DO_NOT_USE_INTERRUPTS
//#define HALF_STEP


#include <Encoder.h>

#include "Keyboard.h"


const int RATE_PIN = A0;
const int PREV_PIN = 2;
const int NEXT_PIN = 3;
const int FADE_PIN = 4;
const int MASH_PIN = 14;
const int PRNT_PIN = 15;
const int LOCK_PIN = 16;

bool isFadeBtnUp = true;
bool isMashBtnUp = true;
bool isPrintBtnUp = true;
bool isLockBtnUp = true;
long curPos = 0;


Encoder digiPot(PREV_PIN, NEXT_PIN);


void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  pinMode(RATE_PIN, INPUT_PULLUP);
  pinMode(FADE_PIN, INPUT_PULLUP);
  pinMode(MASH_PIN, INPUT);
  pinMode(PRNT_PIN, INPUT);
  pinMode(LOCK_PIN, INPUT);

  digiPot.write(0);

//  Serial.println(" u=-= setup =-=");
}


void loop() {

  long updPos = digiPot.read();

//  Serial.print("RATE_PIN [");
//  Serial.print(analogRead(RATE_PIN));
//  Serial.print("]");
//  Serial.println(" =-= ");

//  Serial.print("PREV_PIN [");
//  Serial.print(digitalRead(PREV_PIN));
//  Serial.print("]");
//  Serial.println(" =-= ");
//
//  Serial.print("NEXT_PIN [");
//  Serial.print(digitalRead(NEXT_PIN));
//  Serial.print("]");
//  Serial.println(" =-= ");

 
  if (curPos != updPos && updPos % 4 == 0) {
//    Serial.println(F("POS CHANGE"));
//
    int dir = float((abs(curPos) - abs(updPos)) * 0.25) * -1;
    
//    Serial.print("curPos [");
//    Serial.print(curPos);
//    Serial.print("]");
//    Serial.print(" =-= ");
//    Serial.print("updPos [");
//    Serial.print(updPos);
//    Serial.print("]");
//    Serial.print(" =-= ");
//    Serial.print("dir [");
//    Serial.print(dir);
//    Serial.print("]");
//    Serial.println(" =-= ");

    if (dir == -1) {
//      Serial.println(F("PREV"));
      Keyboard.write(KEY_BACKSPACE);
      delay(33);
    
    } else if (dir == 1) {
//      Serial.println(F("NEXT"));
      Keyboard.write('h');
      delay(33);
    }

    curPos = updPos;
  }

  if (analogRead(RATE_PIN) < 1000) {
    int rateVal = analogRead(RATE_PIN);

//    Serial.print("rateVal [");
//    Serial.print(rateVal);
//    Serial.print("]");
//    Serial.println(" =-= ");

    if (rateVal < 50) {
//      Serial.println(F("RATE++"));
      Keyboard.write('+');
      delay(125);
    
    } else if (rateVal < 150) {
//      Serial.println(F("RATE--"));
      Keyboard.write('-');
      delay(125);
    
    } else {
//      Serial.println(F("RATE MAX"));
      for (byte i=0; i<5; i++) {
        Keyboard.write('+');
        delay(125);
      }
    }
  }

  
  if (digitalRead(FADE_PIN) == LOW && isFadeBtnUp) {
//    Serial.println(F("FADE DN"));
    isFadeBtnUp = false;
    Keyboard.write(0x20);
    delay(100);
  } 

  if (digitalRead(FADE_PIN) == HIGH && !isFadeBtnUp) {
//    Serial.println(F("FADE UP"));
    isFadeBtnUp = true;
  }


  if (digitalRead(LOCK_PIN) == HIGH && isLockBtnUp) {
//    Serial.println(F("LOCK DN"));
    isLockBtnUp = false;
    Keyboard.press(207);
    delay(33);
    Keyboard.releaseAll();
    delay(100);
  }


  if (digitalRead(LOCK_PIN) == LOW && !isLockBtnUp) {
//    Serial.println(F("LOCK UP"));
    isLockBtnUp = true;
  }

  
  if (digitalRead(PRNT_PIN) == HIGH && isPrintBtnUp) {
    Serial.println(F("PRINT DN"));
    isPrintBtnUp = false;
    Keyboard.press(206);
    delay(33);
    Keyboard.releaseAll();
    delay(125);
  }

  if (digitalRead(PRNT_PIN) == LOW && !isPrintBtnUp) {
    Serial.println(F("PRINT UP"));
    isPrintBtnUp = true;
  }


  if (digitalRead(MASH_PIN) == HIGH && isMashBtnUp) {
//    Serial.println(F("MASH DN"));
    isMashBtnUp = false;
    Keyboard.write('a');
    delay(125);
  }

  if (digitalRead(MASH_PIN) == LOW && !isMashBtnUp) {
//    Serial.println(F("MASH UP"));
    isMashBtnUp = true;
  }
}


void launch() {
  Keyboard.press(KEY_LEFT_CTRL);
  delay(33);
  Keyboard.press(KEY_LEFT_SHIFT);
  delay(33);
  Keyboard.press('k');
  delay(100);
  Keyboard.releaseAll();
}
