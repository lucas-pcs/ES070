#include <string.h>
#include "teclado.h"
#include "tranca.h" 
#include "lcd.h"
#include "rfid.h"

//Estados
#define ESPERA    1
#define CADASTRO  2
#define ESCOLHER  3
#define REMOVER   4
#define LECARTAO  5
#define ABRESENHA 6
#define NOVASENHA 7

Tranca *tranca1;    //Cria ponteiro para a tranca
Teclado *teclado;   //Cria ponteiro para a tranca
Lcd *lcd;           //Cria ponteiro para a tranca
RFID *rfid;         //Cria ponteiro para a tranca

// variaveis mocadas para teste 
String senha = "1234";
String senhaADM = "1235";
byte readCard[4] = {0x5A, 0xA8, 0xED, 0x80};
byte noCard[4] = {0x00, 0x00, 0x00, 0x00};
byte *readC;

class Maquina
{
  private:
    int Estado;
    int countTeclado = 0;
    String senInput = "";   
  public:
    Maquina();
    int getEstado();
    void setEstado(int estado);
    void Espera();
    void Escolher();
    void LeCartao();
    void AbreSenha();
    void NovaSenha();
};

Maquina::Maquina()
{
  Estado = ESPERA;
  //Definição de portas do sistema (definir o melhor local para essas váriavéis)
  int  portaTranca = A2; // tranca
  byte portaLinhas[4] = {A3, 8, 7, 6}; // linha do teclado
  byte portaColunas[4] = {5, 4, 3, 2}; // coluna do teclaso
  byte portaLcd = 0x27; // porta do módulo i2c

  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
  teclado = new Teclado(portaLinhas, portaColunas);   //cria o objeto teclado
  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
  rfid = new RFID();                            //cria o objeto lcd
};

void Maquina::setEstado(int estado)
{
  Estado = estado;
};

int Maquina::getEstado()
{
  return Estado;
};

void Maquina::Espera()
{
  char letra;
  letra = teclado->leTeclado();
  readC = rfid->LeTag();
  if(strncmp((char *)&readC[0],(char *)&noCard[0], 4) != 0){
    //Vai pro estado le cartão
    Estado = LECARTAO;
  }else if (letra != ' '){
    Serial.print(letra);
    senInput += letra;
    lcd->escreveSenha("senha",senInput);
    countTeclado ++;
  }
  if (countTeclado == 4){
    Estado = ESCOLHER;
  }
};


void Maquina::LeCartao()
{
    if(strncmp((char *)&readC[0],(char *)&readCard[0], 4) == 0){      
      tranca1->AbreeFecha();
      lcd->escreveSenha("Card","Correto");
    }else{     
      lcd->escreveSenha("Card","Incorreto");    
    }
    senInput = "";
    Estado = ESPERA;
};

void Maquina::Escolher()
{
  char letra;
  letra = teclado->leTeclado();
  switch(letra){
    case 'A':
      Estado = ABRESENHA;
    case 'B':
      if(strncmp(&senInput[0],&senha[0], 4)){
        Estado = NOVASENHA;
      }else{
        lcd->escreveSenha("Senha","Incorreta");
        Estado = ESPERA;
      }
      senInput = "";
    case 'C':
      Serial.print(letra);
    case 'D':
      Serial.print(letra);
  }
};

void Maquina::AbreSenha(){
  if(strncmp(&senInput[0],&senha[0], 4)){
    tranca1->AbreeFecha();
    lcd->escreveSenha("Senha","Correto");
  }else{
    lcd->escreveSenha("Senha","Incorreta");
  }
  senInput = "";
  Estado = ESPERA;
};


void Maquina::NovaSenha(){
  lcd->escreveSenha("Digite a Senha",senInput);
  char letra;
  letra = teclado->leTeclado();
  readC = rfid->LeTag();
  if(strncmp((char *)&readC[0],(char *)&noCard[0], 4) != 0){
    //Vai pro estado le cartão
    strcpy((char *)&readCard,(char *)&readC);
    Estado = ESPERA;
  }else if (letra != ' '){
    Serial.print(letra);
    senInput += letra;
    lcd->escreveSenha("senha",senInput);
    countTeclado ++;
  }
  if (countTeclado == 4){
    senha = senInput;
    Estado = ESPERA;
  }
};
