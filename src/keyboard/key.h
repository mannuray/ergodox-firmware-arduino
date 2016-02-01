#ifndef __KEY__
#define __KEY__

#include <stdint.h>
#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>

class KeyBoard;

class KeyExecutor {
  public:
    virtual void executePress() = 0;
    virtual void executeRelease() = 0;
};

class GeneralKey: public KeyExecutor {
  KeyboardKeycode key;

  public:
    GeneralKey(KeyboardKeycode key);
    void executePress();
    void executeRelease();
};

class KeyLayerChanger: public KeyExecutor {
  KeyBoard *keyBoard;

  public:
    KeyLayerChanger(KeyBoard *keyBoard);
    void executePress();
    void executeRelease();
};

#endif
