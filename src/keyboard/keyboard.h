#ifndef __KEY_BOARD__
#define __KEY_BOARD__

#include "layer.h"
#include "scanner.h"

class KeyBoard {
  bool wasPressedKeys[ROWS][COLUMNS];
  bool isPressedKeys[ROWS][COLUMNS];
  bool (*pIsPressed)[ROWS][COLUMNS];
  bool (*pWasPressed)[ROWS][COLUMNS];
 
  Layer *layers[2];
  //Layer *transparentLayer; //  see how we can implement it
  int currentLayer = 0;
  DovarkLayer l1;
  GeneralLayer l2;

  KeyScanner *scanners[2];

  ArduinoKeyScanner s1;
  //IOExpanderKeyScanner s2;

  

  bool caps = false;
  bool num = false;
  bool scroll = false;

  public:
      void init(Layer **layers, KeyScanner **scanners);
      void rotateLayer();
      void loop();
};

#endif
