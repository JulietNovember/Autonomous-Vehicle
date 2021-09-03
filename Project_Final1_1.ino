
//This program was created by John Nasir for Summer 2021 Automotive Mechatronics term proect for Nashwan Sebi with the use of Adafruit Libraries for the VL530X
// and assisted by a test program supplied by the manufacturer Adafruit



#include "Adafruit_VL53L0X.h"
#include <Pixy2.h>

Pixy2 pixy;


double distanceLast = 0;
double velocity1 = 0 ;
double distanceNow = 0;
double velocityLast = 0;
double velocityNow = 0;
double acceleration = 0 ;
int lineLength;
int x = 1;
int Color;
int lineDistanceX;
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int ENA = 9;
const int ENB = 3;
int Speed1=0;
int Speed2=0;
int z = 0;
int flag = 0;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

   Serial.print("Starting...\n");
 
  pixy.init();
  
  
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
//   Highway();
   trafficLight();
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
//   power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  
  VL53L0X_RangingMeasurementData_t measure;
    
 // Serial.print("Reading a measurement... ");

 
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  //flag = 0;
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
   // Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);

    distanceNow = measure.RangeMilliMeter;
    //Serial.print("Distance Now: ");
    //Serial.println(distanceNow);


    velocity1 = (distanceNow - distanceLast) / 1       ;    //Change in disance over time 


  //  Serial.print("Distance Last: ");
   // Serial.println(distanceLast);
    
    distanceLast = measure.RangeMilliMeter; //Reset last distance

    //Serial.print("Velocity 1: "); 
    //Serial.println(velocity1);

    acceleration = (velocity1 - velocityLast) / 10;
 velocityLast = velocity1;
 pixy.ccc.getBlocks();
delay(200);
//Serial.println(pixy.ccc.numBlocks);
 if (distanceNow < 120)
    {
      Serial.print("Distance :");
      Serial.println(distanceNow);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      pixy.ccc.getBlocks();
     
    }


 else if (pixy.ccc.numBlocks > 0)  //If light detected
    {
      //pixy.ccc.getBlocks();
      trafficLight();
     
    }

//else if (pixy.ccc.numBlocks <= 0)
////{
//Serial.println(pixy.line.numBarcodes);
//pixy.line.getAllFeatures();
//delay(2000);
//if (pixy.line.barcodes > 0)
//{
//  Serial.println("second if");
//
//}
//}



 

//else if (pixy.ccc.numBlocks == 0)
//{
//
//pixy.line.getMainFeatures();
//if (pixy.line.numBarcodes > 0)
//{
//  Turn();
//}
//else
//{
//  pixy.ccc.getBlocks();
//}
 




 
 else
 {
 Highway();
  }
  }

}



 void trafficLight(){

  Serial.println("trafficLight function called");
 int i;
  // grab blocks!
  pixy.ccc.getBlocks();
 
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    
 //   for (i=0; i<pixy.ccc.numBlocks; i++) //Determine if this statement is necessary
   // {
     
     // Serial.println(pixy.ccc.blocks[i].m_signature );
  switch (pixy.ccc.blocks[i].m_signature) {
  case 1:
      Serial.println(pixy.ccc.blocks[i].m_y);
     Speed1 = constrain(map(pixy.ccc.blocks[i].m_y,43,91,0,85),0,80);
     Speed2 = constrain(map(pixy.ccc.blocks[i].m_y,43,91,0,75),0,60);
     Serial.print("Speed 1 : ");
     Serial.println(Speed1);
     Serial.println("Speed 2:  ");
     Serial.println(Speed2);
     analogWrite(ENB,Speed1);
     analogWrite(ENA,Speed2);
      
  break;
  case 2: 
     Serial.println(pixy.ccc.blocks[i].m_y);
     Speed1 = constrain(map(pixy.ccc.blocks[i].m_y,70,95,0,80),0,100);
     Speed2 = constrain(map(pixy.ccc.blocks[i].m_y,70,95,0,65),0,80);
     Serial.print("Speed 1 : ");
     Serial.println(Speed1);
     Serial.println("Speed 2:  ");
     Serial.println(Speed2);
     analogWrite(ENB,Speed1);
     analogWrite(ENA,Speed2);
     
  break;
  case 3:
  Serial.println(pixy.ccc.blocks[i].m_y);
  Highway();
     
  break;
  
  case 4:
  Serial.println(pixy.ccc.blocks[i].m_y); 
  Speed1 = constrain(map(pixy.ccc.blocks[i].m_y,40,108,0,80),0,100);
  Speed2 = constrain(map(pixy.ccc.blocks[i].m_y,40,108,0,75),0,80);
  Serial.print("Speed 1 : ");
     Serial.println(Speed1);
     Serial.println("Speed 2:  ");
     Serial.println(Speed2);
     analogWrite(ENB,Speed1);
     analogWrite(ENA,Speed2);
  if (pixy.ccc.blocks[i].m_y <= 70)
  {
    Serial.println("__________");
   Turn();
  }
  break;
    }
  }
 }
//As of right now, i believe if there is a car in front of of our car, our car will not detect the white line and
//therefore this part will not execute

      
    //Serial.print("Velicity Last");
    //Serial.println(velocityLast);
    
    // Serial.print("Velocity Now:  ");
    // Serial.println(velocity1);
    
    // Serial.print("Distance : ");
    // Serial.println(distanceNow);
    
    //Serial.print("Acceleration");
    //Serial.println(acceleration);
   


  void Highway()
{
  
Serial.println("CAS and ACC Online");

    if (distanceNow >= 304 && distanceNow <= 1066)    //304 is the 12 in minimum distance for cruise control while 1066 is the upper limit that the ladar can detect (3.5 ft)
    {
 //    digitalWrite(IN1, LOW);
//  digitalWrite(IN2, HIGH);
 // digitalWrite(IN3, LOW);
 // digitalWrite(IN4, HIGH);

    
    int Speed2 = map(distanceNow, 304, 1066, 0, 180);     //Map these upper limits to 0 and max speed on the motors
    int Speed1 = map(distanceNow, 304, 1066, 0, 155);

    analogWrite(ENB, Speed2);
    analogWrite(ENA, Speed1);
    //Serial.print("Driving Speed 1: ");
    //Serial.println(Speed1);
    //Serial.print("Driving Speed 2: ");
     // Serial.println(Speed2);
    }
    
    else if (distanceNow > 1066)
    {
 //   digitalWrite(IN1, LOW);
 // digitalWrite(IN2, HIGH);
 // digitalWrite(IN3, LOW);
 // digitalWrite(IN4, HIGH);
     
      analogWrite(ENA, 150);
     analogWrite(ENB, 150);
      //Serial.print("Driving Speed 1: ");
      //Serial.println(Speed1);
      //Serial.print("Driving Speed 2: ");
      //Serial.println(Speed2);
    }
    else if (distanceNow < 304) 
    {
     
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      //Serial.print("Driving Speed: ");
      //Serial.println(Speed1);
      //Serial.print("Driving Speed 2: ");
      //Serial.println(Speed2);
     
    }
      
   
  
  else {
    Serial.println(" out of range ");
    //analogWrite(ENA,255);
    //analogWrite(ENB,235);
    //Uncomment above two lines to enable driving while the ladar does not detect anything in front 
    //(Warning, this could cause the car to drive indefinetly in open areas.
  }
delay(10);
 // pixy.ccc.getBlocks();

  }



void Turn()

{
 Serial.print("TURN FUNCTION CALLED");
 analogWrite(ENA, 80);
  analogWrite(ENB, 80);
  delay(500);
 analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(300);
  analogWrite(ENA, 150);
  analogWrite(ENB, 0);
  delay(1000);
 analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  pixy.ccc.getBlocks();

  }


     
