#ifndef __SCANNER__
#define __SCANNER__

#include "option.h"


class KeyScanner {
  public:
    virtual void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) = 0;
};

class ArduinoKeyScanner : public KeyScanner {
  const int rows[ROWS] = {14, 15, 16, 17, 18, 19};
  const int columns[COLUMNS] = {5, 6, 7, 8, 9, 10, 11};
  const int startColumn = 7;

  public:
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

class IOExpanderKeyScanner : public KeyScanner {
  const int address = 0x20;
  const int GPIOA = 0x12;
  const int GPIOB = 0x13;

  public:
    IOExpanderKeyScanner();
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

#endif
