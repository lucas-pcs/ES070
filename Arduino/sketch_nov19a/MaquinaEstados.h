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
    RFID rfid;
    
  public:

    void init(){
      teclado.init();
      lcd.init();
      rfid.init();
    }

    void maquina(){
    }

};
#endif
