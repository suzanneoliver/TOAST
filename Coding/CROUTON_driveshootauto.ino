//RoboClaw RC Mode
//Control RoboClaw with servo pulses from a microcontroller.

/*
 * To Turn ON: 
 * Turn on remote, with channel 5 in Up position
 * Power up Roboclaw
 * Wait ~10 seconds
 * Plug in Arduino
 * 
 * 
 * Wiring:
 * 3 -> Receiver 3
 * 5,6 -> Receiver 2,1
 * 8,9 -> Roboclaw S1, S2
 * 10 -> Receiver 5
 * 11 -> Servo signal
 * 5V -> Servo power
 * GRD -> Receiver GRD, Servo GRD
 * 
 * On Roboclaw: RC Mode, Mix On, Exp On, Deadband to 5.5%
 * Receiver power -> Roboclaw power
 * Receiver GRD -> Roboclaw GRD
 */
 

#include <Servo.h>
#include <math.h>   

#define MIN 1250
#define MAX 1750
#define STOP 1500
#define DEAD 50


int ch1 = 5;
int ch2 = 6;

int shoot = 3;
int auton = 10;

int pwm;
int trig;
int do_aut;

int max_steps;
int steps;

Servo M1; // create servo object to control a RoboClaw channel
Servo M2; // create servo object to control a RoboClaw channel
Servo myservo; //gun servo
int pos = 0; // variable to store the servo position


void setup()
{
 M1.attach(8); // attaches the RC signal on pin 5 to the servo object
 M2.attach(9); // attaches the RC signal on pin 6 to the servo object
 myservo.attach(11);

  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);  

  pinMode(shoot, INPUT);
  pinMode(auton, INPUT);

  do_aut = pulseIn(auton, HIGH);
  pwm = pulseIn(shoot, HIGH);
  myservo.write(15);
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
  Serial.print(read1);
  Serial.print("\n");
  Serial.print(read2);
  Serial.print("\n");
  Serial.print("\n");
  
  if (read1 < 2000 && read1 > 1000) {
    M1.writeMicroseconds(read1);
  }
  else {
     M1.writeMicroseconds(STOP);
  }
  if (read2 < 2000 && read2 > 1000) {
    M2.writeMicroseconds(read2);
  }
  else {
     M2.writeMicroseconds(STOP);
  }


  trig = pulseIn(shoot, HIGH);
  Serial.print(trig);
  Serial.print("\n");


  if (abs(pwm - trig) > 500) {
  
    myservo.write(70);              // tell servo to go to position in variable 'pos'
    delay(140);      // waits 15ms for the servo to reach the position

    myservo.write(15);
    delay(100);

    pwm = trig;
    Serial.print("shooting \n");
  }
  
} 

