#include <HID-Project.h>
#include <Wire.h>

#include "scanner.h"
#include "layer.h"
#include "keyboard.h"

KeyBoard k;
bool initk = false;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Keyboard.begin();
  BootKeyboard.begin();


  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT); 

/*
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT); */

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");

  // init layers
  Layer *layers[KEYLAYERS] = {new DovarkLayer(), new GeneralLayer()};
  /*for(int l = 0; l < KEYLAYERS; l++) {
    Serial.println("\nI2C init layers");
    layers[l]->init();
    Serial.println("\nI2C init layers Ffinish");
  }*/

  Serial.println("\nI2C layers");

  // init scanners
  KeyScanner *scanners[2] = {new ArduinoKeyScanner(), new ArduinoKeyScanner()}; //new IOExpanderKeyScanner()};

  Serial.println("\nI2C keybeard");
  
  //init keyboard
  k.init(layers, scanners);

  Serial.println("\nI2C running");
  initk = true;

}

void loop() {
  // put your main code here, to run repeatedly

  if(!initk)
    return;
  
  Serial.println("\nKeyboard");
  /*
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    digitalWrite(CAP_LED_PIN, HIGH);
  else
    digitalWrite(CAP_LED_PIN, LOW);

   // update all your led's here, I am using only capslock led
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    digitalWrite(CAP_LED_PIN, HIGH);
  else
    digitalWrite(CAP_LED_PIN, LOW); */
   
  k.loop();
  delay(DEBOUNCE_TIME);

}
