
#include <Arduino.h>
#include <Wire.h>

#include "scanner.h"
#include "option.h"

void ArduinoKeyScanner ::scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) {
  // this is a column driven scan
  // for row driven scan, interchange row and column loop

  for(int column = 0; column <= COLUMNS; column++) {
    digitalWrite(columns[column], HIGH);
    for(int row = 0; row <= ROWS; row++) {
      (*keyMatrix)[row][column + startColumn] = digitalRead(rows[row]);
    }
    digitalWrite(columns[column], LOW);
  }
}


IOExpanderKeyScanner::IOExpanderKeyScanner() {
  Wire.beginTransmission(address);
  Wire.write(0x01); // port B will drive the columns, set to output
  Wire.write(0x00);
  Wire.endTransmission();
}
 
void IOExpanderKeyScanner::scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) {
  int output = 1;
  int mask = 1;
  for(int column = 0; column <= COLUMNS; column++) {
    // write the output to port B
    Wire.beginTransmission(address);
    Wire.write(GPIOB);
    Wire.write(output);
    Wire.endTransmission();

    // read from port A
    Wire.beginTransmission(address);
    Wire.write(GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(address, 1);
    byte input = Wire.read();

    mask = 1;
    for(int row = 0; row <= ROWS; row++) {
      (*keyMatrix)[row][column] = !((input & mask) == 0);
      mask >>= 1;
    }

    output >>= 1;
  }
}
