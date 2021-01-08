/* ***************************************************** */
/* File name:          sketch_dec17a               
/* File description:   Main do projeto                        
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                              
/* ***************************************************** */
#include "maquina.h"
#include <avr/sleep.h>

// Criação dos ponteiros.
Maquina *maq;           //Cria ponteiro para a máquina de estados
Tranca *tranca1;        //Cria ponteiro para a tranca
Teclado *teclado;       //Cria ponteiro para o teclado
Lcd *lcd;               //Cria ponteiro para o lcd
RFID *rfid;             //Cria ponteiro para o RFID
SensorPIR *sensorpir;   //Cria ponteiro para o sensor de presença

// Declaracao das variáveis globais.
int  portaTranca = A3;                // Pino ligado ao relé responsável por abrir a tranca.
byte portaLinhas[4] = {A1, 3, 4, 5};  // Linhas do teclado.
byte portaColunas[4] = {6, 7, 8, A2}; // Colunas do teclado.
byte portaLcd = 0x27;                 // Endereço do módulo I2C
int portaSensorPIR = 2;               // Pino em que quando o sensor de presença detecta alguém envia sinal HIGH
int tx = 1;                           // Porta TX
int rx = 0;                           // Porta RX

/* ************************************************ */
/* Method name:        setup                     
/* Method description: Inicialização de todos os hardware 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void setup() {
  Serial.begin(9600);                                         // Inicializa a saída serial, utilizada no processo de desenvolvimento
  tranca1 = new Tranca(portaTranca);                          // Cria o objeto tranca
  teclado = new Teclado(portaLinhas, portaColunas, tx, rx);   // Cria o objeto teclado
  lcd = new Lcd(portaLcd);                                    // Cria o objeto lcd
  rfid = new RFID();                                          // Cria o objeto RFID
  sensorpir = new SensorPIR(portaSensorPIR);                  // Cria o objeto do sensor de presença
  maq = new Maquina(tranca1, teclado, lcd, rfid, sensorpir);  // Cria o objeto máquina de estados
}

/* ************************************************ */
/* Method name:        loop                     
/* Method description: Função de loop que chama as funções de acordo com estado 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void loop() {
  int iSensorPIR;                           // Variavél que indica a presença de alguém
  iSensorPIR = sensorpir->leSensorPIR();    // Leitura do sensor
  if(iSensorPIR == HIGH){
    modoOcioso();
  }
 int est = maq->getEstado();
  switch (est) {
    case ESPERA:
      maq->Espera();
      break;
    case ESCOLHER:
      maq->Escolher();
      break;
    case LECARTAO:
      maq->LeCartao();
      break;
    case ABRESENHA:
      maq->AbreSenha();
      break;
    case NOVASENHA:
      maq->NovaSenha();
      break;
    case TROCASENHA:
      maq->TrocaSenha();
      break;
    case MENUMESTRE:
      maq->MenuMestre();
      break;
    case EDITASENHA:
      maq->EditaSenha();
      break;
    case REMOVER:
      maq->Remove();
      break;
    case CADASTRACARD:
      maq->CadastraCard();
      break;
    default:
      break;
  }
}

/* ************************************************ */
/* Method name:        modoOcioso                     
/* Method description: Função que produz o modo ocioso 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void modoOcioso(){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    int interrupcao = sensorpir->returnPorta();
    attachInterrupt(digitalPinToInterrupt(interrupcao), acordar, CHANGE);
    sleep_cpu();
}

/* ************************************************ */
/* Method name:        acordar                     
/* Method description: Função que sai do modo ocioso 
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************ */
void acordar(){
    sleep_disable();   // Desabilita o sleep
    detachInterrupt(0);// Desabilita a interrupção
}
