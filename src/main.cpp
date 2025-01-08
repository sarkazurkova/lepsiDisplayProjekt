#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>
//#include <Bounce2.h>
#pragma GCC optimize ("O3")


#define COLUMS 20
#define ROWS 4
#define IRPIN 3


LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

unsigned long numbers[10][2] = {
  {0, 3977445120},
  {1, 4127850240},
  {2, 3793616640},
  {3, 3760193280},
  {4, 4061003520},
  {5, 3860463360},
  {6, 3827040000},
  {7, 3994156800},
  {8, 3927310080},
  {9, 3893886720}
};

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK); 
  Serial.begin(9600);
  lcd.clear();
}

void loop() {
  if (IrReceiver.decode()) {
    //lcd.clear();
    unsigned long receivedValue = IrReceiver.decodedIRData.decodedRawData;
    if (receivedValue>999999999){
      for(int i = 0; i < 10; i++){
        int a;
        if(receivedValue == numbers[i][1]){
          a = numbers[i][1];
          lcd.setCursor(0,1);
          lcd.print(a);
          Serial.println(numbers[i][0]);
        }
      }
      lcd.setCursor(0,0);
      lcd.print(receivedValue);
      IrReceiver.printIRResultShort(&Serial); // Vytiskne kompletní přijatá data v jedné řádce
      Serial.println(receivedValue);
    }
  
    IrReceiver.resume(); // Povolí příjem další hodnoty
    
  }
}

