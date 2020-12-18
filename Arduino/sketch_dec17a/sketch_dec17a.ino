#include "teclado.h"
#include "tranca.h" 
#include "lcd.h"

Tranca *tranca1;  //Cria ponteiro para a tranca
Teclado *teclado;  //Cria ponteiro para a tranca
Lcd *lcd;  //Cria ponteiro para a tranca

long comeco = 0;
long intervalo = 500;

//void setup() {
//  // put your setup code here, to run once:
//  tranca1 = new Tranca(10);       //cria o objeto led1
//    pinMode(_Porta, OUTPUT);   //Define a porta como saída
//  Serial.print("O tranca1 esta: ");
//  Serial.println(_Porta);
//  
//  teclado = new Teclado();       //cria o objeto led1
//  lcd = new Lcd();       //cria o objeto led1
//  Serial.begin(9600);
//}

void setup() {
  // put your setup code here, to run once:
  tranca1 = new Tranca(10);       //cria o objeto led1
  teclado = new Teclado();       //cria o objeto led1
  lcd = new Lcd();       //cria o objeto led1
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();
  teclado->leTeclado();
  lcd->escreveTela("texto", 0);
  if((agora - comeco) > intervalo) {
    comeco = agora;
    if(tranca1->Estado()) {
      tranca1->Fecha();
    } else {
      tranca1->Abre();
    }
  }
}
