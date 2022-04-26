#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3f
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

RF24 radio(9,10); // CE, CSN
const byte addresses[6] = {"00001"};
struct Data_Package{
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
  float l1 = 14;
  float l2 = 18.5;
  float l3 = 11.5;
  float l4 = 23;
  float pi = 3.14;
int button1Pressed =0;
void setup() {
  radio.begin();
  radio.openWritingPipe(addresses); 
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
 lcd.begin (20,4);
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(HIGH);
}

void loop() {
   delay(5);
   radio.stopListening();
   data.button1state = digitalRead(2);
   data.button2state = digitalRead(3);
   data.button3state = digitalRead(4);
   int aa = analogRead(A0);  
   data.slider1 = map(aa,0,1023,0,179);
   data.slider2 = map(aa,0,1023,179,0);
   int bb = analogRead(A1);  
   data.slider3 = map(bb,0,1023,30,180);
   int cc = analogRead(A2);  
   data.slider4 = map(cc,0,1023,0,130);
   int dd = analogRead(A3);  
   data.slider5 = map(dd,0,1023,0,180);
   int ee = analogRead(A7);  
   data.pot = map(ee,0,1023,0,180);
   int ff = analogRead(A6);
   data.slider6 = map(ff,0,1023,0,250);
   int gg = map(ff,0,1023,0,270);
   
   radio.write(&data,sizeof(Data_Package));
   
    if (data.button1state == HIGH) {
    button1Pressed += 1;
    delay(1000);
    switch (button1Pressed) {
      case 1:
        lcd.setCursor (0,3);
        lcd.print("Position 1 Saved"); 
        delay(1000);   
        break;
        case 2:
        lcd.setCursor (0,3);
        lcd.print("Position 2 Saved"); 
        delay(1000);   
        break;
        case 3:
        lcd.setCursor (0,3);
        lcd.print("Position 3 Saved");  
        delay(1000);  
        break;
        case 4:
        lcd.setCursor (0,3);
        lcd.print("Position 4 Saved"); 
        delay(1000);   
        break;
        case 5:
        lcd.setCursor (0,3);
        lcd.print("Position 5 Saved");  
        delay(1000);  
        break;
        case 6:
        lcd.setCursor (0,3);
        lcd.print("Position 6 Saved");
        delay(1000);    
        break;
        case 7:
        lcd.setCursor (0,3);
        lcd.print("Position 7 Saved");    
        break;
        case 8:
        lcd.setCursor (0,3);
        lcd.print("Position 8 Saved");
        delay(1000);    
        break;
    }
}
  if (data.button3state == HIGH) {
    button1Pressed = 0;
  }
     lcd.setCursor (0,0);
     lcd.print("B=");
     lcd.print(gg);
     lcd.setCursor (10,0);
     lcd.print("J1=");
     lcd.print(data.slider5);
     lcd.setCursor (0,1);
     lcd.print("J2=");
     lcd.print(data.slider4);
     lcd.setCursor (10,1);
     lcd.print("J3=");
     lcd.print(data.slider3);
     lcd.setCursor (0,2);
     lcd.print("W=");
     lcd.print(data.slider1);
     lcd.setCursor (10,2);
     lcd.print("G=");
     lcd.print(data.pot);
     delay(100);
     lcd.clear();
}
