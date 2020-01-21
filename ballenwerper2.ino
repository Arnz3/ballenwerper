#include <Servo.h>
#include <SoftwareSerial.h>

//motorA pins
const int PWMpinA = 6;
const int MotorPinA1 = 8;
const int MotorPinA2 = 7;

//motorB pins
const int PWMpinB = 3;
const int MotorPinB1 = 4;
const int MotorPinB2 = 2;

//Servo pin
Servo Servo1;

//Bluetooth pins
const int Tx = 11;
const int Rx = 10;

//variables
int PB = 255;
int ServoPosition = 0;
int readdata;

SoftwareSerial bluetooth(Tx, Rx);

void setup()
{
  pinMode(PWMpinA, OUTPUT);
  pinMode(MotorPinA1, OUTPUT);
  pinMode(MotorPinA2, OUTPUT);
  pinMode(PWMpinB, OUTPUT);
  pinMode(MotorPinB1, OUTPUT);
  pinMode(MotorPinB2, OUTPUT);
  Servo1.attach (12);
  Servo1.write(0);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop()
{
  if (bluetooth.available() >= 2){
    //convert the 2byte nr in a 1byte
    unsigned int readdata = bluetooth.read();
    unsigned int readdata1 = bluetooth.read();
    unsigned int realdata = (readdata1 *256) + readdata;
    Serial.println(realdata);

    if (realdata < 180){
      //servo instellen 
      ServoPosition = realdata;
      Servo1.write(ServoPosition);
      delay(100); 
    }

    else if (realdata > 999){
      //snelheid uit bt halen
      PB = realdata - 1000; // data in app +1000
    }

    else if (realdata == 800){
      // motorsnelheid instellen
      analogWrite(PWMpinA, PB);
      analogWrite(PWMpinB, PB);
      // besturing magnetische arm<<

      // motor aanzetten
      digitalWrite(MotorPinA1, HIGH);
      digitalWrite(MotorPinA2, LOW);
      digitalWrite(MotorPinB1, HIGH);
      digitalWrite(MotorPinB2, LOW);
      delay(5000);
    }

    else if (realdata == 700) {
      digitalWrite(MotorPinA1, LOW);
      digitalWrite(MotorPinA2, LOW);
      digitalWrite(MotorPinB1, LOW);
      digitalWrite(MotorPinB2, LOW);
    }
  
  }
  
}
