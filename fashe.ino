const int xPin = A0;
const int yPin = A1;
char lastCommand = 'S';
unsigned long lastExecuteTime = 0;
const unsigned long commandDuration = 2000;

void setup() {
  Serial.begin(9600);
  delay(100);
  //Serial.println("Transmitter Ready");
  lastCommand = 'Z'; // 初始化为不存在的命令，确保第一次发送
}

void loop() {
  //int xRaw = analogRead(xPin);
 /// int yRaw = analogRead(yPin);
  int xRaw = 310;
  int yRaw = 300;
  
  char newCommand = 'S';
  
  // 优先判断前后（Y轴）
  if (yRaw > 400) {
    newCommand = 'F';
  } else if (yRaw < 320) {
    newCommand = 'B'; 
  } 
  // 再判断左右（X轴）
  else if (xRaw < 320) {
    newCommand = 'L';
  } else if (xRaw > 400) {
    newCommand = 'R';
  }
    //Serial.print("Sent: ");
    Serial.println(newCommand);
    //Serial.print(" (X:");
    //Serial.print(xRaw);
    //Serial.print(" Y:");
    //Serial.print(yRaw);
    //Serial.println(")");
  // 发送命令（包括第一次和每次改变时）
  if (newCommand != lastCommand) {
    Serial.println(newCommand);
    lastCommand = newCommand;
    lastExecuteTime = millis();
    
    //Serial.print("Sent: ");
    //Serial.print(newCommand);
    //Serial.print(" (X:");
    //Serial.print(xRaw);
    //Serial.print(" Y:");
    //Serial.print(yRaw);
    //Serial.println(")");
  }
  
  delay(1000);
}