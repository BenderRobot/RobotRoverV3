// sketch_robot 2.6 by Benjamin LAURENS

#include <Wire.h>
#include <Servo.h>


#define directionA 4
#define moteurA 5
#define directionB 7
#define moteurB 6

#define ledCam 8
#define servo 9
#define SLAVE_ADDRESS 0x12
#define ledStart 13

Servo myservo;
int pos = 85;
int dataReceived = 0, commande = 0;


void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  myservo.attach(servo);
  pinMode(moteurA, OUTPUT);
  pinMode(directionA, OUTPUT);
  pinMode(moteurB, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(ledCam, OUTPUT);
  pinMode(ledStart, OUTPUT);
  Serial.println("Robot started, waiting for instruction ....");
  Serial.println("");
  
}

void loop()
{
  delay(15);
}

void receiveData(int byteCount)
{
  while(Wire.available())
  { 
    dataReceived = Wire.read();
    Serial.print("dataReceived ");
    Serial.println(dataReceived);
    Serial.print("commande ");
    Serial.println(commande);
    if(commande != 1 && dataReceived == 1)
    {
      Serial.println("Robot ON");
      digitalWrite(ledStart, HIGH);
      commande = 1;
      servoCam(8);
    }
    else if(commande == 1 && dataReceived == 4 || commande == 1 && dataReceived == 5)
    {
      Serial.println("Robot led");
      ledcam(dataReceived);
    }
    else if(commande == 1 && dataReceived >= 11 && dataReceived <= 19)
    {
      deplacement(dataReceived);
    }
    else if(commande == 1 && dataReceived >= 6 && dataReceived <= 10)
    {
      servoCam(dataReceived);
    }    
    else if(commande == 1 && dataReceived == 0)
    {
      digitalWrite(ledStart, LOW);
      digitalWrite(ledCam, LOW);
      analogWrite(moteurA, 0);
      analogWrite(moteurB, 0);
      servoCam(10);
      commande = 0;
      Serial.println("Robot OFF");
    }
  }
}

void ledcam(int commande)
{
  
  if (commande == 4)
  {
      digitalWrite(ledCam, HIGH);
      Serial.println("Led Camera ON");
      digitalWrite(ledCam, LOW);
  }
  else if (commande == 5)
  {
    digitalWrite(ledCam, HIGH);    
    Serial.println("Led Camera OFF");
    digitalWrite(ledCam, LOW); 
  }
}

void servoCam(int commande)
{
  if (commande == 6)
  {
    pos = 135;
    myservo.write(pos);      
    Serial.println("Robot 135");
  }
  else if (commande == 7)
  {
    pos = 110;
    myservo.write(pos);
    Serial.println("Robot 110");
  }
  else if (commande == 8)
  {
    pos = 85;
    myservo.write(pos);
    Serial.println("Robot 85");
  }
  else if (commande == 9)
  {
    pos = 70;
    myservo.write(pos);
    Serial.println("Robot 70");
  }
  else if (commande == 10)
  {
    pos = 50;
    myservo.write(pos);
    Serial.println("Robot 50");
  }
}


void deplacement(int commande)
{
  if(commande == 11)
  {
    analogWrite(moteurA, 500);
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 1);
    Serial.println("Forward");
  }
  else if(commande == 12)
  {
    analogWrite(moteurA, 500);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 1);
    Serial.println("light right");
  }
  else if(commande == 13)
  {
    analogWrite(moteurA, 500);
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 0);
    Serial.println("Right");
  }
  else if(commande == 14)
  {
    analogWrite(moteurA, 500);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 0);
    Serial.println("back Right");
  }
  else if(commande == 15)
  {
    analogWrite(moteurA, 500);
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 0);
    Serial.println("Back");
  }
  else if(commande == 16)
  {
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 0);
    Serial.println("back left");
  }
  else if(commande == 17)
  {
    analogWrite(moteurA, 500);
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 1);
    Serial.println("Left");
  }
  else if(commande == 18)
  {
    
    analogWrite(moteurB, 500);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 1);
    Serial.println("go left");
  }
  else if(commande == 19)
  {
    analogWrite(moteurA, 0);
    analogWrite(moteurB, 0);
    Serial.println("Stop");
  }
} 
