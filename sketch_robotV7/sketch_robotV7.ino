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
int pos = 100;
int dataReceived = 0, commande = 0 ,i;


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
    Serial.print(dataReceived);
    Serial.println(commande);
    if(commande != 1 && dataReceived == 1)
    {
      Serial.println("Robot ON");
      digitalWrite(ledStart, HIGH);
      commande = 1;
      servoCam(11);
    }
    else if(commande == 1 && dataReceived == 30 || commande == 1 && dataReceived == 20)
    {
      ledcam(dataReceived);
    }
    else if(commande == 1 && dataReceived >= 4 && dataReceived <= 8)
    {
      deplacement(dataReceived);
    }
    else if(commande == 1 && dataReceived >= 9 && dataReceived <= 13)
    {
      servoCam(dataReceived);
    }    
    else if(commande == 1 && dataReceived == 0)
    {
      digitalWrite(ledStart, LOW);
      digitalWrite(ledCam, LOW);
      analogWrite(moteurA, 0);
      analogWrite(moteurB, 0);
      servoCam(12);
      commande = 0;
      Serial.println("Robot OFF");
    }
  }
}

void ledcam(int commande)
{
  if (commande == 30)
  {
    for(i = 0; i < 3; i++)
    {
      digitalWrite(ledCam, HIGH);
      Serial.println("Led Camera ON");
      digitalWrite(ledCam, LOW);
      delay(10000);
    }
  }
  else if (commande == 20 && i == 3)
  {
    digitalWrite(ledCam, HIGH); 
    Serial.println("Led Camera OFF");
    digitalWrite(ledCam, LOW);    
  }
}

void servoCam(int commande)
{
  if (commande == 9)
  {
    pos = 150;
    myservo.write(pos);      
    Serial.println("Robot 140");
  }
  else if (commande == 10)
  {
    pos = 120;
    myservo.write(pos);
    Serial.println("Robot 110");
  }
  else if (commande == 12)
  {
    pos = 70;
    myservo.write(pos);
    Serial.println("Robot 70");
  }
  else if (commande == 13)
  {
    pos = 55;
    myservo.write(pos);
    Serial.println("Robot 55");
  }
  else if (commande == 11)
  {
    if(pos > 85)
    {
      for(pos = pos; pos >= 85; pos--)
      {
        myservo.write(pos);
        delay(500);
      }
    }
    else
    {
      for(pos = pos;pos <= 85; pos++)
      {
        myservo.write(pos);
        delay(500);
      }
    }
    Serial.println("Robot 80");
  }
}


void deplacement(int commande)
{
  if(commande == 4)
  {
    analogWrite(moteurA, 400);
    analogWrite(moteurB, 400);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 1);
    Serial.println("Forward");
  }
  else if(commande == 6)
  {
    analogWrite(moteurA, 400);
    analogWrite(moteurB, 400);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 0);
    Serial.println("Back");
  }
  else if(commande == 5)
  {
    analogWrite(moteurA, 400);
    analogWrite(moteurB, 400);
    digitalWrite(directionA, 1);
    digitalWrite(directionB, 0);
    Serial.println("Right");
  }
  else if(commande == 7)
  {
    analogWrite(moteurA, 400);
    analogWrite(moteurB, 400);
    digitalWrite(directionA, 0);
    digitalWrite(directionB, 1);
    Serial.println("Left");
  }
  else if(commande == 8)
  {
    analogWrite(moteurA, 0);
    analogWrite(moteurB, 0);
    Serial.println("Stop");
  }
} 
