// this is the autoscan portion of the device using LEDs as the indicators

#include <avr/sleep.h> // sleep mode library

const int switchPin = 3; //selection pin

int relay1 = 7;
int relay2 = 6;
int relay3 = 5;
int relay4 = 4;

int interrupt = 2;

int switchState = 0;

void setup() {

  for(int i=13; i>=10; i--) {
    pinMode(i, OUTPUT);
  }

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(interrupt, INPUT);

  pinMode(switchPin, INPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(interrupt, HIGH);
  

}

void loop() {
  autoScan();
}



void autoScan(){
  
switchState = digitalRead(switchPin);
int z = 0;
while(z<3){
  for(int i=13; i>=10; i--){
    digitalWrite(i, HIGH);
    switch(i){
      case 13: {
        int x = 0;
        while(x<60){
          switchState = digitalRead(switchPin);
          if(switchState == LOW){
            digitalWrite(relay1, LOW);
            digitalWrite(i, LOW);
            while(1){
              switchState = digitalRead(switchPin);
              if(switchState == HIGH){
                digitalWrite(relay1, HIGH);
                digitalWrite(i, HIGH);
                break;
              } 
            }
            x = 0;
            continue;
          }
          x++;
          delay(50);
        }
        break;
      }
      case 12:{
        int x = 0;
        while(x<60)  {
          switchState = digitalRead(switchPin);
          if(switchState == LOW) {
            digitalWrite(relay2, LOW);
            digitalWrite(i, LOW);
            while(1){
              switchState = digitalRead(switchPin);
              if(switchState == HIGH){
                digitalWrite(relay2, HIGH);
                digitalWrite(i, HIGH);
                break; 
              }
            }
            x = 0;
            continue;
          }
          x++;
          delay(50);
        }
        break;
      }
       case 11:{
        int x = 0;
        while(x<60) {
          switchState = digitalRead(switchPin);
          if(switchState == LOW) {
            digitalWrite(relay3, LOW);
            digitalWrite(i, LOW);
            while(1){
              switchState = digitalRead(switchPin); 
              if(switchState == HIGH) {
                digitalWrite(relay3, HIGH);
                digitalWrite(i, HIGH);
                break;
              }
            }
            x = 0;
            continue;
          }
          x++;
          delay(50);
        }
        break;
      }
       case 10:{
        int x = 0;
        while(x<60) {
          switchState = digitalRead(switchPin);
          if(switchState == LOW) {
            digitalWrite(relay4, LOW);
            digitalWrite(i, LOW);
            while(1){
              switchState = digitalRead(switchPin); 
              if(switchState == HIGH) {
                digitalWrite(relay4, HIGH);
                digitalWrite(i, HIGH);
                break;
              }
            }
            x = 0;
            continue;
          }
          x++;
          delay(50);
        }
        break;
       }
    }
  digitalWrite(i, LOW);
  }
  z++;
}

sleepSetup();
delay(1500);
while(1){
  switchState = digitalRead(switchPin);
  if(switchState == HIGH){
    break;
  }
}
}



void sleepSetup(){
  sleep_enable();
  attachInterrupt(0, pinInterrupt, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void pinInterrupt(){
  sleep_disable();
  detachInterrupt(0);
}

