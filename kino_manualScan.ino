#include <avr/sleep.h> // sleep mode library

const int switchPin1 = 8; // pins for the switch
const int switchPin2 = 3;

int led1 = 13; // pins for the indicator LED
int led2 = 12;
int led3 = 11; 
int led4 = 10;

int relay1 = 7; // setting relay pins
int relay2 = 6;
int relay3 = 5;
int relay4 = 4;

int switchState1; // variables for state of the switches
int switchState2;

int interrupt = 2; // interrupt pin for sleep mode

void setup() {

  pinMode(switchPin1, INPUT); // setting each pin 
  pinMode(switchPin2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(interrupt, INPUT);

  digitalWrite(led1, LOW); // setting the initial states of each output
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(interrupt, HIGH);
  
  

}

void loop() {

  switchState1 = digitalRead(switchPin1);
      delay(400);
      ledState(led1, relay1);
      delay(500);
      ledState(led2, relay2);
      delay(500);
      ledState(led3, relay3);
      delay(500);
      ledState(led4, relay4);
      delay(100);
      sleepSetup();


       
}

void ledState(int ledz, int readRelayx){
  int redLedx = readRelayx;
  int ledx = ledz;
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  while(1){
    switchState1 = digitalRead(switchPin1);
    if(switchState1 == LOW){
      continue;
    }
    else {
      digitalWrite(ledx, HIGH);
      int x = 0;
      while(x<10000){
        switchState1 = digitalRead(switchPin1);
        switchState2 = digitalRead(switchPin2);
        if(switchState2 == LOW && switchState1 == HIGH){ //Selection LED
          digitalWrite(redLedx, LOW);
          while(1){                                      //Will turn off when selection released
            switchState2 = digitalRead(switchPin2);
            if(switchState2 == HIGH){
              digitalWrite(redLedx, HIGH);
              break;
            }
          }
        }
        x++;
        delay(6);
        if(switchState1 == LOW && switchState2 == HIGH){ //going to next LED (ending the while loop)
          switchState1 = digitalRead(switchPin1); 
          boolean isHigh = true;
          while(isHigh){
            int switchState1 = digitalRead(switchPin1);
            if(switchState1 == LOW){
              isHigh = true;
            }
            if(switchState1 == HIGH){
              isHigh = false;
              break;
            }
          }
          digitalWrite(ledx, LOW);
          break;
        }
      }
      break;
    }
  }
}


void sleepSetup(){
  sleep_enable();
  attachInterrupt(0,pinInterrupt,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void pinInterrupt(){
  sleep_disable();
  detachInterrupt(0);
}

