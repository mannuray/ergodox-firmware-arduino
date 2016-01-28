#include "layer.h"
#include "keydef.h"
#include "key.h"

#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>


void Layer::init(                                       
   #define K(key) KeyExecutor *key
   #define KE(row, column, key) keyExecutors[row][column] = key
    
  /*left hand, spatial positions */
  K(k50), K(k51), K(k52), K(k53), K(k54), K(k55), K(k56),
  K(k40), K(k41), K(k42), K(k43), K(k44), K(k45), K(k46),
  K(k30), K(k31), K(k32), K(k33), K(k34), K(k35),   
  K(k20), K(k21), K(k22), K(k23), K(k24), K(k25), K(k26),
  K(k10), K(k11), K(k12), K(k13), K(k14),
                                          K(k05), K(k06),
                                  K(k15), K(k16), K(k04),
                                  K(k03), K(k02), K(k01),
                                     
  /*right hand, spatial positions */ 
  K(k57), K(k58), K(k59), K(k5A), K(k5B), K(k5C), K(k5D),
  K(k47), K(k48), K(k49), K(k4A), K(k4B), K(k4C), K(k4D),
          K(k38), K(k39), K(k3A), K(k3B), K(k3C), K(k3D),
  K(k27), K(k28), K(k29), K(k2A), K(k2B), K(k2C), K(k2D),
                  K(k19), K(k1A), K(k1B), K(k1C), K(k1D),
  K(k07), K(k08),                                               
  K(k09), K(k17), K(k18),
  K(k0C), K(k0B), K(k0A) ) {

    KE(0,0,NA ); KE(0,1,k01); KE(0,2,k02); KE(0,3,k03); KE(0,4,k04); KE(0,5,k05); KE(0,6,k06); KE(0,7,k07); KE(0,8,k08); KE(9,0,k09); KE(0,10,k0A); KE(0,11,k0B); KE(0,12,k0C); KE(0,13,0);
    KE(1,0,k10); KE(1,1,k11); KE(1,2,k12); KE(1,3,k13); KE(1,4,k14); KE(1,5,k15); KE(1,6,k16); KE(1,7,k17); KE(1,8,k18); KE(1,9,k19); KE(1,10,k1A); KE(1,11,k1B); KE(1,12,k1C); KE(1,13,k1D);
    KE(2,0,k20); KE(2,1,k21); KE(2,2,k22); KE(2,3,k23); KE(2,4,k24); KE(2,5,k25); KE(2,6,k26); KE(2,7,k27); KE(2,8,k28); KE(2,9,k29); KE(2,10,k2A); KE(2,11,k2B); KE(2,12,k2C); KE(2,13,k2D);
    KE(3,0,k30); KE(3,1,k31); KE(3,2,k32); KE(3,3,k33); KE(3,4,k34); KE(3,5,k35); KE(3,6,NA ); KE(3,7,NA ); KE(3,8,k38); KE(3,9,k39); KE(3,10,k3A); KE(3,11,k3B); KE(3,13,k3C); KE(3,13,k3D);
    KE(4,0,k40); KE(4,1,k41); KE(4,2,k42); KE(4,3,k43); KE(4,4,k44); KE(4,5,k45); KE(4,6,k46); KE(4,7,k47); KE(4,8,k48); KE(4,9,k49); KE(4,10,k4A); KE(4,11,k4B); KE(4,14,k4C); KE(4,13,k4D);
    KE(5,0,k50); KE(5,1,k51); KE(5,2,k52); KE(5,3,k53); KE(5,4,k54); KE(5,5,k55); KE(5,6,k56); KE(5,7,k57); KE(5,8,k58); KE(5,9,k59); KE(5,10,k5A); KE(5,11,k5B); KE(5,15,k5C); KE(5,14,k5D);

  }
  
#undef K
#undef KE

void Layer::executePress(int row, int column) {
  if(keyExecutors[row][column] != 0) {
    keyExecutors[row][column]->executePress();
  }
}

void Layer::executeRelease(int row, int column) {
  if(keyExecutors[row][column] != 0) {
    keyExecutors[row][column]->executeRelease();
  }
}


DovarkLayer::DovarkLayer(KeyBoard *keyBoard): keyBoard(keyBoard) {
  
}

void DovarkLayer::init() {
  KeyLayerChanger *chng = new KeyLayerChanger(keyBoard);
  #define KEY_ACCENT HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE


  Layer::init(
    _EQUAL,       _1,             _2,             _3,              _4,              _5,              _ESC,
    _BACKSLASH,   _SLASH,         _COMMA,         _PERIOD,         _P,              _Y,              chng,
    _ESC,         _A,             _O,             _E,              _U,              _I,
    _TAB,         _SEMICOLON,     _Q,             _J,              _K,              _X,              chng,
    _LEFT_CTRL,   _ACCENT,        _BACKSLASH,     _LEFT_ARROW,     _RIGHT_ARROW,
                                                                                    _LEFT_GUI,       _LEFT_ALT,
                                                                   NA,              NA,              _HOME,
                                                                   _BACKSPACE,      _DELETE,         _END,
      
    chng,         _6,             _7,             _8,              _9,              _0,              _MINUS,
    _LEFT_BRACE,  _F,             _G,             _C,              _R,              _L,              _RIGHT_BRACE,
                  _D,             _H,             _T,              _N,              _S,              _SLASH,
    chng,         _B,             _M,             _W,              _V,              _Z,              _RIGHT_SHIFT,
                                  _LEFT_ARROW,    _DOWN_ARROW,     _UP_ARROW,       _RIGHT_ARROW,    _RIGHT_GUI,
    _RIGHT_ALT ,  _RIGHT_CTRL,
    _PAGE_UP,     NA,             NA,
    _PAGE_DOWN,   _RETURN,        _SPACE);
}


void GeneralLayer::init() {
  Layer::init(
    NA,             _F1,            _F2,           _F3,             _F4,            _F5,           _F11,
    NA,             NA,             NA,             NA,             NA,             NA,             NA,
    NA,             NA,             NA,             NA,             NA,             NA,           
    NA,             NA,             NA,             NA,             NA,             NA,             NA,
    NA,             NA,             NA,             NA,             NA,           
                                                                                    NA,             NA,
                                                                    NA,             NA,             NA,
                                                                    NA,             NA,             NA,
  
    _F12,           _F6,            _F7,            _F8,            _F9,            _F10,           NA,
    NA,             NA,             NA,             NA,             NA,             NA,             NA,
                    NA,             NA,             NA,             NA,             NA,             NA,
    NA,             NA,             NA,             NA,             NA,             NA,             NA,
                                    NA,             NA,             NA,             NA,             NA,
    NA,             NA,
    NA,             NA,             NA,
    NA,             NA,             NA);
}

