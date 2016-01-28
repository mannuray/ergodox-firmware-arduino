#ifndef __KEY__
#define __KEY__

#include "keyboard.h"

class KeyExecutor {
  public:
    virtual void executePress() = 0;
    virtual void executeRelease() = 0;
};

class GeneralKey: public KeyExecutor {
  char key;

  public:
    GeneralKey(char key);
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
