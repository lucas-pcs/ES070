/* ************************************************************************************************ */
/* File name:          bluetooth.h               
/* File description:   Arquivo com funções de controle do bluetooth                     
/* com senhas salvas
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */
#include <SoftwareSerial.h>

SoftwareSerial bt_serial(0, 1) //pinos RX e TX do arduino

void setup(){
  bt_serial.begin(9600);
}

void loop(){
  char c = bt_serial.read();
  if( c == 'A'){
    Serial.println("deu certo");
  }
}
