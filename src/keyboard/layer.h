#ifndef __LAYER__
#define __LAYER__

#include "option.h"
#include "keydef.h"
#include "key.h"

class KeyExecutor;
class KeyBoard;

class Layer {
  protected:
    KeyExecutor *keyExecutors[ROWS][COLUMNS];

  public:
    virtual void init() {};
    #define k(key) KeyExecutor *key

    #define K(key) KeyExecutor *key
    #define KE(row, column, key) keyExecutors[row][column] = key
    
    void init(                                       
      
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
      k(k59),  k(k5A), k(k5B));


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

