
#include <Arduino.h>
#include <Wire.h>

#include "scanner.h"
#include "option.h"

void ArduinoKeyScanner::init() {

  for(int row = 0; row < ROWS; row++) {
    pinMode(rows[row], OUTPUT);
  }

  for(int column = 0; column < COLUMNS_HALF; column++) {
    pinMode(columns[column], INPUT_PULLUP);
  }
}

void ArduinoKeyScanner::scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) {
  // this is a column driven scan
  // for row driven scan, interchange row and column loop

  for(int column = 0; column < COLUMNS_HALF; column++) {
    digitalWrite(columns[column], HIGH);
  }

  for(int row = 0; row < ROWS; row++) {
    digitalWrite(rows[row], HIGH);
  }

  for(int row = 0; row < ROWS; row++) {
    digitalWrite(rows[row], LOW);
    for(int column = 0; column < COLUMNS_HALF; column++) {
      (*keyMatrix)[row][column + startColumn] = !digitalRead(columns[column]);
    }
    digitalWrite(rows[row], HIGH);
  }
}


void IOExpanderKeyScanner::init() {
  Wire.beginTransmission(IOX_BASE_ADR);  //all I2C commands begin with this statement and the address of the chip.
  Wire.write((byte)IODIRB); // select a write to the IODIRA register
  Wire.write((byte)0xff); // set all of bank B to inputs. 0 = output, 1 = input
  Wire.endTransmission();  // all I2C commands must end with this statement

  Wire.beginTransmission(IOX_BASE_ADR);  //all I2C commands begin with this statement and the address of the chip.
  Wire.write((byte)IODIRA); // select a write to the IODIRA register
  Wire.write((byte)0x00); // set all of bank A to inputs. 0 = output, 1 = input
  Wire.endTransmission();  // all I2C commands must end with this statement
    
   // This sets the pull ups on the port.  Don't do this if port is actively driven or circuit has external pull ups.
  Wire.beginTransmission(IOX_BASE_ADR);
  Wire.write((byte)GPPUB); // Select port B pull up register
  Wire.write((byte)0xff);  //turn all the pull ups on. 1=ON, 0=OFF
  Wire.endTransmission();   
}
 
void IOExpanderKeyScanner::scanKeys(bool (*keyMatrix)[ROWS][COLUMNS]) {
  uint8_t output = 128;
  uint8_t mask = 1;

  Serial.println("\n");
  
  for(int row = 0; row < ROWS; row++) {
    
    // write the output to port A
    Wire.beginTransmission(IOX_BASE_ADR);
    Wire.write(GPIOA);
    Wire.write(~output); // set one bit to low
    Wire.endTransmission();

    // read from port B
    Wire.beginTransmission(IOX_BASE_ADR);
    Wire.write(GPIOB);
    Wire.endTransmission();
    Wire.requestFrom(IOX_BASE_ADR, 1);
    byte input = Wire.read();

    mask = 1;
    for(int column = 0; column < COLUMNS_HALF; column++) {
      (*keyMatrix)[row][column] = !((~input & mask) == 0);
      mask <<= 1;
    }

    output >>= 1;
  }
}
