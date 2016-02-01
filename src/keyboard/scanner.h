#ifndef __SCANNER__
#define __SCANNER__

#include <Arduino.h>

#include "option.h"


class KeyScanner {
  public:
    virtual void init() {};
    virtual void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) {};
};

class ArduinoKeyScanner : public KeyScanner {
  const int rows[ROWS] = {A0, A1, A2, A3, A4, A5 };
  const int columns[COLUMNS_HALF] = {5, 6, 7, 8, 9, 10, 11};
  const int startColumn = 7;

  public:
    void init();
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

class IOExpanderKeyScanner : public KeyScanner {
  const int address = 0x20;
  const int GPIOA = 0x12;
  const int GPIOB = 0x13;

  public:
    void init();
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

#endif
