#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>

AccelStepper stepper(1, 2, 3);
RF24 radio(49, 48); // CE, CSN

const byte addresses[6] = {"00001"};
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

struct Data_Package {
  int button1state;
  byte button2state;
  byte button3state;
  byte slider1;
  byte slider2;
  byte slider3;
  byte slider4;
  byte slider5;
  byte slider6;
  byte pot;
};
Data_Package data;

int servo1PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int servo2PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int servo3PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int servo4PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int servo5PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int servo6PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
int stepperPosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};

int button1Pressed = 0;
boolean button2Pressed = false;
boolean button3Pressed;
int val = 0;
int previous = 0;
int long newval = 0;

void setup() {
  Serial.begin(9600);
  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);
  stepper.setMaxSpeed(4800);
  stepper.setAcceleration(4800);
  radio.begin();
  radio.openReadingPipe(1, addresses);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
  }

  myservo1.write(data.slider1);\
  delay(15);
  myservo2.write(data.slider2);
  delay(15);
  myservo3.write(data.slider3);
  delay(15);
  myservo4.write(data.slider4);
  delay(15);
  myservo5.write(data.slider5);
  delay(15);
  myservo6.write(data.pot);
  delay(15);
  val = data.slider6;
  newval = map(val,0,250,0,4800);
  if ((val > previous + 50) || (val < previous - 5)) { 
    stepper.runToNewPosition(newval);  
    previous = val;  
}
 // Serial.println(character.text);
  if (data.button1state == HIGH) {
    button1Pressed += 1;
    delay(1000);
    switch (button1Pressed) {
      case 1:
        servo1PosSave[0] = data.slider1;
        servo2PosSave[0] = data.slider2;
        servo3PosSave[0] = data.slider3;
        servo4PosSave[0] = data.slider4;
        servo5PosSave[0] = data.slider5;
        servo6PosSave[0] = data.pot;
        stepperPosSave[0] = newval;       
        break;
      case 2:
        servo1PosSave[1] = data.slider1;
        servo2PosSave[1] = data.slider2;
        servo3PosSave[1] = data.slider3;
        servo4PosSave[1] = data.slider4;
        servo5PosSave[1] = data.slider5;
        servo6PosSave[1] = data.pot;
        stepperPosSave[1] = newval;
        break;
      case 3:
        servo1PosSave[2] = data.slider1;
        servo2PosSave[2] = data.slider2;
        servo3PosSave[2] = data.slider3;
        servo4PosSave[2] = data.slider4;
        servo5PosSave[2] = data.slider5;
        servo6PosSave[2] = data.pot;
        stepperPosSave[2] = newval;
        break;
      case 4:
        servo1PosSave[3] = data.slider1;
        servo2PosSave[3] = data.slider2;
        servo3PosSave[3] = data.slider3;
        servo4PosSave[3] = data.slider4;
        servo5PosSave[3] = data.slider5;
        servo6PosSave[3] = data.pot;
        stepperPosSave[3] = newval;
        break;
      case 5:
        servo1PosSave[4] = data.slider1;
        servo2PosSave[4] = data.slider2;
        servo3PosSave[4] = data.slider3;
        servo4PosSave[4] = data.slider4;
        servo5PosSave[4] = data.slider5;
        servo6PosSave[4] = data.pot;
        stepperPosSave[4] = newval;
        break;
      case 6:
        servo1PosSave[5] = data.slider1;
        servo2PosSave[5] = data.slider2;
        servo3PosSave[5] = data.slider3;
        servo4PosSave[5] = data.slider4;
        servo5PosSave[5] = data.slider5;
        servo6PosSave[5] = data.pot;
        stepperPosSave[5] = newval;
        break;
      case 7:
        servo1PosSave[6] = data.slider1;
        servo2PosSave[6] = data.slider2;
        servo3PosSave[6] = data.slider3;
        servo4PosSave[6] = data.slider4;
        servo5PosSave[6] = data.slider5;
        servo6PosSave[6] = data.pot;
        stepperPosSave[6] = newval;
        break;
      case 8:
        servo1PosSave[7] = data.slider1;
        servo2PosSave[7] = data.slider2;
        servo3PosSave[7] = data.slider3;
        servo4PosSave[7] = data.slider4;
        servo5PosSave[7] = data.slider5;
        servo6PosSave[7] = data.pot;
        stepperPosSave[7] = newval;
        break;
    }
  }
  
  if (data.button2state == HIGH) {
    button2Pressed = true;
  }

  if (button2Pressed) {
    for (int i = 0; i < 8; i++) {
      delay(1000);
      myservo1.write(servo1PosSave[i]);
      myservo2.write(servo2PosSave[i]);
      myservo3.write(servo3PosSave[i]);
      myservo4.write(servo4PosSave[i]);
      myservo5.write(servo5PosSave[i]);
      myservo6.write(servo6PosSave[i]);
      stepper.runToNewPosition(stepperPosSave[i]);
      previous = val;
      boolean button3Pressed = false;
      delay(500);
      if (data.button3state == HIGH) {
       button3Pressed = true;
}
    if (button3Pressed) {
      button2Pressed = false;
      button1Pressed = 0;
       int servo1PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int servo2PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int servo3PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int servo4PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int servo5PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int servo6PosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
       int stepperPosSave[] = {1, 1, 1, 1, 1, 1, 1, 1};
     delay(15);
      break;
    } 
    }
  }
}
