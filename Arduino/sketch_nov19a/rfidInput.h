#ifndef rfidInput_h
#define rfidInput_h
#include <SPI.h> 
#include <MFRC522.h> 

class RFID{
  private:
    MFRC522 rfid(); 
  public:
    void inicia();
    void ler();
};

void RFID::inicia()
{
}

#endif
