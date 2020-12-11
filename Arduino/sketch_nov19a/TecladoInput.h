#include <Keypad.h>
#ifndef TecladoInput_h
#define TecladoInput_h

  const byte nlinha = 4; // n de linhas
  const byte ncolunas = 4; //n de colunas

class Teclado{
  
  private:
    const char dicionarioTeclado[nlinha][ncolunas] = { // Matriz de caracteres (mapeamento do teclado)
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}
    };
    const byte linhas[nlinha] = {9, 8, 7, 6};
    const byte colunas[ncolunas] = {5, 4, 3, 2}; 
    Keypad teclado_personalizado;
  
  public:

    void init(){
      teclado_personalizado = Keypad(makeKeymap(dicionarioTeclado), linhas, colunas, nlinha, ncolunas);
      Serial.begin(9600); // Inicia porta serial
    }

    char leTeclado(){
      char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
      if (leitura_teclas) {                 // Se alguma tecla foi pressionada
        return leitura_teclas;
      }
      else {
        return ' ';
      }
    }
 
};
#endif
