#include <SoftwareSerial.h> //Import bluetooth library

//To drive a motor to a direction, say, clockwise, the pin Input 1 must be high 
//while the pin Input 2 must be low. To drive the motor counter clockwise, 
//the pin Input 1 is low while the pin Input 2 is high.

// Initialize front motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
int front_m1p1 = 1;
int front_m1p2 = 2;
int front_m2p1 = 3;
int front_m2p2 = 4;

// Initialize back motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
int back_m1p1 = 5;
int back_m1p2 = 6;
int back_m2p1 = 7;
int back_m2p2 = 8;

//Initialize movement keyword variables
String Forward = "Forward"; 
String Back = "Back";
String Stop = "Stop";
String f_Right = "Forward Right";
String Right = "Right";
String b_Right = "Back Right";
String f_Left = "Forward Left";
String Left = "Left";
String b_Left = "Back Left";
/*
// Delay values, can be altered and optimized during the testing phase
int mini_delay = 100
int short_delay = 300
int medium_delay = 500
int long_delay = 1000
*/
// Initialize bluetooth connection
SoftwareSerial Blue(9,10); // RX pin 9; TX pin 10
char blueData; //Bluetooth data will be stored here
// RX pin receives data while TX pin transmits data

void setup() {
  // put your setup code here, to run once:
  //Set front motor pins to output mode
  pinMode(front_m1p1, OUTPUT);
  pinMode(front_m1p2, OUTPUT);
  pinMode(front_m2p1, OUTPUT);
  pinMode(front_m2p2, OUTPUT);

  //Set back motor pins to output mode
  pinMode(back_m1p1, OUTPUT);
  pinMode(back_m1p2, OUTPUT);
  pinMode(back_m2p1, OUTPUT);
  pinMode(back_m2p2, OUTPUT);

  //Set up bluetooth signal and begin reading
  Serial.begin(9600);
  Blue.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Blue.available()){
    blueData = Blue.read();
    if blueData == 'F'{ //Forward
      movement(Forward);
      Serial.println("Moving Forward now..");
      delay(100);
    }
    if blueData == 'G'{ //Forward Left
      turn(f_Left);
      Serial.println("Moving Forward and Left now..");
      delay(100);
    }
    if blueData == 'I'{ //Forward Right
      turn(f_Right);
      Serial.println("Moving Forward and Right now..");
      delay(100);
    }
    if blueData == 'B'{ //Back
       movement(Back);
       Serial.println("Moving Back now..");
       delay(100);  
    }
    if blueData == 'H'{ //Back Left
       turn(b_Left);
       Serial.println("Moving Back and Left now..");
       delay(100);  
    }
    if blueData == 'J'{ //Back Right
       turn(b_Right);
       Serial.println("Moving Back and Right now..");
       delay(100);  
    }
    if blueData == 'L'{ //Left
       turn(Left);
       Serial.println("Moving Left now..");
       delay(100);  
    }
    if blueData == 'R'{ //Right
       turn(Right);
       Serial.println("Moving Right now..");
       delay(100);  
    }
    if blueData == ('S' or 'D'){ //Stop or turn everything OFF
      movement(Stop);
      Serial.println("Stopped and stationary..");
      delay(200);  
    }
  }else{
    Serial.println("Attempting to receive a command..");
    delay(100);
  }
}

//Function that controls the movement of the car. Takes in inputs: Forward, Back and Stop
void movement(String Mode){
  if (Mode == Forward){
    // Front motor 1: Counter Clockwise, Front motor 2: Clockwise
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, HIGH);
    digitalWrite(front_m2p1, HIGH);
    digitalWrite(front_m2p2, LOW);
    
    // Back motor 1: counter Clockwise, Back motor 2: Clockwise
    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, HIGH);
    digitalWrite(back_m2p1, HIGH);
    digitalWrite(back_m2p2, LOW);
    
  }else if (Mode == Back){
    // Front motor 1: Clockwise, Front motor 2: Counter Clockwise
    digitalWrite(front_m1p1, HIGH);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, HIGH);

    // Back motor 1: Clockwise, Back motor 2: Counter Clockwise
    digitalWrite(back_m1p1, HIGH);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, HIGH);
    
  }else if (Mode == Stop){ 
    //Stops all four motors
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, LOW);

    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, LOW);
  }
}

//Function for the turning of the car, takes in a string input of Front Left, Left, Back Left or Front Right, Right, Back Right
void turn(String Mode){
  if (Mode == Right){
    // Front motor 1: Counter Clockwise, Front motor 2: Counter Clockwise
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, HIGH);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, HIGH);

    // Back motor 1: Counter Clockwise, Back motor 2: Counter Clockwise
    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, HIGH);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, HIGH);
    
  }else if (Mode == Left){
    // Front motor 1: Clockwise, Front motor 2: Clockwise
    digitalWrite(front_m1p1, HIGH);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, HIGH);
    digitalWrite(front_m2p2, LOW);

    // Back motor 1: Clockwise, Back motor 2: Clockwise
    digitalWrite(back_m1p1, HIGH);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, HIGH);
    digitalWrite(back_m2p2, LOW);
  }else if (Mode == f_Left){
      // Front motor 1: Stationary, Front motor 2: Clockwise
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, HIGH);
    digitalWrite(front_m2p2, LOW);

    // Back motor 1: Stationary, Back motor 2: Clockwise
    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, HIGH);
    digitalWrite(back_m2p2, LOW);
    
  }else if (Mode == f_Right){
    // Front motor 1: Counter-Clockwise, Front motor 2: Stationary
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, HIGH);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, LOW);

    // Back motor 1: Counter-Clockwise, Back motor 2: Stationary
    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, HIGH);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, LOW);
    
  }else if (Mode == b_Left){
      // Front motor 1: Stationary, Front motor 2: Counter-Clockwise
    digitalWrite(front_m1p1, LOW);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, HIGH);

    // Back motor 1: Stationary, Back motor 2: Counter-Clockwise
    digitalWrite(back_m1p1, LOW);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, HIGH);
    
  }else if (Mode == b_Right){
    // Front motor 1: Clockwise, Front motor 2: Stationary
    digitalWrite(front_m1p1, HIGH);
    digitalWrite(front_m1p2, LOW);
    digitalWrite(front_m2p1, LOW);
    digitalWrite(front_m2p2, LOW);

    // Back motor 1: Clockwise, Back motor 2: Stationary
    digitalWrite(back_m1p1, HIGH);
    digitalWrite(back_m1p2, LOW);
    digitalWrite(back_m2p1, LOW);
    digitalWrite(back_m2p2, LOW);
    
  }
}
