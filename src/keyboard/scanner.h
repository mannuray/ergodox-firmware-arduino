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
  const int columns[COLUMNS_HALF] = {11, 10, 9, 8, 7, 6, 5};
  const int startColumn = 7;

  public:
    void init();
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

class IOExpanderKeyScanner : public KeyScanner {
  const byte  IOX_BASE_ADR =0x20;      // Base Address of MCP23017 Chip with address lines all set to zero (grounded)
                                     // Address for second MCP23017 would be 0x21, the next 0x22, etc.

  //MCP23017 internal registers - Not all registers included. See the Microchip MCP23017 datasheet for full list
  const byte  IODIRA = 0x00;           // Port A direction register. Write a 0 to make a pin an output, a 1 to make it an input
  const byte  IODIRB = 0x01;           // Port B direction register. Write a 0 to make a pin an output, a 1 to make it an input
  const byte  GPIOA = 0x12;            // Register Address of Port A - read data from or write output data to this port
  const byte  GPPUA =  0x0c;           // Register to enable the internal pull up resistors on Port A. 1 = pull up enabled
  const int   GPIOB = 0x13;            // Register Address of Port B - read data from or write output data to this port
  const byte  GPPUB =  0x0d;           // Register to enable the internal pull up resistors on Port B. 1 = pull up enabled


  public:
    void init();
    void scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]);
};

#endif
