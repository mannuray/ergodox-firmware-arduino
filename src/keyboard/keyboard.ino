#include <HID-Project.h>
#include <Wire.h>

#include "scanner.h"
#include "layer.h"
#include "keyboard.h"

KeyBoard k;


DovarkLayer l1(&k);
GeneralLayer l2;

ArduinoKeyScanner s1;
IOExpanderKeyScanner s2; 

KeyScanner *scanners[2];
Layer *layers[KEYLAYERS];

bool initk = false;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Keyboard.begin();
  BootKeyboard.begin();
  
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor

  // init layers
  layers[0] = &l1;
  layers[1] = &l2;
  
  for(int l = 0; l < KEYLAYERS; l++) {
    layers[l]->init();
  } 

  // init scanners
  scanners[0] = &s1;
  scanners[1] = &s2;

  for(int s = 0; s < 2; s++) {
    scanners[s]->init();
  } 
  
  //init keyboard
  k.init(layers, scanners);

  initk = true;

}

void loop() {
  // put your main code here, to run repeatedly

  if(!initk)
    return;
   
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    digitalWrite(CAP_LED_PIN, HIGH);
  else
    digitalWrite(CAP_LED_PIN, LOW);

   // update all your led's here, I am using only capslock led
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    digitalWrite(CAP_LED_PIN, HIGH);
  else
    digitalWrite(CAP_LED_PIN, LOW); 
   
  k.loop();
  delay(DEBOUNCE_TIME);

}
