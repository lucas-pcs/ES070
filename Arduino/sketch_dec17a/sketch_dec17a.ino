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
#define DENOVO   5


char letra;
int Estado = 1;
int i=0;
String senInput = "";
String senha = "1234";
String senhaADM = "1235";

//Definição de portas do sistema
int  portaTranca = A2; // tranca
byte portaLinhas[4] = {A3, 8, 7, 6}; // linha do teclado
byte portaColunas[4] = {5, 4, 3, 2}; // coluna do teclaso
byte portaLcd = 0x27; // porta do módulo i2c

void setup() {  
  tranca1 = new Tranca(portaTranca);                  //cria o objeto traca
  teclado = new Teclado(portaLinhas, portaColunas);   //cria o objeto teclado
  lcd = new Lcd(portaLcd);                            //cria o objeto lcd
  rfid = new RFID();                            //cria o objeto lcd
  Serial.begin(9600);
}


class Maquina
{
  private:
    int Estado;   
  public:
    Maquina();
    int getEstado();
    void setEstado(int estado);
    void Espera();
    void Escolher();
};

Maquina::Maquina()
{
  Estado = ESPERA;
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
  if (letra != ' '){
    Serial.print(letra);
    senInput += letra;
    lcd->limpaTela();
    lcd->escreveTela("senha", 0);
    lcd->escreveTela(senInput, 1);
    i ++;
  }
  if (i == 4){
    Estado = ESCOLHER;
  }
};
void Maquina::Escolher()
{
  i = 0;
  switch(letra){
    case 'A':
      if(strncmp(&senInput[0],&senha[0], 4)){
        tranca1->Abre();
        
        lcd->limpaTela();
        lcd->escreveTela("ABRIU", 0);
        lcd->escreveTela(senInput, 1);
        
        delay(300);
        tranca1->Fecha();
        lcd->limpaTela();
      }else{
        
        lcd->limpaTela();
        lcd->escreveTela("Senha", 0);
        lcd->escreveTela("Incorreta", 1);
        
        delay(300);
        lcd->limpaTela();
      }
      senInput = "";
      Estado = ESPERA;
    case 'B':
      Serial.print(letra);
    case 'C':
      Serial.print(letra);
    case 'D':
      Serial.print(letra);
  }
};

Maquina maq;

void loop() {
  letra = teclado->leTeclado();
  int est = maq.getEstado();
  switch (Estado) {
    case ESPERA:
      maq.Espera();
    case ESCOLHER:
      maq.Escolher();
  }
}
