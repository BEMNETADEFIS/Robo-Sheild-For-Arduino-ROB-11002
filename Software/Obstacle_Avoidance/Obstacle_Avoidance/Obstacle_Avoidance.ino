/*
Obstacle avoiding Robot
*/

#include <NewPing.h>                    // library for ultrasonic sensor

#define US_TRIGGER_PIN  A3              // Sensor Trigger pin
#define US_ECHO_PIN     2               // sensor echo pin
#define MAX_DISTANCE 	10		// Maximum obstacle distance in cm

int MotorLeft[2] = {8,9};		// Motor Pins
int MotorRight[2] = {10,11};	// Motor Pins

NewPing sonar(US_TRIGGER_PIN, US_ECHO_PIN, MAX_DISTANCE);    // sensor object

unsigned int time;
unsigned int distance;
unsigned int distance_right_side;
unsigned int distance_left_side;

void setup()
{
  MotorInit();
}

void loop()
{
 	Robot_Forward();
        delay(1000);
	Scan_Obstacle();
//	if( distance == 0 )									//the distance value is 0 (which for the newping libary means no ping was returned) then...
	if(distance > MAX_DISTANCE || distance == 0)        //If there is nothing in front of the robot within MAX_DISTANCE or the distance value is 0 (which for the newping libary means no ping was returned) then...
	{
		Robot_Forward();                                // no obstacle detected, move robot forward
	} 
	else                                                //obstacle detected
	{		
		Robot_Stop();                                       
		Robot_Navigate();
	}

}

//Intialize the motor
void MotorInit()
{
	pinMode(MotorLeft[0],OUTPUT);
	pinMode(MotorLeft[1],OUTPUT);
	pinMode(MotorRight[0],OUTPUT);
	pinMode(MotorRight[1],OUTPUT);
}

//Robot Driving Functions
void Robot_Forward()
{
	digitalWrite(MotorLeft[0],0);
	digitalWrite(MotorLeft[1],1);
	digitalWrite(MotorRight[0],1);
	digitalWrite(MotorRight[1],0);   
}

void Robot_Backward()
{
	digitalWrite(MotorLeft[0],1);
	digitalWrite(MotorLeft[1],0);
	digitalWrite(MotorRight[0],0);
	digitalWrite(MotorRight[1],1);  
}

void Robot_Left()
{
	digitalWrite(MotorLeft[0],1);
	digitalWrite(MotorLeft[1],0);
	digitalWrite(MotorRight[0],1);
	digitalWrite(MotorRight[1],0);    
}

void Robot_Right()
{
	digitalWrite(MotorLeft[0],0);
	digitalWrite(MotorLeft[1],1);
	digitalWrite(MotorRight[0],0);
	digitalWrite(MotorRight[1],1);    
}

void Robot_Stop()
{
	digitalWrite(MotorLeft[0],0);
	digitalWrite(MotorLeft[1],0);
	digitalWrite(MotorRight[0],0);
	digitalWrite(MotorRight[1],0);
}

void Scan_Obstacle()
{
	time = sonar.ping(); 
	distance = time / US_ROUNDTRIP_CM;
	delay(200);
}


void Robot_Navigate()
{
	Robot_Right();
	delay(500);   
	Scan_Obstacle();	

	if( distance < MAX_DISTANCE )  	// obstacle detected, so move back
	{
		Robot_Backward();                                  
		delay(500);                                      
		Robot_Right();                                     
		delay(200);                                      
	}
}

