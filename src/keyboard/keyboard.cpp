#include <Arduino.h>

#include "keyboard.h"
#include "layer.h"
#include "scanner.h"

void KeyBoard::init(Layer **layers, KeyScanner **scanners) {
  // init all the classes here, not in constructor as it may get complicated
  // as some class will need the refrence of the class;
  
  pIsPressed = &isPressedKeys;
  pWasPressed = &wasPressedKeys;

  //this->layers = new *Layer[2]
  //layers[0] = new DovarkLayer(this); 
  /*
  layers[1] = new GeneralLayer(); //new IOExpanderKeyScanner()};

  scanners[0] = new ArduinoKeyScanner();
  scanners[1] = new ArduinoKeyScanner();
  //{new DovarkLayer(&k), new GeneralLayer()}; */

  for(int row = 0; row < ROWS; row ++) {
    for(int column = 0; column < COLUMNS; column++) {
      (*pIsPressed)[row][column] = false;
      (*pWasPressed)[row][column] = false;
    }
  }

  l1.init(this);
  l2.init();


  //this->layers = layers;
  //this->scanners = scanners;
}

void KeyBoard::rotateLayer() {
  ++currentLayer >= KEYLAYERS ? : currentLayer = 0;
}

void KeyBoard::loop() {
  bool (*temp)[ROWS][COLUMNS] = pWasPressed;
  pWasPressed = pIsPressed;
  pIsPressed = temp;

  Serial.println("\ninitial");

  /*for(int i = 0; i < 2; i++) {
  Serial.println("\nScanner running");
 //   if(scanners[i] != NULL); {
      Serial.println("\nScanner running not null ");
      scanners[i]->scanKeys(pIsPressed);
 //   }
  }*/
  s1.scanKeys(pIsPressed);
  //s2.scanKeys(pIsPressed);
   return;
  // see how the code for transpraent layer will work
  Serial.println("\nI2C starting keys scanes   ");
  for(int row = 0; row < ROWS; row++) {
    Serial.print("\nI2C row keys  "); Serial.print( row );
    for(int column = 0; column < COLUMNS; column++) {
      //Serial.print("\nI2C column keys "); Serial.print( column );
      //Serial.print(" values "); Serial.print((*pIsPressed)[row][column]); Serial.print( " "); Serial.print((*pWasPressed)[row][column]);
      if((*pWasPressed)[row][column] != (*pIsPressed)[row][column]) {
        if((*pIsPressed)[row][column]) {
          //layers[currentLayer]->executePress(row, column);
          l1.executePress(row, column);
        }
        else {
          //layers[currentLayer]->executeRelease(row, column);
          l1.executeRelease(row, column);
        }
      }
    }
  }
}
