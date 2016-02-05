#include "layer.h"
#include "keydef.h"
#include "key.h"

#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>

#define k(key) KeyExecutor *key
#define KE(row, column, key) keyExecutors[row][column] = key


void Layer::init(                                       
    
  /*left hand, spatial positions */
  k(k00),  k(k01),  k(k02),  k(k03),  k(k04),  k(k05),  k(k06),
  k(k10),  k(k11),  k(k12),  k(k13),  k(k14),  k(k15),  k(k16),  
  k(k20),  k(k21),  k(k22),  k(k23),  k(k24),  k(k25),   
  k(k30),  k(k31),  k(k32),  k(k33),  k(k34),  k(k35),  k(k36),  
  k(k40),  k(k41),  k(k42),  k(k43),  k(k44),  
                                               k(k46),  k(k56),  
                                                        k(k55),  
                                      k(k52),  k(k53),  k(k54),
                                     
  /*right hand, spatial positions */ 
  k(k07),  k(k08),  k(k09),  k(k0A),  k(k0B),  k(k0C),  k(k0D),
  k(k17),  k(k18),  k(k19),  k(k1A),  k(k1B),  k(k1C),  k(k1D),  
           k(k28),  k(k29),  k(k2A),  k(k2B),  k(k2C),  k(k2D),  
  k(k37),  k(k38),  k(k39),  k(k3A),  k(k3B),  k(k3C),  k(k3D),  
                    k(k49),  k(k4A),  k(k4B),  k(k4C),  k(k4D),  
  k(k57),  k(k47),   
  k(k58),   
  k(k59),  k(k5A), k(k5B) ) {

    KE(0,0,k00); KE(0,1,k01); KE(0,2,k02); KE(0,3,k03); KE(0,4,k04); KE(0,5,k05); KE(0,6,k06); KE(0,7,k07); KE(0,8,k08); KE(0,9,k09); KE(0,10,k0A); KE(0,11,k0B); KE(0,12,k0C); KE(0,13,k0D);
    KE(1,0,k10); KE(1,1,k11); KE(1,2,k12); KE(1,3,k13); KE(1,4,k14); KE(1,5,k15); KE(1,6,k16); KE(1,7,k17); KE(1,8,k18); KE(1,9,k19); KE(1,10,k1A); KE(1,11,k1B); KE(1,12,k1C); KE(1,13,k1D);
    KE(2,0,k20); KE(2,1,k21); KE(2,2,k22); KE(2,3,k23); KE(2,4,k24); KE(2,5,k25); KE(2,6,NA ); KE(2,7,NA ); KE(2,8,k28); KE(2,9,k29); KE(2,10,k2A); KE(2,11,k2B); KE(2,12,k2C); KE(2,13,k2D);
    KE(3,0,k30); KE(3,1,k31); KE(3,2,k32); KE(3,3,k33); KE(3,4,k34); KE(3,5,k35); KE(3,6,k36); KE(3,7,k37); KE(3,8,k38); KE(3,9,k39); KE(3,10,k3A); KE(3,11,k3B); KE(3,12,k3C); KE(3,13,k3D);
    KE(4,0,k40); KE(4,1,k41); KE(4,2,k42); KE(4,3,k43); KE(4,4,k44); KE(4,5,NA ); KE(4,6,k46); KE(4,7,k47); KE(4,8,NA ); KE(4,9,k49); KE(4,10,k4A); KE(4,11,k4B); KE(4,12,k4C); KE(4,13,k4D);
    KE(5,0,NA ); KE(5,1,NA ); KE(5,2,k52); KE(5,3,k53); KE(5,4,k54); KE(5,5,k55); KE(5,6,k56); KE(5,7,k57); KE(5,8,k58); KE(5,9,k59); KE(5,10,k5A); KE(5,11,k5B); KE(5,12,NA ); KE(5,13,NA );
  }
  
#undef k
#undef KE

void Layer::executePress(int row, int column) {
  if(keyExecutors[row][column] != NULL) {
    keyExecutors[row][column]->executePress();
    //Serial.print("\nI2C keys press original "); Serial.print( keyExecutors[0][9]->executePress );
  }
}

void Layer::executeRelease(int row, int column) {
  if(keyExecutors[row][column] != NULL) {
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
    _BACKSLASH,   _SLASH,         _COMMA,         _PERIOD,         _P,              _Y,              _CAPS_LOCK,
    _TAB,         _A,             _O,             _E,              _U,              _I,
    _LEFT_SHIFT,  _SEMICOLON,     _Q,             _J,              _K,              _X,              chng,
    _LEFT_CTRL,   _ACCENT,        _LEFT_ALT,      _MENU,           _RIGHT_ARROW,
                                                                                    _LEFT_GUI,       _LEFT_ALT,
                                                                                                     _HOME,
                                                                   _BACKSPACE,      _DELETE,         _END,
      
    NA  ,         _6,             _7,             _8,              _9,              _0,              _MINUS,
    _LEFT_BRACE,  _F,             _G,             _C,              _R,              _L,              _RIGHT_BRACE,
                  _D,             _H,             _T,              _N,              _S,              _SLASH,
    NA,           _B,             _M,             _W,              _V,              _Z,              _RIGHT_SHIFT,
                                  _LEFT_ARROW,    _DOWN_ARROW,     _UP_ARROW,       _RIGHT_ARROW,    _RIGHT_CTRL,
    _RIGHT_GUI ,  _RIGHT_ALT,
    _PAGE_UP,     
    _PAGE_DOWN,   _RETURN,        _SPACE);
}


GeneralLayer::GeneralLayer(KeyBoard *keyBoard): keyBoard(keyBoard) {
  
}

void GeneralLayer::init() {
  KeyLayerChanger *chng = new KeyLayerChanger(keyBoard);

  Layer::init(
    _ESC,           _F1,            _F2,           _F3,             _F4,            _F5,           _F11,
    NA,             NA,             NA,             NA,             NA,             NA,             _CAPS_LOCK,
    _TAB,           NA,             NA,             NA,             NA,             NA,           
    _LEFT_SHIFT,    NA,             NA,             NA,             NA,             NA,             chng,
    _LEFT_CTRL,     NA,             _LEFT_ALT,      _MENU,          NA,           
                                                                                    _LEFT_GUI,     _LEFT_ALT,
                                                                                                   _HOME,
                                                                    _BACKSPACE,     _DELETE,       _END,
  
    _F12,           _F6,            _F7,            _F8,            _F9,            _F10,           NA,
    NA,             NA,             NA,             NA,             NA,             NA,             _NUM_LOCK,
                    NA,             NA,             NA,             NA,             NA,             _PRINTSCREEN,
    NA,             NA,             NA,             NA,             NA,             NA,             _RIGHT_SHIFT,
                                    NA,             NA,             NA,             NA,             _RIGHT_CTRL,
    _RIGHT_GUI ,   _RIGHT_ALT,
    _PAGE_UP,     
    _PAGE_DOWN,    _RETURN,         _SPACE);
}

