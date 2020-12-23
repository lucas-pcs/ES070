#include <string.h>
#include "teclado.h"
#include "tranca.h" 
#include "lcd.h"
#include "rfid.h"

Tranca *tranca1;    //Cria ponteiro para a tranca
Teclado *teclado;   //Cria ponteiro para a tranca
Lcd *lcd;           //Cria ponteiro para a tranca
RFID *rfid;         //Cria ponteiro para a tranca

#define ESPERA   1
#define CADASTRO 2
#define ESCOLHER 3
#define REMOVER  4
#define LECARTAO 5
#define ABRESENHA 6

//
String senInput = "";
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
  public:
    Maquina();
    int getEstado();
    void setEstado(int estado);
    void Espera();
    void Escolher();
    void LeCartao();
    void AbreSenha();
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
  if(strncmp(&readC[0],&noCard[0], 4) != 0){
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
    Serial.print(letra);
    //Serial.print(strncmp(&readC[0],&readCard[0], 4));
    if(strncmp(&readC[0],&readCard[0], 4) == 0){      
      tranca1->AbreeFecha();
      lcd->escreveSenha("Card","Correto");
    }else{     
      lcd->escreveSenha("Card","Incorreto");    
      delay(3000);
      lcd->limpaTela();
    }
    senInput = "";
    Estado = ESPERA;
};

void Maquina::Escolher()
{
  i = 0;
  switch(letra){
    case 'A':
      Estado = ABRESENHA;
    case 'B':
      Serial.print(letra);
    case 'C':
      Estado = ESPERA;
    case 'D':
      Serial.print(letra);
  }
};

void Maquina::Escolher()
{
  i = 0;
  switch(letra){
    case 'A':
      Serial.print(strncmp(&senInput[0],&senha[0], 4));
      if(strncmp(&senInput[0],&senha[0], 4)){
        tranca1->Abre();
        
        lcd->limpaTela();
        lcd->escreveTela("ABRIU", 0);
        lcd->escreveTela(senInput, 1);
        
        delay(3000);
        tranca1->Fecha();
        lcd->limpaTela();
      }else{
        
        lcd->limpaTela();
        lcd->escreveTela("Senha", 0);
        lcd->escreveTela("Incorreta", 1);
        
        delay(3000);
        lcd->limpaTela();
      }
      senInput = "";
      Estado = ESPERA;
    case 'B':
      Serial.print(letra);
    case 'C':
      Serial.print(letra);
      //Serial.print(strncmp(&readC[0],&readCard[0], 4));
      if(strncmp(&readC[0],&readCard[0], 4) == 0){
        tranca1->Abre();
        
        lcd->limpaTela();
        lcd->escreveTela("ABRIU", 0);
        
        delay(3000);
        tranca1->Fecha();
        lcd->limpaTela();
      }else{
        
        lcd->limpaTela();
        lcd->escreveTela("Card", 0);
        lcd->escreveTela("Incorreto", 1);
        delay(3000);
        lcd->limpaTela();
      }
      senInput = "";
      Estado = ESPERA;
    case 'D':
      Serial.print(letra);
  }
};
