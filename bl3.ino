#include <NewPing.h>

// Pinii motor 1
#define motor1_f 5
#define motor1_b 6

// Pinii motor 2
#define motor2_f 3
#define motor2_b 11

#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 100

//leduri fata
int redPin_f = 4;
int greenPin_f = 7;
int bluePin_f = 2;

//leduri spate
int redPin_b = 9;
int greenPin_b = 10;
int bluePin_b = 12;

#define buzzer 8
  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

char command;

void setup() {
  
 digitalWrite(motor1_f, 0);
 digitalWrite(motor1_b, 0);
 digitalWrite(motor2_f, 0);
 digitalWrite(motor2_b, 0);
 pinMode (motor1_f, OUTPUT);
 pinMode (motor1_b, OUTPUT);
 pinMode (motor2_f, OUTPUT);
 pinMode (motor2_b, OUTPUT);

 pinMode(redPin_f, OUTPUT);
 pinMode(greenPin_f, OUTPUT);
 pinMode(bluePin_f, OUTPUT);
 pinMode(redPin_b, OUTPUT);
 pinMode(greenPin_b, OUTPUT);
 pinMode(bluePin_b, OUTPUT);

 pinMode(buzzer, OUTPUT);
 digitalWrite(buzzer, HIGH);

 Serial.begin(9600);
 lights_off();
}

void loop() {
 
 if(testDistance() == 0 and command == 'N') {
    Stop(200);
 }
    
 if(Serial.available() > 0){ 
    command = Serial.read();

    switch(command){
      case 'N':  
        go_forward();
        break;
      case 'S':  
        go_back();
        break;
      case 'V':  
        go_left();
        break;
      case 'E':  
        go_right();
        break;
      case 'A':  
        go_right_up();
        break;
      case 'B':  
        go_left_up();
        break;
      case 'C':  
        go_right_down();
        break;
      case 'D':  
        go_left_down();
        break;
      case 'R':
        Stop(200);
        break;
      case 'K':
        K_lights();
        break;
      case 'L':
        brake_lights();
        break;
      case 'l':
        lights_off();
        break;
      case 'X':
         sound_on();
        break;
      case 'x':
         sound_off();
        break;
    }
  }
}

void StartMotor (int m1, int m2, int forward, int speed)
{

 if (speed==0) // oprire
 {
  digitalWrite(m1, 0); 
  digitalWrite(m2, 0);
 }
 else 
 {
   if (forward==1)
   {
     digitalWrite(m2, 0);
     analogWrite (m1, speed); // folosire PWM
   }
   else
   {
     digitalWrite(m1, 0);
     analogWrite(m2, speed);
   }
 }
}

// Functie de siguranta
// Executa oprire motoare, urmata de delay
void Stop(int ms)
{
 StartMotor (motor1_f, motor1_b, 0, 0);
 StartMotor (motor2_f, motor2_b, 0, 0);
 brake_lights();
 delay(ms);
}

void go_forward(){
  
  Stop(200);
  normal_lights();
  StartMotor (motor1_f, motor1_b, 1, 200);   //fata
  StartMotor (motor2_f, motor2_b, 1, 200);
}

void go_back(){
  
  Stop(200);
  white_back_lights();
  StartMotor (motor1_f, motor1_b, 0, 200);   //spate
  StartMotor (motor2_f, motor2_b, 0, 200);
}

void go_left(){
  Stop(200);
  normal_lights();
  StartMotor (motor1_f, motor1_b, 1, 200);   // stanga
  StartMotor (motor2_f, motor2_b, 0, 200); 
  
}

void go_right(){
  Stop(200);
  normal_lights();
  StartMotor (motor1_f, motor1_b, 0, 200);   //dreapta
  StartMotor (motor2_f, motor2_b, 1, 200);
}

void go_right_up(){
  Stop(200);
  normal_lights();
  go_right();
  delay(500);
  go_forward();
}

void go_left_up(){
  Stop(200);
  normal_lights();
  go_left();
  delay(500);
  go_forward();
}

void go_right_down(){
  Stop(200);
  go_right();
  delay(500);
  white_back_lights();
  go_back();
}

void go_left_down(){
  Stop(200);
  go_left();
  delay(500);
  white_back_lights();
  go_back();
}

void lights_off(){
  analogWrite(redPin_f, 0);
  analogWrite(greenPin_f, 0); //inchis
  analogWrite(bluePin_f, 0);

  //red back-lights
  analogWrite(redPin_b, 0);  //inchis
  analogWrite(greenPin_b, 0);
  analogWrite(bluePin_b, 0);
}

void normal_lights(){
  //white front lights
  analogWrite(redPin_f, 255);
  analogWrite(greenPin_f, 255); 
  analogWrite(bluePin_f, 255);

  //back lights off
  analogWrite(redPin_b, 0); 
  analogWrite(greenPin_b, 0);
  analogWrite(bluePin_b, 0);
}

void white_back_lights(){
  //white back lights
  analogWrite(redPin_b, 250);  
  analogWrite(greenPin_b, 250);
  analogWrite(bluePin_b, 250);
}

void brake_lights(){
  //yellow front lights
  analogWrite(redPin_f, 255);
  analogWrite(greenPin_f, 255); 
  analogWrite(bluePin_f, 255);

  //red back lights
  analogWrite(redPin_b, 250);  
  analogWrite(greenPin_b, 0);
  analogWrite(bluePin_b, 0);
}

void K_lights(){
  analogWrite(redPin_f, 255);
  analogWrite(greenPin_f, 255); 
  analogWrite(bluePin_f, 255);

  analogWrite(redPin_b, 255); 
  analogWrite(greenPin_b, 255);
  analogWrite(bluePin_b, 255);

  delay(800);

  analogWrite(redPin_f, 0);
  analogWrite(greenPin_f, 0); 
  analogWrite(bluePin_f, 0);

  analogWrite(redPin_b, 0); 
  analogWrite(greenPin_b, 0);
  analogWrite(bluePin_b, 0);

  delay(800);
}

void sound_on(){
  digitalWrite(buzzer, LOW);
}
void sound_off(){
 digitalWrite(buzzer, HIGH);
}

int testDistance(){
  unsigned int distance;
  distance = sonar.ping_cm();
  if (distance > 15 or distance == 0)
    return 1;
  return 0;
}
