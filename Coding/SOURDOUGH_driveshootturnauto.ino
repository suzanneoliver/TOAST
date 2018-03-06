//RoboClaw RC Mode
//Control RoboClaw with servo pulses from a microcontroller.

/*
 * 2,3 to Receiver 2,4
 * 4,5 to Roboclaw S1, S2
 * 6 to Reciever 3
 * 8,9,10,11 to Stepper Driver 1,2,3,4
 * 12 to Receiver 5
 * 13 to Servo signal
 * GRD to Servo GRD, Stepper GRD, Receiver GRD
 * 5V to Servo power
 * 
 * Servo wires through slip ring for 360 turn
 */


#include <Servo.h>
#include <math.h>   
#include <SoftwareSerial.h>
#include <Stepper.h>

#define MIN 1250
#define MAX 1750
#define STOP 1500
#define DEAD 70


int ch1 = 2;
int ch2 = 3;

int auton = 7;
int shoot = 6;
int pwm;
int steps;
int max_steps;
int do_aut;

const int stepsPerRevolution = 200;
int spin =  12;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

Servo M1; // create servo object to control a RoboClaw channel
Servo M2; // create servo object to control a RoboClaw channel
Servo myservo; //gun servo
int pos = 0; // variable to store the servo position


void setup()
{
 M1.attach(4); // attaches the RC signal on pin 5 to the servo object
 M2.attach(5); // attaches the RC signal on pin 6 to the servo object
 myservo.attach(13);
 myservo.write(90);

  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);  

  pinMode(shoot, INPUT);
  pwm = pulseIn(shoot, HIGH);

  myStepper.setSpeed(100);
  pinMode(spin, INPUT);

  steps = 0;
  max_steps = 20;
}
void loop()
{
  
 while (steps < max_steps)
  {
    do_aut = pulseIn(auton, HIGH);
    if (do_aut > 1500) 
    {
      M1.writeMicroseconds(MAX);
      steps += 1;
      delay(200);
      Serial.print(steps);
      Serial.print("\n");
    }
    else {
      break;
    }
  }

  
  int read1 = pulseIn(ch1, HIGH);
  int read2 = pulseIn(ch2, HIGH);
  //Serial.print(read1);
  //Serial.print(read2);
  if (read1 < 2100 && read1 > 900) {
    M1.writeMicroseconds(read1);
  }
  else {
     M1.writeMicroseconds(STOP);
  }
  if (read2 < 2100 && read2 > 900) {
    M2.writeMicroseconds(read2);
  }
  else {
     M2.writeMicroseconds(STOP);
  }


  int trig = pulseIn(shoot, HIGH);
  Serial.print(trig);
  Serial.print("\n");
  
if (abs(pwm - trig) > 500) {
    Serial.print(trig);
    Serial.print("\n");
    //Serial.print(pwm);
    //Serial.print("\n");  
  
    myservo.write(110);              // tell servo to go to position in variable 'pos'
    delay(80);      // waits 15ms for the servo to reach the position

    myservo.write(90);

    if (trig > 1500) {
      pwm = 1800;
    }
    else {
      pwm = 1200;
    }
    
    Serial.print("shooting \n");
  }

  int val = pulseIn(spin, HIGH);
  //Serial.print(val);
 // Serial.print("\n");

  if (val > 1800)
  {
    myStepper.step(5);
    delay(10);
  }
  else if (val < 1200 && val > 900)
  {
    myStepper.step(-5);
    delay(10);
  }
} 
