/*
Demonstrates reading DTMF keys from chip like MT8870 and driving motors with the help
of L293d bridge; making a Mobile controlled Robot.
Tones are read from the DTMF decoder and keys 2, 8, 4, 6 are used to move the robot
FORWARD, BACKWARD, LEFT and RIGHT.
The DTMF interrupt (INT1) is used to read a new key.

Check the below link for connections and other details
http://exploreembedded.com/wiki/index.php?title=Explore_Robo  

*/

int MotorLeft[2] = {8,9};		// Motor Pins
int MotorRight[2] = {10,11};	// Motor Pins

	
int Mobile[5]={4,5,6,7};	// DTMF mobile tones


volatile int NewTone_Flag = 0;
int volatile NewTone = 0;


void setup()
{
	MotorInit();
	MobileInit();
	attachInterrupt(1, CheckTone, FALLING);
	//Serial.begin(9600);
	//Serial.println("Mobile controlled Robo");
}


void loop()
{ 
	
	
	if(NewTone_Flag == 1)
	{ 
		NewTone = ReadTone();
		NewTone_Flag = 0;
	}
	
	switch(NewTone)
	{
		case 2: Robot_Forward();break;
		case 8: Robot_Backward(); break;
		//In order to have steering control over left and right movement, we turn left or right for a short moment and stop.
		//Notice that in order to use the delay() we need to disable the interuptts. 
		case 4: noInterrupts(); Robot_Right();delay(500); Robot_Stop(); NewTone=0; interrupts(); break;
		case 6: noInterrupts(); Robot_Left();delay(500); Robot_Stop(); NewTone = 0; interrupts(); break;
		case 5: Robot_Stop();break;
		default:Robot_Stop();
	}
	
}

void CheckTone()
{
	NewTone_Flag = 1;
}

int ReadTone()
{
	int MobileTone=0,i;
	
        for(i=0;i<4;i++)
        MobileTone|= digitalRead(Mobile[i])<<i;
	//MobileTone = (digitalRead(Mobile[3])*8)+ (digitalRead(Mobile[2])*4)+(digitalRead(Mobile[1])*2)+(digitalRead(Mobile[0])*1);
	//Serial.print(MobileTone);
	return MobileTone;
}

void MobileInit()
{
	int i;
	for(i=0 ; i<5; i++)
	{
		pinMode(Mobile[i],INPUT);
	}
	//first pin will be used as interrupt, hence direction set not required.
}

//Initialize the motor

void MotorInit()
{
	int i;
	for(i=0 ; i<2; i++)
	{
		pinMode(MotorLeft[i],OUTPUT);
		pinMode(MotorRight[i],OUTPUT);
	}
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


