#ifndef __KEY_BOARD__
#define __KEY_BOARD__

#include "layer.h"
#include "scanner.h"

class KeyBoard {
  bool wasPressedKeys[ROWS][COLUMNS];
  bool isPressedKeys[ROWS][COLUMNS];
  bool (*pIsPressed)[ROWS][COLUMNS];
  bool (*pWasPressed)[ROWS][COLUMNS];
 
  Layer **layers;
  //Layer *transparentLayer; //  see how we can implement it
  int currentLayer = 0;

  KeyScanner **scanners;

  bool caps = false;
  bool num = false;
  bool scroll = false;

  public:
      void init(Layer **layers, KeyScanner **scanners);
      void rotateLayer();
      void loop();
};

#endif
