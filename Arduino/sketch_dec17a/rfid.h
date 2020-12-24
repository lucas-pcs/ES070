#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

class RFID{
  private:
    byte readCard[4]; // Array that will hold UID of the RFID card.
    int successRead;
    MFRC522 mfrc522;
    byte noCard[4] = {0x00, 0x00, 0x00, 0x00};
  public:
    RFID();
    byte* LeTag();
    void CadastraTag();  
};

RFID::RFID(){
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia o módulo MFRC522 RFID
  Serial.print("mfrc522 INICIALIZADO");  
};

byte* RFID::LeTag(){
   if (mfrc522.PICC_IsNewCardPresent()) {
    if ( mfrc522.PICC_ReadCardSerial()) {
      for(int i = 0; i < mfrc522.uid.size; i++){
        readCard[i] = mfrc522.uid.uidByte[i]; // Lê o cartão RFID
      }
      return readCard; 
    }else{
      return noCard;
    }
  } 
};

void RFID::CadastraTag(){
  for(int i = 0; i < mfrc522.uid.size; i++){
    EEPROM.write(i, readCard[i] ); // Escreve a tag na memória eeprom
  }  
};
