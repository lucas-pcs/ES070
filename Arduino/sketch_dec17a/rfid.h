/* ************************************************************************************************ */
/* File name:          rfid.h
/* File description:   Arquivo com funções de controle do rfid
/* Author name:        Luiz Furlan
/* Author name:        Lucas Pereira
/* Author name:        Gabriel Murizine
/* Creation date:
/* Revision date:
/* ************************************************************************************************ */

#include <SPI.h>
#include <MFRC522.h>

class RFID
{
  private:
    byte readCard[4]; // Array that will hold UID of the RFID card.
    int successRead;
    MFRC522 mfrc522;
    byte noCard[4] = {0x00, 0x00, 0x00, 0x00};
  public:
    RFID();
    byte* LeTag();

};

/* ************************************************************************************************ */
/* Method name:        RFID
/* Method description: Inicializa leitor rfid
/* Input params:       n/a
/* Output params:      n/a
/* ************************************************************************************************ */
RFID::RFID() {
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia o módulo MFRC522 RFID
  Serial.println("mfrc522 INICIALIZADO");
};

/* ************************************************************************************************ */
/* Method name:        LeTag
/* Method description: Função que le tag que foi aproximada
/* Input params:       Byte* : retorna vertor com tag lida
/* Output params:      n/a
/* ************************************************************************************************ */
byte* RFID::LeTag() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if ( mfrc522.PICC_ReadCardSerial()) {
      for (int i = 0; i < mfrc522.uid.size; i++) {
        readCard[i] = mfrc522.uid.uidByte[i]; // Lê o cartão RFID
      }
      return readCard;
    }
  }
  return noCard;
};
