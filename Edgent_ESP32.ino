/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

#define BLYNK_TEMPLATE_ID "TMPL6t4diTIq0"
#define BLYNK_TEMPLATE_NAME "Monitoring MQ2"

#include <WiFi.h>


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

BlynkTimer timer;
bool isconnected = false;

/*
   Exponential regression:
  a = [log(y2)-log(y1)]/[log(x2)-log(x1)]


  a =  -0.44721 //LPG
  a =  -0.29405 //CO
  a =  -0.34103 //CH4

  b = log(y)-a*log(x)


  b =  1.23798 //LPG
  b =  1.40088 //CO
  a =  1.28644 //CH4
*/

#define RL 10
#define alpg  -0.44721
#define blpg 1.23798
#define aco  -0.29405
#define bco 1.40088
#define ach4  -0.34103
#define bch4 1.28644
#define Ro 2.7

float VRL;
float Rs;
float ratio;
float lpg;
float co;
float ch4;

int i;
int value;
int numReadings = 10;


#define MQ_sensor 36
void setup() {


  Serial.begin(115200);
  delay(500);

  BlynkEdgent.begin();

  pinMode(MQ_sensor, INPUT);
  timer.setInterval(5000L, checkBlynkStatus);
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}

void checkBlynkStatus() {
  isconnected = Blynk.connected();
  if (isconnected == true) {
    //Serial.println("Blynk Connected");
  }
  else {
    Serial.println("Blynk Not Connected");
  }
  delay(100);
}

void sendSensor() {

  for (i = 0; i < numReadings; i++) {
    value = value + analogRead(MQ_sensor);
    delay(10);
  }
  value = value / numReadings;
  Serial.print("Value : ");
  Serial.println(value);

  //LPG
  VRL = value * (3.3 / 4095.0);
  Rs = ((3.3 * RL) / VRL) - RL;
  ratio = Rs / Ro;
  lpg = pow(10, (log10(ratio) - blpg) / alpg);
  Serial.print("Ratio : ");
  Serial.println(ratio);

  Serial.print("LPG   : ");
  Serial.print(lpg);
  Serial.println(" ppm");
  delay(200);
  //CO
  co = pow(10, (log10(ratio) - bco) / aco);

  Serial.print("CO    : ");
  Serial.print(co);
  Serial.println(" ppm");
  delay(200);
  //CH4
  ch4 = pow(10, (log10(ratio) - bch4) / ach4);

  Serial.print("CH4   : ");
  Serial.print(ch4);
  Serial.println(" ppm");
  delay(1000);
  Serial.println(" ");


  Blynk.virtualWrite(V0, lpg);
  Blynk.virtualWrite(V1, co);
  Blynk.virtualWrite(V2, ch4);
}
