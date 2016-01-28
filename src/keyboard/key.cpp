#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>

#include "key.h"
#include "keyboard.h"


GeneralKey::GeneralKey(char key): key(key) {

}

void GeneralKey::executePress() {
  Keyboard.press(key);
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
