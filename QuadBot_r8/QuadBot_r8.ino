#include "nuke.h"
String command = ""; // command buffer for ssc-32

/*mode breakdown
 1 = body translation (default)
 2 = walking mode
 3 = Accelerometer mode
 */
int mode = 1;

// acceleromoter
int acc_x, acc_y, acc_z;

// joystick
String data = "";  // used to parse blue tooth data
int left_ud_int = 0; // left joystick up/down value
int left_lr_int = 0; // left joystick left/right value
int right_ud_int = 0; // right joystick up/down value
int right_lr_int = 0; // right joystick left/right value
int remote_mode_int = 0; // mode from remote

void setup()
{
  Serial.begin(115200); 
  // setup ssc-32 serial connection
  Serial1.begin(115200);
  // setup bluetooth serail connection
  Serial2.begin(9600);
  // setup IK
  setupIK();
  gaitSelect(RIPPLE);
  doIK();

}

void loop()
{ 
  if (Serial2.available()) {
    char c = Serial2.read();
    data += c;
    int newline_found = data.indexOf('\n');

    if (newline_found > 0){
      parse_and_convert_data();
      mode = remote_mode_int;

      if (mode == 0){
        mode = 1; 
      }

      switch(mode){
      case 1:
        bodyPosY = -right_ud_int; 
        bodyPosX = -right_lr_int; 
        bodyRotX = left_ud_int; 
        bodyRotY = -left_lr_int; 
        data = ""; 
        doIK(); 
        break;
      case 2:
        Xspeed = left_ud_int;
        Yspeed = left_lr_int;
        doIK();
        data = ""; 
        break;
      case 3: 
        acc_x = analogRead(0);       // read analog input pin 0
        acc_y = analogRead(1);       // read analog input pin 1 
        acc_x = map(acc_x, 290, 390, -20, 20);
        acc_y = map(acc_y, 300, 400, -20, 20);
        bodyRotX = -acc_x;
        bodyRotY = -acc_y;
        doIK();    
        data = "";
        break;
      default:
        mode = 1;
        break;

      }


    }
  }
  
}
