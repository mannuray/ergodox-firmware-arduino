#include <HID-Project.h>

#include "scanner.h"
#include "layer.h"
#include "keyboard.h"

KeyBoard k;

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
  BootKeyboard.begin();

  // init layers
  Layer *layers[KEYLAYERS] = {new DovarkLayer(&k), new GeneralLayer()};
  for(int l = 0; l < KEYLAYERS; l++)
    layers[l]->init();

  // init scanners
  KeyScanner *scanners[2] = {new ArduinoKeyScanner(), new IOExpanderKeyScanner()};

  //init keyboard
  k.init(layers, scanners);

}

void loop() {
  // put your main code here, to run repeatedly:

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
