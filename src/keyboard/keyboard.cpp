#include "keyboard.h"
#include "layer.h"
#include "scanner.h"

void KeyBoard::init(Layer **layers, KeyScanner **scanners) {
  // init all the classes here, not in constructor as it may get complicated
  // as some class will need the refrence of the class;
  
  pIsPressed = &isPressedKeys;
  pWasPressed = &wasPressedKeys;

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

  for(int i = 0; i < 2; i++) {
    scanners[i]->scanKeys(pIsPressed);
  }

  // see how the code for transpraent layer will work
  for(int row = 0; row < ROWS; row++) {
    for(int column = 0; column < COLUMNS; column++) {
      if((*pWasPressed)[ROWS][COLUMNS] != (*pIsPressed)[ROWS][COLUMNS]) {
        if((*pIsPressed)[ROWS][COLUMNS]) {
          layers[currentLayer]->executePress(row, column);
        }
        else {
          layers[currentLayer]->executeRelease(row, column);
        }
      }
    }
  }
}
