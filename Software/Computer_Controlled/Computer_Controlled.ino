/*
Reads keys w,s,a,r from keyboard(with USB) and controls the Explore Robo


*/

int MotorLeft[2] = {8,9};		// Motor Pins
int MotorRight[2] = {10,11};	// Motor Pins

void setup()
{
Serial.begin(9600);
MotorInit();
Serial.print("*Explore Robo Mode Computer: Controlled*\n\r");
Serial.println("Commands:\n W->Forward \n S->Backwards \n A->Left \n D->Right");
}

void loop()
{
int command; 
command = Serial.read();
  switch(command)
 {
    case 'w': Robot_Forward(); delay(100); Robot_Stop();break; 
    case 's': Robot_Backward(); delay(100);Robot_Stop(); break;  
    case 'a': Robot_Left(); delay(100); Robot_Stop();break;
    case 'd': Robot_Right(); delay(100);Robot_Stop(); break; 
    //in case the caps lock is ON
    case 'W': Robot_Forward(); delay(100);Robot_Stop(); break; 
    case 'S': Robot_Backward(); delay(100);Robot_Stop(); break;  
    case 'A': Robot_Left(); delay(100);Robot_Stop(); break;
    case 'D': Robot_Right(); delay(100);Robot_Stop(); break;      
    default: break; 
 }     
}

//Intialize the motor
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


