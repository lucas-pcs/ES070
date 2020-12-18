#include "teclado.h"
#include "tranca.h" 


Tranca *tranca1;  //Cria ponteiro para a tranca
Teclado *teclado;  //Cria ponteiro para a tranca

long comeco = 0;
long intervalo = 500;

void setup() {
  // put your setup code here, to run once:
  tranca1 = new Tranca(10);       //cria o objeto led1
  teclado = new Teclado();       //cria o objeto led1
  pinMode(tranca1->Porta(), OUTPUT);   //Define a porta como saída
  Serial.begin(38400);              //Configura o Monitor Serial
  Serial.print("O tranca1 esta: ");
  Serial.println(tranca1->Porta());
}

void loop() {
  
  unsigned long agora = millis();
  teclado->leTeclado();

  if((agora - comeco) > intervalo) {
    comeco = agora;
    if(tranca1->Estado()) {
      tranca1->Fecha();
    } else {
      tranca1->Abre();
    }
  }
}
