//To drive a motor to a direction, say, clockwise, the pin Input 1 must be high 
//while the pin Input 2 must be low. To drive the motor counter clockwise, 
//the pin Input 1 is low while the pin Input 2 is high.

// Initialize front motors 1 and 2; Motor 1 is on the left and Motor 2 is on the right
// When viewed from above the car with the car's front facing away from the observer
// For speed control, must use PMW Pins: 3, 5, 6, 9, 10, 11
int front_m1p1 = 25; // IN1
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

//LED used to visually see when the chip receives a signal when it lights up
int led = 31; 

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

//Initialize max speed (255 -> 5 volts)
//Actual speed -> speed received from bluetooth module
int max_speed = 255;
int actual_speed = 0; //Car begins stationary

// Initialize bluetooth connection
// RX pin 19; TX pin 18 -> arduino MEGA
// RX pin receives data while TX pin transmits data
char blueData; //Bluetooth data will be stored here
char lock1;
char lock2;
char lock3;

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
  
  //Set up bluetooth signal on hardware serial and begin reading at 115200 baud
  Serial1.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:

//The locks are used to eliminate the "S" signal received through the app.
// The signal floods the chip and is therefore unable to smoothly read other signals
// By eliminating this signal so that one-off "S" signals are not "read" the car can move smoothly
 if (Serial1.available()){
  lock1 = Serial1.read();
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  if (lock1 == 'S'){
    delay(50);
    lock2 = Serial1.read();
    if (lock2 == lock1){
       delay(50);
       lock3 = Serial1.read();
       if (lock3 == lock2){
        blueData = lock3;
        }else{
          blueData = lock3;
          }
      }else{
        blueData = lock2;
        }
    }else{
    blueData = lock1;
  }
  
  if (((int(blueData)-int('0')) >= 0) && ((int(blueData)-int('0')) <= 9)){
    //Multiply by 10 to get speed, then by 2.55 to convert from 0->100 to 0->255
    //Add 0.5 for rounding purposes then change it to an int which truncates it
    speed_control(int((int(blueData)-int('0')) * 25.5));
   }
   if (blueData == 'q'){
    speed_control(max_speed);
    }
    if (blueData == 'F'){ //Forward
      movement(Forward);
    }
    if (blueData == 'G'){ //Forward Left
      turn(f_Left);
    }
    if (blueData == 'I'){ //Forward Right
      turn(f_Right);
    }
    if (blueData == 'B'){ //Back
       movement(Back);
    }
    if (blueData == 'H'){ //Back Left
       turn(b_Left);
    }
    if (blueData == 'J'){ //Back Right
       turn(b_Right);
    }
    if (blueData == 'L'){ //Left
       turn(Left);
    }
    if (blueData == 'R'){ //Right
       turn(Right);
    }
    if ((blueData == 'D') or (blueData == 'S')){ //Stop or turn everything OFF
      movement(Stop);
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
