/* This version of the code is the main wireless version uploaded onto the car
   for the car to work. This works without the Serial monitor on the computer.
 */

//To drive a motor to a direction, say, clockwise, the pin Input 1 must be high 
//while the pin Input 2 must be low. To drive the motor counter clockwise, 
//the pin Input 1 is low while the pin Input 2 is high.

// Initialize front motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
// For speed control, must use PMW Pins: 3, 5, 6, 9, 10, 11
int front_m1p1 = 7; // IN1 
int front_m1p2 = 8; // IN2 
int fm1_speed = 3; //Speed control for left front motor : ENA

int front_m2p1 = 5; //IN3 
int front_m2p2 = 4; //IN4 
int fm2_speed = 6; //Speed control for right front motor : ENB

// Initialize back motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
int back_m1p1 = 12; //IN1 
int back_m1p2 = 10; //IN2 
int bm1_speed = 9; //Speed control for left back motor : ENA

int back_m2p1 = 25; //IN3 
int back_m2p2 = 2; //IN4 
int bm2_speed = 11; //Speed control for right back motor : ENB

int led = 31; //LED to light up when a signal is detected by the HC-05

//Initialize movement keyword variables
String Forward = "Forward"; 
String Back = "Back";
String Stop = "Stop";
String Right = "Right";
String f_Right = "Front Right";
String b_Right = "Back Right";
String Left = "Left";
String f_Left = "Front Left";
String b_Left = "Back Left";

//Initialize max and min speeds of the car (255 -> 5 volts)
//Actual speed -> speed received from bluetooth module
int max_speed = 255;
int min_speed = 0;
int actual_speed = min_speed; //Car begins stationary

// Initialize bluetooth connection; RX pin 19; TX pin 18 -> arduino MEGA
// RX pin receives data while TX pin transmits data
char blueData; //Bluetooth data will be stored here
//Locks used to eliminate the flood of "S" signals in the chip, to achieve smooth motion
char lock1;
char lock2;
// Conversion and intData will be used for speed control and converting characters to integers
const int conversion = int('0');
int intData;

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
  pinMode(led, OUTPUT);
  
  //Set up bluetooth signal and begin reading
  Serial1.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:

 if (Serial1.available()){
  lock1 = Serial1.read();
  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  if (lock1 == 'S'){
    delay(50);
    lock2 = Serial1.read();
    if (lock2 == lock1){
       delay(50);
      blueData = 'S';
    }else{
        blueData = lock2;
      }
    }else{
    blueData = lock1;
  }
  intData = int(blueData);
  
  if ((int(intData - conversion) >= 0) && (int(intData - conversion) <= 9)){
    //Multiply by 10 to get speed, then by 2.55 to convert from 0->100 to 0->255
    speed_control(int(int(intData - conversion) * 25.5));
   }
   
  switch (blueData){
    case 'q':
      speed_control(max_speed);
      break;
      
    case 'F':
      movement(Forward);
      break;

    case 'G':
      turn(f_Left);
      break;

    case 'I':
      turn(f_Right);
      break;

    case 'B':
      movement(Back);
      break;

    case 'H':
      turn(b_Left);
      break;

    case 'J':
      turn(b_Right);
      break;

    case 'L':
      turn(Left);
      break;
     
    case 'R':
      turn(Right);
      break;
      
    case 'D':
      movement(Stop);
      break;
      
    case 'S':
      movement(Stop);
      break;
    }
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
