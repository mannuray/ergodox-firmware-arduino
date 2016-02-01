#include <Arduino.h>

#include "keyboard.h"
#include "layer.h"
#include "scanner.h"

void KeyBoard::init(Layer **layers, KeyScanner **scanners) {
  // init all the classes here, not in constructor as it may get complicated
  // as some class will need the refrence of the class;
  
  pIsPressed = &isPressedKeys;
  pWasPressed = &wasPressedKeys;

  for(int row = 0; row < ROWS; row ++) {
    for(int column = 0; column < COLUMNS; column++) {
      (*pIsPressed)[row][column] = false;
      (*pWasPressed)[row][column] = false;
    }
  }

  this->layers = layers;
  this->scanners = scanners;
}

void KeyBoard::rotateLayer() {
  ++currentLayer >= KEYLAYERS ? : currentLayer = 0;
}

void KeyBoard::loop() {
  bool (*temp)[ROWS][COLUMNS] = pWasPressed;
  pWasPressed = pIsPressed;
  pIsPressed = temp;


  for(int i = 0; i < 1; i++) {
    scanners[i]->scanKeys(pIsPressed);
  }
  
  //return;
  // see how the code for transpraent layer will work
  for(int row = 0; row < ROWS; row++) {
    for(int column = 0; column < COLUMNS; column++) {
      if((*pWasPressed)[row][column] != (*pIsPressed)[row][column]) {
        //BSerial.print("\nI2C keys press "); Serial.print("row "); Serial.print(row); Serial.print(" column "); Serial.print( column );
        if((*pIsPressed)[row][column]) {
          layers[currentLayer]->executePress(row, column);
        }
        else {
          layers[currentLayer]->executeRelease(row, column);
        }
      }
    }
  }
}
