/*
Code Version 1 :- increase the speed on clicking the push button (code developed from "dsr_nema17_42hs48_1684_009_02.ino") 
---------------- Components Used ----------------
Driver Used  = TB6600
Stepper Used = Nema 17, 45kgcm@20rpm Unknown Series (https://robokits.co.in/motors/stepper-motor/stepper-motor-with-gearbox/nema17-planetary-geared-stepper-motor-45kgcm)
Gear Box = 1:14 Aprox
Micro Step used = 3200SPR ; S1 = 0, S2 = 0, S3 = 1
Current Set = 1.5Amp ; S4 = 1, S5 = 1, S6 = 0
Input Volatge = 12v (8amp) for driver 
Arduino = Nano original
12v to 5v buck (for powering Nano)

--------------------------------------------------

-------------- Connections -------------------
TB6600 to Nano
 ENA- , DIR- and PUL-  ->   gnd of arduino
 ENA+                  ->   D7
 DIR+                  ->   D8
 PUL+                  ->   D9 

Push Button (10k pull up)to nano on pin D2
-----------------------------------------------


Created on :- 12-02-2026
Created by :- K Madhu Mohan Chary 
For code enquiry :- madhu@marutdrones.com 

*/

// Used Common cathode setup on driver
const byte pul_pin = 9; //pulse pin 
const byte dir_pin = 8; //direction pin
const byte ena_pin = 7; //enable pin

//micro
unsigned long curr_micro = 0;
unsigned long prev_micro = 0;
volatile bool state = HIGH;

volatile int dt_micro = 1000;
volatile int dt_micro_min = 100;//100
volatile int dt_micro_max = 1000;//1000
volatile int dt_micro_factor = 100;

//digital Read from other (nano)
volatile byte btn_pin = 2;
volatile bool btn_val = LOW;


void change_dt_micro()
{
    dt_micro = dt_micro - dt_micro_factor;

    if(dt_micro < dt_micro_min)
    {
      dt_micro = dt_micro_max;
    }
}

void setup() {
  pinMode(pul_pin,OUTPUT);
  pinMode(dir_pin,OUTPUT);
  pinMode(ena_pin,OUTPUT);

  pinMode(btn_pin,INPUT);

  digitalWrite(ena_pin,LOW);
  digitalWrite(dir_pin,LOW);
  Serial.begin(9600);

  delay(100);
  attachInterrupt(digitalPinToInterrupt(btn_pin), change_dt_micro, RISING);           
                
}

void loop()
{
  curr_micro = micros();
  if((curr_micro - prev_micro) >= dt_micro)
  {
      state = !state;
      digitalWrite(pul_pin,state);
      //Serial.println(state);
      //Serial.println(dt_micro);
      prev_micro = curr_micro;
  }

}




