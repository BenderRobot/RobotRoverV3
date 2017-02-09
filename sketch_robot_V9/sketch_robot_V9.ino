// library
#include <Wire.h>
#include <Servo.h>

// I2C message to robot OFF
#define CMD_POWER_OFF 10
// I2C message to robot ON
#define CMD_POWER_ON 11
// I2C message to led camera OFF
#define CMD_LED_CAM_OFF 4
// I2C message to led camera ON
#define CMD_LED_CAM_ON 5
// I2C message to move servo to up
#define CMD_SERVO_UP 30
// I2C message to center servos
#define CMD_SERVO_CENTER 34
// I2C message to move servo to down
#define CMD_SERVO_DOWN 31
// I2C message to move servo to up
#define CMD_SERVO_RIGHT 33
// I2C message to center servos
#define CMD_SERVO_LEFT 32
// I2C message to stop all moves
#define CMD_MOVE_STOP 19
// I2C message to move forward
#define CMD_MOVE_FORWARD 20
// I2C message to move backward
#define CMD_MOVE_BACKWARD 21
// I2C message to turn left
#define CMD_TURN_LEFT 22
// I2C message to turn right
#define CMD_TURN_RIGHT 23

// max and min servo angles
#define MAX_ANGLE_PAN 180
#define MIN_ANGLE_PAN 10
#define MAX_ANGLE_TILT 120
#define MIN_ANGLE_TILT 50
#define STEP 2
#define TIME_PAUSE 50

// pin moteur A
#define moteurA 4
#define directionA 5

// pin moteur B
#define moteurB 6
#define directionB 7

// constant speed and dir
#define SPEED 500
#define TURN_SPEED 250
#define GO 0
#define BCK 1

// other pins
#define servoTilt 9
#define servoPan 8
#define ledStart 13

//slave adrress I2C 
#define SLAVE_ADDRESS 0x12

// servo objects
Servo servoCamTilt;
Servo servoCamPan;

// volattile variables
volatile int servoPosCenter = 80;
volatile int servoAngleTilt = 80;
volatile int servoAnglePan = 80;
volatile int on = 0;
// I2C variables M=>S
volatile byte cmd = 0;
volatile byte tempCmd = 0;
volatile byte test_send = 0;


void setup() {
  
  //serial communication
  Serial.begin(9600);
  
  // I2C communication
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  // connect servo
  servoCamTilt.attach(servoTilt);
  servoCamPan.attach(servoPan);

  // init pinMode
  pinMode(moteurA, OUTPUT);
  pinMode(directionA, OUTPUT);
  pinMode(moteurB, OUTPUT);
  pinMode(directionB, OUTPUT);
  //pinMode(ledCam, OUTPUT);
  pinMode(ledStart, OUTPUT);
  
  Serial.println("Robot started, waiting for instruction ....");
  Serial.println("");
}

void loop() {
  // Execute received commands
  if (cmd != 0) {
    switch (cmd) {
      case CMD_POWER_ON:
         powerOn();
         break;
       case CMD_POWER_OFF:
         powerOff();
         break;
       /*case CMD_LED_CAM_ON:
         ledCamOn();
         break;
       case CMD_LED_CAM_OFF:
         ledCamOff();
         break;*/
       case CMD_SERVO_UP:
         servoUp();
         break;
       case CMD_SERVO_CENTER:
         servoCenter();
         break;
       case CMD_SERVO_DOWN:
         servoDown();
         break;
       case CMD_SERVO_RIGHT:
         servoRight();
         break;
       case CMD_SERVO_LEFT:
         servoLeft();
         break;
       case CMD_MOVE_STOP:
         moveStop();
         break;  
       case CMD_MOVE_FORWARD:
          if(on) { moveForward(); }
          break;
        case CMD_MOVE_BACKWARD:
          if(on) { moveBackward(); }
          break;
        case CMD_TURN_LEFT:
          if(on) { turnLeft(); }
          break;
        case CMD_TURN_RIGHT:
          if(on) { turnRight(); }
          break;
    }
    tempCmd = cmd;
    if ( cmd < 29 )
    { 
      cmd = 0;
    }
  }
}

void receiveData(int byteCount) {
  if(byteCount == 1) {
    cmd = Wire.read();
    Serial.print("Data Received ");
    Serial.println(cmd);
  }
}

void sendData(){
  byte data[] = {servoAngleTilt, servoAnglePan};
  //byte data0 = servoAngleTilt;
  //byte data1 = servoAnglePan;
  if(test_send == 0) {
    Wire.write(data[0]);//5
    Serial.println(data[0]);
    test_send = 1;
  }
  else {
    Wire.write(data[1]);
    Serial.println(data[1]);
    test_send = 0;
  }
  Serial.println("Send DATA");
}

void powerOn() {
  Serial.println("Robot ON");
  digitalWrite(ledStart, HIGH);
  on = 1; 
  servoCenter();
}

void powerOff() {
  Serial.println("Robot OFF");
  digitalWrite(ledStart, LOW);
  //digitalWrite(ledCam, LOW);
  analogWrite(moteurA, 0);
  analogWrite(moteurB, 0);
  servoCenter();
  on = 0;
}

/*void ledCamOn() {
   digitalWrite(ledCam, HIGH);
   Serial.println("Led Camera ON");
   digitalWrite(ledCam, LOW);
   onLed = 1;
}
void ledCamOff() {
   digitalWrite(ledCam, HIGH);
   Serial.println("Led Camera OFF");
   digitalWrite(ledCam, LOW);
   onLed = 0;
}*/

void servoUp() {
  if(on == 1 && servoAngleTilt < MAX_ANGLE_TILT) {
    servoAngleTilt += STEP;
    servoCamTilt.write(servoAngleTilt);
    delay(TIME_PAUSE); 
    Serial.println("Servo UP");
  }
}
void servoDown() {
  if(on == 1 && servoAngleTilt > MIN_ANGLE_TILT) {
    servoAngleTilt -= STEP;
    servoCamTilt.write(servoAngleTilt);
    delay(TIME_PAUSE);
    Serial.println("Servo DOWN");
  }
}
void servoLeft() {
  if(on == 1 && servoAnglePan < MAX_ANGLE_PAN) {
    servoAnglePan += STEP;
    servoCamPan.write(servoAnglePan); 
    delay(TIME_PAUSE);
    Serial.println("Servo LEFT");
  }
}
void servoRight() {
  if(on == 1 && servoAnglePan > MIN_ANGLE_PAN) {
    servoAnglePan -= STEP;
    servoCamPan.write(servoAnglePan); 
    delay(TIME_PAUSE);
    Serial.println("Servo RIGHT");
  }
}
void servoCenter() {
  servoCamTilt.write(servoPosCenter);
  servoAngleTilt = servoPosCenter;
  delay(200);
  servoCamPan.write(servoPosCenter);
  servoAnglePan = servoPosCenter;
  Serial.println("Servo CENTER");
}
void moveStop() {
  analogWrite(moteurA, 0);
  analogWrite(moteurB, 0);
  Serial.println("Stop");
}
void moveForward() {
  analogWrite(moteurA, SPEED);
  analogWrite(moteurB, SPEED);
  digitalWrite(directionA, GO);
  digitalWrite(directionB, GO);
  Serial.println("Forward");
}
void moveBackward() {
  analogWrite(moteurA, SPEED);
  analogWrite(moteurB, SPEED);
  digitalWrite(directionA, BCK);
  digitalWrite(directionB, BCK);
  Serial.println("Backward");
}
void turnLeft() {
  analogWrite(moteurA, TURN_SPEED);
  analogWrite(moteurB, TURN_SPEED);
  digitalWrite(directionA, GO);
  digitalWrite(directionB, BCK);
  Serial.println("Left");
}
void turnRight() {
  analogWrite(moteurA, TURN_SPEED);
  analogWrite(moteurB, TURN_SPEED);
  digitalWrite(directionA, BCK);
  digitalWrite(directionB, GO);
  Serial.println("Right");
}
