#include "maquina.h"

Maquina *maq;

Tranca *tranca1;    //Cria ponteiro para a tranca
Teclado *teclado;   //Cria ponteiro para a tranca
Lcd *lcd;           //Cria ponteiro para a tranca
RFID *rfid;         //Cria ponteiro para a tranca

void setup() {  
  Serial.begin(9600);
  int  portaTranca = A2; // tranca
  byte portaLinhas[4] = {A3, 8, 7, 6}; // linha do teclado
  byte portaColunas[4] = {5, 4, 3, 2}; // coluna do teclaso
  byte portaLcd = 0x27; // porta do módulo i2c

  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
  teclado = new Teclado(portaLinhas, portaColunas);   //cria o objeto teclado
  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
  rfid = new RFID();                            //cria o objeto lcd
  
  maq = new Maquina(tranca1, teclado, lcd, rfid);                  //cria o objeto maquina de estados
}

void loop() {
  int est = maq->getEstado();
  Serial.print(" estado : ");
  Serial.print(est);
  switch (est) {
    case ESPERA:
      maq->Espera();
    case ESCOLHER:
      maq->Escolher();
    case LECARTAO:
      maq->LeCartao();
    case ABRESENHA:
      maq->AbreSenha();
    case NOVASENHA:
      maq->NovaSenha();
  }
}
//
//#define ESPERA    1
//#define CADASTRO  2
//#define ESCOLHER  3
//#define REMOVER   4
//#define LECARTAO  5
//#define ABRESENHA 6
//#define NOVASENHA 7
//    void Espera();
//    void Escolher();
//    void LeCartao();
//    void AbreSenha();
//    void NovaSenha();

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
