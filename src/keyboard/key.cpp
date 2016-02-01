#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>
#include <stdint.h>

#include "key.h"
#include "keyboard.h"



GeneralKey::GeneralKey(KeyboardKeycode key): key(key) {

}

void GeneralKey::executePress() {
  Keyboard.press(key);
  Serial.print("\nI2C keys press executor  ");  Serial.print( key );
}

void GeneralKey::executeRelease(){
  Keyboard.release(key);
}


KeyLayerChanger::KeyLayerChanger(KeyBoard *keyBoard): keyBoard(keyBoard) {

}

void KeyLayerChanger::executePress() {
  keyBoard->rotateLayer();
}

void KeyLayerChanger::executeRelease() {

}
