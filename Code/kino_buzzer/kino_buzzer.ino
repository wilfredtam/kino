// Hello! this code is for a multiplexer device that utilizes one buzzer as an indicator for 4 options
// written by: Wilfred Tam

#include <avr/sleep.h> // sleep mode library

const int switchPin1 = 8; // cycling pin
const int switchPin2 = 3; // selection pin & returning from sleep mode
const int selectPin = 9; // mode selection pin

const int led1 = 13; // pins for the indicator LED (manualScan);

// constant int because these pins will/should not change

int relay1 = 7; // setting relay pins 
int relay2 = 6; 
int relay3 = 5;
int relay4 = 4;

int switchState1; // integers to hold the states of each switch
int switchState2;
int selectState;
boolean state1;
boolean state2;
boolean state3;
boolean state4;

unsigned long buzzerTimer = 0; //unsigned long because the number will get large, time buzzer has been running

int interrupt = 2; // interrupt pin for sleep mode

void setup() {

  pinMode(switchPin1, INPUT); // setting each pin and their respective roles
  pinMode(switchPin2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(interrupt, INPUT);

  digitalWrite(led1, LOW); // setting the initial states of each output
  digitalWrite(relay1, HIGH); // the relays are active low, so set them initially HIGH
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(interrupt, HIGH); // interrupt is active low so inital toggle is HIGH
  
}


// ** GOAL: change so that the beeps are with their respective outputs (one for 1, two for 2, etc...)

void loop() {
  selectState = digitalRead(selectPin); // selecting the state of the device depending on mode selection pin(9)
  delay(500);
  if(selectState == HIGH){
    manualScan();
  }
  if(selectState == LOW){
    autoScan();
  }
  sleepSetup();
}

void autoScan(){
  int z = 0;
  while(z<3){                                     // the auto scan will occur for 3 cycles (z = 0,1,2)
    for(int i=led1; i>=10; i--){
      switch(i){
        case 13: {
          int x = 0;
          digitalWrite(led1,HIGH);                // buzzer is active high
          buzzerTimer = millis();
          while(x<60){                            // the amount of time that will be on this 'case'
            if((millis()-buzzerTimer) > 750){     // setting the amount of time(in ms) the buzzer will ring
            digitalWrite(led1,LOW);
            }
            switchState2 = digitalRead(switchPin2);
            if(switchState2 == LOW){              // switch is active low because of pull up resistor, when switch closes, will be connected to gnd
              digitalWrite(relay1,LOW);           // relay is active low 
              while(1){                           // making sure the relay will stay triggered until selection is released (HIGH)
                switchState2 = digitalRead(switchPin2);
                if(switchState2 == HIGH){
                  digitalWrite(relay1,HIGH);
                  break;
                } 
              }
            x = 0;                                // resets the timer if selection button is pressed
            continue;
            }
           x++;
           delay(50);
          }
          break;  
        }
        case 12: {
          int x = 0;
          digitalWrite(led1,HIGH); 
          buzzerTimer = millis();
          while(x<60){
            if((millis()-buzzerTimer) > 750){
            digitalWrite(led1,LOW);
            }
            switchState2 = digitalRead(switchPin2);
            if(switchState2 == LOW){
              digitalWrite(relay2,LOW);
              while(1){
                switchState2 = digitalRead(switchPin2);
                if(switchState2 == HIGH){
                  digitalWrite(relay2,HIGH);
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
        case 11: {
          int x = 0;
          digitalWrite(led1,HIGH);
          buzzerTimer = millis();
          while(x<60){
            if((millis()-buzzerTimer) > 750){
            digitalWrite(led1,LOW);
            }
            switchState2 = digitalRead(switchPin2);
            if(switchState2 == LOW){
              digitalWrite(relay3,LOW);
              while(1){
                switchState2 = digitalRead(switchPin2);
                if(switchState2 == HIGH){
                  digitalWrite(relay3,HIGH);
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
        case 10: {
          int x = 0;
          digitalWrite(led1,HIGH);
          buzzerTimer = millis();
          while(x<60){
            if((millis()-buzzerTimer) > 750){
            digitalWrite(led1,LOW);
            }
            switchState2 = digitalRead(switchPin2);
            if(switchState2 == LOW){
              digitalWrite(relay4,LOW); 
              while(1){
                switchState2 = digitalRead(switchPin2);
                if(switchState2 == HIGH){
                  digitalWrite(relay4,HIGH);
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
    }
    z++;                                              // adds to z until fulfills the for loop
  }
  sleepSetup();                                       // sleeps after the for loop is fulfilled
  delay(1500);
  while(1){
    switchState2 = digitalRead(switchPin2);
    if(switchState2 == HIGH){
      break;  
    }
  }
}

void manualScan(){
      state1 = ledState(led1, relay1);
      delay(500);
      if(state1 == true){
        state2 = ledState(led1, relay2);
        delay(500);
        if(state2 == true){
          state3 = ledState(led1, relay3);
          delay(500);
          if(state3 == true){
            state4 = ledState(led1, relay4);
            delay(500);
          }
        }
      }
}

boolean ledState(int ledx, int readRelayx){
  int redLedx = readRelayx;
  digitalWrite(ledx, LOW);
  boolean isCycle = true;
  boolean notSleep = true;
  while(isCycle){
    switchState1 = digitalRead(switchPin1);
    if(switchState1 == LOW){
      continue;
    }
    else {
      digitalWrite(ledx, HIGH);
      int x = 0;
      while(x<10000){                                    //long autoscan, which will eventually send it to sleep mode
        switchState1 = digitalRead(switchPin1);
        switchState2 = digitalRead(switchPin2);
        if(redLedx == relay1){
          if(x>150){
            digitalWrite(ledx, LOW);
          }
        }
        else if(x>75){
          digitalWrite(ledx, LOW);
        }
        if(switchState2 == LOW && switchState1 == HIGH){ //Selection LED
          digitalWrite(redLedx, LOW);
          digitalWrite(ledx, LOW);
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
          buzzerTimer = millis();
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
          isCycle = false;
          break;
        }
        if(x>= 9999) {
          notSleep = false;
      }
      isCycle = false;
    }
  }
}
if(isCycle == false && notSleep == false){
  return false;
}
  return true;
}

void sleepSetup(){                                      // sleep mode 
  sleep_enable();
  attachInterrupt(0,pinInterrupt,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void pinInterrupt(){                                    // this program will run when the interrupt pin is LOW [determined in sleepSetup()]
  sleep_disable();
  detachInterrupt(0);
}

