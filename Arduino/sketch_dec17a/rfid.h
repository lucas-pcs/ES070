#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

class RFID{
  private:
    byte readCard[4]; // Array that will hold UID of the RFID card.
    int successRead;
  public:
    RFID();
    void LeTag();
    void CadastraTag();  
};

RFID::RFID(){
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia o módulo MFRC522 RFID  
};

void RFID::LeTag(){
  for(int i = 0; i < mfrc522.uid.size; i++){
    readCard[i] = mfrc522.uidByte[i]; // Lê o cartão RFID
  }
  return readCard;
};

void RFID::CadastraTag(){
  for(int i = 0; i < mfrc522.uid.size; i++){
    EEPROM.write(i, readCard[i] ); // Escreve a tag na memória eeprom
  }  
};
