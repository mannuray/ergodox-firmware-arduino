#ifndef __LAYER__
#define __LAYER__

#include "option.h"

class KeyExecutor;
class KeyBoard;

class Layer {
  protected:
    KeyExecutor *keyExecutors[ROWS][COLUMNS];

  public:
    virtual void init() = 0;
    #define K(key) KeyExecutor *key

     virtual void init(                                       
      
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
      K(k0C), K(k0B), K(k0A) );

    #undef k
    
    void executePress(int row, int column);
    void executeRelease(int row, int column);
};


class DovarkLayer : public Layer {
  KeyBoard *keyBoard;
  public:
    DovarkLayer(KeyBoard *keyBoard);
    void init();
};


class GeneralLayer : public Layer {
  public:
    void init();
};
    
#endif

