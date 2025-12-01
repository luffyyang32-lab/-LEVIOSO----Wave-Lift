#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // 格式: 
AF_DCMotor MotorFR(1);
AF_DCMotor MotorFL(2);
AF_DCMotor MotorBL(3);
AF_DCMotor MotorBR(4);

int valSpeed = 200;
unsigned long motorStartTime = 0;
const unsigned long motorDuration = 2000;
unsigned long lastDebugTime = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // 初始化软串口，波特率设为9600

  MotorFL.setSpeed(valSpeed);
  MotorFR.setSpeed(valSpeed);
  MotorBL.setSpeed(valSpeed);
  MotorBR.setSpeed(valSpeed);

  MotorFL.run(RELEASE);
  MotorFR.run(RELEASE);
  MotorBL.run(RELEASE);
  MotorBR.run(RELEASE);

  Serial.println("READY - Gesture Control Car");
  delay(100);
}

void loop() {
  if (millis() - lastDebugTime > 2000) {
    Serial.print("Receiver running... ");
    Serial.println(Serial.available());
    lastDebugTime = millis();
  }

  if (motorStartTime > 0 && (millis() - motorStartTime >= motorDuration)) {
    Serial.println("AUTO STOP after 2s");
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
    motorStartTime = 0;
  }

  if (Serial.available() > 0) {
    Serial.print("Got data: ");
     if (mySerial.available() > 0) {      // 检查是否有数据可读
    char cmd = mySerial.read(); // 读取一个字符
    //command.trim();
    Serial.print("Received: ''");
    Serial.print(cmd);
    Serial.print("''");
    Serial.println();

    
      switch(cmd) {
        case 'F': 
          Serial.println("ACTION: FORWARD");
          motorStartTime = millis();
          MotorFL.run(FORWARD);
          MotorFR.run(FORWARD);
          MotorBL.run(FORWARD);
          MotorBR.run(FORWARD);
          break;

        case 'B':
          Serial.println("ACTION: BACKWARD");
          motorStartTime = millis();
          MotorFL.run(BACKWARD);
          MotorFR.run(BACKWARD);
          MotorBL.run(BACKWARD);
          MotorBR.run(BACKWARD);
          break;

        case 'L':
          Serial.println("ACTION: LEFT");
          motorStartTime = millis();
          MotorFL.run(BACKWARD);
          MotorFR.run(FORWARD);
          MotorBL.run(BACKWARD);
          MotorBR.run(FORWARD);
          break;

        case 'R':
          Serial.println("ACTION: RIGHT");
          motorStartTime = millis();
          MotorFL.run(FORWARD);
          MotorFR.run(BACKWARD);
          MotorBL.run(FORWARD);
          MotorBR.run(BACKWARD);
          break;

        case 'S':
          Serial.println("ACTION: STOP");
          motorStartTime = 0;
          MotorFL.run(RELEASE);
          MotorFR.run(RELEASE);
          MotorBL.run(RELEASE);
          MotorBR.run(RELEASE);
          break;
      }
  }
}