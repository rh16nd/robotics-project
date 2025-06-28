#include <Servo.h>
char Th1, Th2, tmp;
Servo M1;
Servo M2;
int M1_ZERO = 100; //with respect to Center of Image
int M2_ZERO = 98;
const int laserPin = 7;

int M1_Min = M1_ZERO - 45;
int M1_Max = M1_ZERO + 45;

int M2_Min = M2_ZERO - 45;
int M2_Max = M2_ZERO + 45;

void setup() 
{
  Serial.begin(9600);
  M1.attach(2);
  M2.attach(3);
  pinMode(7, OUTPUT);
  M1.write(M1_ZERO);
  M2.write(M2_ZERO);
}
void Move_Motors(int th1, int th2) {
    // Constrain the input angles directly within the min and max limits
    
    int RobotAngle1 = M1_ZERO + th1;
    int RobotAngle2 = M2_ZERO - th2;
    RobotAngle1 = constrain(RobotAngle1, M1_Min, M1_Max);
    RobotAngle2 = constrain(RobotAngle2, M2_Min, M2_Max);

    // Debugging outputs to monitor servo positions
    Serial.print("M1 Position: ");
    Serial.println(RobotAngle1);
    Serial.print("M2 Position: ");
    Serial.println(RobotAngle2);

    // Move servos to calculated positions
    M1.write(RobotAngle1);
    M2.write(RobotAngle2);
    digitalWrite(7,HIGH);
    delay(3000);
    digitalWrite(7,LOW);
}
void loop() 
{
  delay(200);

  if(Serial.available()>=2)
  {
    Th1 = Serial.read();//decode -128
    Th2 = Serial.read();//decode -128

    //Remove any extra worng reading
    while(Serial.available()) tmp = Serial.read();    
    
    // Run the robotic arm here. For testing, we will 
    //switch On or switch off a LED according to Th1 value
    //if(Th1 ==1) digitalWrite(13,1);
    //else digitalWrite(13,0);

    Move_Motors(Th1, Th2); 
    
    Serial.print('1'); // This tell the PC that Arduino is Ready for next angles
  }
}
