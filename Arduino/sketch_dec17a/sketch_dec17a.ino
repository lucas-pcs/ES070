#include "maquina.h"

Maquina *maq;

void setup() {  
  maq = new Maquina();                  //cria o objeto maquina de estados
  Serial.begin(9600);
}

void loop() {
  int est = maq->getEstado();
  switch (est) {
    case ESPERA:
      maq->Espera();
    case ESCOLHER:
      maq->Escolher();
    case LECARTAO:
      maq->LeCartao();
    case ABRESENHA:
      maq->AbreSenha();
  }
}

//void setup() {  
//  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
//  teclado = new Teclado(portaLinhas, portaColunas);   //cria o objeto teclado
//  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
//  rfid = new RFID();                            //cria o objeto lcd
//  Serial.begin(9600);
//}
//
//
//void loop() {
//  letra = teclado->leTeclado();
//  readC = rfid->LeTag();
//  if(strncmp(&readC[0],&noCard[0], 4) != 0){
//    letra = 'C';
//  }
//  int est = maq.getEstado();
//  switch (Estado) {
//    case ESPERA:
//      maq.Espera();
//    case ESCOLHER:
//      maq.Escolher();
//  }
//}
