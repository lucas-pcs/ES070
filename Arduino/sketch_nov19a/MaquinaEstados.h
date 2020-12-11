#ifndef maquinaInput_h
#define maquinaInput_h

#include "TecladoInput.h"
#include "LCDInput.h"
#include "rfidInput.h"



class MaquinaEstados{
  private:
    char estado;
    char senhaAtual[4];
    Teclado  teclado;
    LCD lcd;
    
  public:

    void init(){
      teclado.init();
      lcd.init();
    }

    void maquina(){
    }

};
#endif
