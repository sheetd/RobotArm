/*
RobotArm v1.0  
2013-08-10 by Neil Meredith <neil@sheetd.com>  
*/


#include <AFMotor.h>

AF_DCMotor motor1(1);  // Instantiate all the motors
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor motor(1);  //new motor for subroutine
int motorNumber = 0;  // variable to store motor number
byte motorSpeed = 0;  // varialbe to store the motor speed (0-255)
boolean motorDirecton = false;  // variable to store motor direction (FORWARD/BACWARD)
int motorTime = 0;  // variable to store motor move time (in Milliseconds)


// Subroutine that waits for the user to hit enter
void input()    
  {
  int incomingByte = 0;	// for incoming serial data
  motor1.setSpeed(0);     // stop the motor
  Serial.println("Hit return for next motion");   
  while (incomingByte != 13)  // 13 is the ASCII code for "enter"
    {
	if (Serial.available() > 0) 
         {   
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:
		Serial.print("I received: ");
		Serial.println(incomingByte, DEC);
	 }
     }
  }

// Subroutine to move motor
void motorMove(int motorNumber, byte motorSpeed, boolean motorDirection,int motorTime) {
  // Serial.print("moving...");
  // something to set the motor #
  motor.setSpeed(motorSpeed);
  // if then to sort motor direction
  motor.run(FORWARD);
  delay (motorTime);
  motor.setSpeed(0);
}



void setup() {
  Serial.begin(9600);       // set up Serial library at 9600 bps
  Serial.println("Robot Arm Controller V1.0");
  }


void loop() {
  start:
  
  // input();  // wait for user to hit return
  
  // FUTURE CODE HERE -- Way to Zero out the robot without using keypad
  // Select motor
  // move left and right with arror keys

// Select the motor to move manually
if (Serial.available() > 0) {
    int inByte = Serial.read();
    Serial.print("Select motor number 1-4");
    switch (inByte) {
    case '1':    
      motor1.setSpeed(255);
      Serial.print("Motor 1 Selected");
      break;
    case '2':    
      motor2.setSpeed(255); 
      Serial.print("Motor 2 Selected");
      break;
    case '3':    
      motor3.setSpeed(255);
      Serial.print("Motor 3 Selected");
      break;
    case '4':    
      motor4.setSpeed(255);
      Serial.print("Motor 4 Selected");
      break;
    default:
      motor1.setSpeed(255);
      motor2.setSpeed(255);
      motor3.setSpeed(255);
      motor4.setSpeed(255);
    ;
    }
  } 

jog:
// Move motors for 1 second in a given direction
if (Serial.available() > 0) {
    int inByte = Serial.read();
    Serial.print("Use '<' for Left movement, '>' for Right movement, 'm' to assign another motor, or 'esc' to escape");
    switch (inByte) {
    case 60: // '<'  input    
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      delay (1000);
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      motor3.setSpeed(0);
      motor4.setSpeed(0);
      goto jog;
      break;
    case 62: // '>' input   
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      delay (1000);
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      motor3.setSpeed(0);
      motor4.setSpeed(0);
      goto jog;
      break;
    case 'm': // 'm' input   
      goto start;
      break;
    case 27: // 'esc' input   
      goto program;
      break;
    default:
    ;
    }
  } 

  Serial.print("Hit Return to run program");
  input();  // wait for user to hit return

program:
// Main motor program 
  Serial.println("Begin sequence of moves"); 
  motor1.setSpeed(255);     // set the speed to 255/255
  motor1.run(FORWARD);
  motor2.setSpeed(255);     // set the speed to 255/255
  motor2.run(FORWARD);
  motor3.setSpeed(255);     // set the speed to 255/255
  motor3.run(FORWARD);
  motor4.setSpeed(255);     // set the speed to 255/255
  motor4.run(FORWARD);
  delay (1000);             // run for 1 second
  motor1.setSpeed(0);       // turn off motors
  motor2.setSpeed(0);   
  motor3.setSpeed(0);    
  motor4.setSpeed(0);   
    
//move M4 counterclockwise
  Serial.print("moving...");
  motor4.setSpeed(100);
  motor4.run(BACKWARD);
  delay (2000);
  motor4.setSpeed(0);
  
  goto start;
  }


