// lcd serial line
const int TxPin = 6;
// blue tooth serial line
const int BtTxPin = 9;

// left joystick
int LEFT_UD = 0;
int LEFT_LR = 0;

// right joystick
int RIGHT_UD = 0;
int RIGHT_LR = 0;

// starting mode
int mode = 1;
// mode button
int buttonPin = 4;
int buttonVal = 0;

#include <SoftwareSerial.h>
// lcd serial connection
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
// bluetooth serail connection
SoftwareSerial btSerial = SoftwareSerial(255, BtTxPin);

void setup(){
  // init serial
  Serial.begin(9600);
  // init lcd serial
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12);   // Clear             
  mySerial.write(17);   // Turn backlight on
  delay(5);             // Required delay
  
  // init blue tooth serial
  // init lcd serial
  pinMode(BtTxPin, OUTPUT);
  digitalWrite(BtTxPin, HIGH);
  btSerial.begin(9600);
  
  // init mode push button
  pinMode(buttonPin, INPUT);
}

void loop(){
  // read left joystick values
  LEFT_UD = analogRead(A1); 
  LEFT_LR = analogRead(A0);
  // read right joystick values
  RIGHT_UD = analogRead(A3);
  RIGHT_LR = analogRead(A2);
  
  
  LEFT_UD = map(LEFT_UD, 0, 1023, -19, 19);
  LEFT_LR = map(LEFT_LR, 0, 1023, -19, 19);
  RIGHT_UD = map(RIGHT_UD, 0, 1023, -60, 60)+1;
  RIGHT_LR = map(RIGHT_LR, 0, 1023, -60, 60)-2;
  

  
  buttonVal = digitalRead(buttonPin);  // read input value
  if (buttonVal == HIGH) {         // check if the input is HIGH (button released)
    
  } else {
    mode += 1;
    if(mode > 3){
      mode = 1; 
    }
  }
  
  mySerial.write(12);   // Clear 
  delay(5);             // Required delay

  // send data to serial
  Serial.print("Left U/D : ");
  Serial.print(LEFT_UD);
  Serial.print(" ");
  Serial.print("Left L/R : ");
  Serial.print(LEFT_LR);
  Serial.print("  ");
  Serial.print("Right U/D : ");
  Serial.print(RIGHT_UD);
  Serial.print(" ");
  Serial.print("Right L/R : ");
  Serial.println(RIGHT_LR);

  // send data to lcd
  if(mode == 1){
    mySerial.print("Body Translation");
    mySerial.print(LEFT_UD);
    mySerial.print(" ");
    mySerial.print(LEFT_LR);
    mySerial.print("    ");
    mySerial.print(RIGHT_UD);
    mySerial.print(" ");
    mySerial.print(RIGHT_LR);
  }else if(mode == 2){
    mySerial.print("Walking Mode");
  }else if(mode == 3){
    mySerial.print("IMU Mode"); 
  }

 
  // transmit data over blue tooth
  btSerial.print("l_ud:");
  btSerial.print(LEFT_UD);
  btSerial.print("!l_lr:");
  btSerial.print(LEFT_LR);
  btSerial.print("!r_ud:");
  btSerial.print(RIGHT_UD);
  btSerial.print("!r_lr:");
  btSerial.print(RIGHT_LR);
  btSerial.print("!mode:");
  btSerial.print(mode);
  btSerial.print("!\n");
    
  delay(50);
}
