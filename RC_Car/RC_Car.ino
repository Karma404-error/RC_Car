#include <SoftwareSerial.h> //Import bluetooth library

//To drive a motor to a direction, say, clockwise, the pin Input 1 must be high 
//while the pin Input 2 must be low. To drive the motor counter clockwise, 
//the pin Input 1 is low while the pin Input 2 is high.

// Initialize front motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
// For speed control, must use PMW Pins: 3, 5, 6, 9, 10, 11
int front_m1p1 = 1; // IN1
int front_m1p2 = 2; // IN2
int fm1_speed = 3; //Speed control for left front motor : ENA

int front_m2p1 = 4; //IN3
int front_m2p2 = 5; //IN4
int fm2_speed = 6; //Speed control for right front motor : ENB

// Initialize back motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
int back_m1p1 = 7; //IN1
int back_m1p2 = 8; //IN2
int bm1_speed = 9; //Speed control for left back motor : ENA

int back_m2p1 = 10; //IN3
int back_m2p2 = 12; //IN4
int bm2_speed = 11; //Speed control for right back motor : ENB

//Initialize movement keyword variables
String Forward = "Forward"; 
String Back = "Back";
String Stop = "Stop";
String Right = "Right";
String Left = "Left";

//Initialize max, min, actual and reduced factor of the car (255 -> 5 volts)
//Actual speed -> speed received from bluetooth module; Reduced factor -> used to
// find new speed of the wheels on the side of the turn to spin slower
int max_speed = 255;
int min_speed = 0;
int actual_speed = min_speed; //Car begins stationary

/*
// Delay values, can be altered and optimized during the testing phase
int mini_delay = 100
int short_delay = 300
int medium_delay = 500
int long_delay = 1000
*/
// Initialize bluetooth connection
SoftwareSerial Blue(19,18); // RX pin 19; TX pin 18 -> arduino MEGA
char blueData; //Bluetooth data will be stored here
// RX pin receives data while TX pin transmits data

void setup() {
  // put your setup code here, to run once:
  //Set front motor pins to output mode
  pinMode(front_m1p1, OUTPUT);
  pinMode(front_m1p2, OUTPUT);
  pinMode(fm1_speed, OUTPUT);
  pinMode(front_m2p1, OUTPUT);
  pinMode(front_m2p2, OUTPUT);
  pinMode(fm2_speed, OUTPUT);

  //Set back motor pins to output mode
  pinMode(back_m1p1, OUTPUT);
  pinMode(back_m1p2, OUTPUT);
  pinMode(bm1_speed, OUTPUT);
  pinMode(back_m2p1, OUTPUT);
  pinMode(back_m2p2, OUTPUT);
  pinMode(bm2_speed, OUTPUT);

  speed_control(min_speed); //Set car to stationary at the beginning

  //Set up bluetooth signal and begin reading
  Serial.begin(9600);
  Blue.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:

 if (Blue.available()){
  blueData = Blue.read();
  
    // BLUETOOTH SPEED CONTROL RECEIVER PLACE FOR SPEEDS 0 TO 100
    // SET actual_speed variable to the received speed through analogwrite(pin, speed): speed ranges from 0% to 255 where 0 -> 0, and 100% -> 255
    // call the "speed_control" function, it takes in one input: actual_speed
    // INSERT HERE

    
  if (blueData == 'F'){ //Forward
      movement(Forward);
      //Serial.println("Moving Forward now..");
      delay(100);
    }
    if (blueData == 'G'){ //Forward Left
      turn(f_Left);
      //Serial.println("Moving Forward and Left now..");
      delay(100);
    }
    if (blueData == 'I'){ //Forward Right
      turn(f_Right);
      //Serial.println("Moving Forward and Right now..");
      delay(100);
    }
    if (blueData == 'B'){ //Back
       movement(Back);
       //Serial.println("Moving Back now..");
       delay(100);  
    }
    if (blueData == 'H'){ //Back Left
       turn(b_Left);
       //Serial.println("Moving Back and Left now..");
       delay(100);  
    }
    if (blueData == 'J'){ //Back Right
       turn(b_Right);
       //Serial.println("Moving Back and Right now..");
       delay(100);  
    }
    if (blueData == 'L'){ //Left
       turn(Left);
       //Serial.println("Moving Left now..");
       delay(100);  
    }
    if (blueData == 'R'){ //Right
       turn(Right);
       //Serial.println("Moving Right now..");
       delay(100);  
    }
    if ((blueData == 'D') or (blueData == 'S')){ //Stop or turn everything OFF
      movement(Stop);
      //Serial.println("Stopped and stationary..");
      delay(200);  
    }
    
  }else{
    Serial.println("Attempting to receive a command..");
    delay(100);
 }
}

//Function that changes the speed of the car wheels
void speed_control(int speed_in){
  analogWrite(fm1_speed, speed_in); 
  analogWrite(fm2_speed, speed_in);
  analogWrite(bm1_speed, speed_in);
  analogWrite(bm2_speed, speed_in);
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
