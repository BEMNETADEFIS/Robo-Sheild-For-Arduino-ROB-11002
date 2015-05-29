/*

The Explore Robo kit has 3 Light Sensors (LDR's) connected to arduino pins
8(Left), 9(Middle) and 10(Right)

Note that these inputs are from the sensor sheild.
The sensor sheild has a comparator, and outputs a logical 1 whenever light falls
on a particular sensor.

Check the below link for connections and other details
http://exploreembedded.com/wiki/index.php?title=Explore_Robo 


*/

int MotorLeft[2] = {8,9};		// Motor Pins
int MotorRight[2] = {10,11};	// Motor Pins

int Sensors[3]= {A0,A1,A2};		//Sensor input (left, middle, right)
void setup()
{
	MotorInit();
	SensorsInit();
	
	//Serial.begin(9600);
	//Serial.println("Light Follower Robot");
}


void loop()
{ 
	
     if( digitalRead(Sensors[0])==1)
        Robot_Left();
     else if( digitalRead(Sensors[1])==1)
        Robot_Forward();
     else if( digitalRead(Sensors[2])==1)
        Robot_Right();
    	
}


//configure sensors as input
void SensorsInit()
{
	int i;
	for(i=0 ; i<3; i++)
	{
		pinMode(Sensors[i],INPUT);
    }
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


