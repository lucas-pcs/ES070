#include <Keypad.h>

byte nlinha = 4; // n de linhas
byte ncolunas = 4; //n de colunas
char dicionarioTeclado[4][4] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

class Teclado{
  private:
    byte *linhas;
    byte *colunas;
    Keypad *teclado_personalizado;
  public:
    Teclado(byte *linha, byte *coluna);
    char leTeclado();
};

Teclado::Teclado(byte *linha, byte *coluna)
{
  linhas = linha;
  colunas = coluna;
  teclado_personalizado = new Keypad(makeKeymap(dicionarioTeclado), linha, coluna, nlinha, ncolunas);
  Serial.print("Teclado INICIALIZADO"); 
};

char Teclado::leTeclado()
{
  char leitura_teclas = teclado_personalizado->getKey(); // Atribui a variavel a leitura do teclado
  if (leitura_teclas) {                                  // Se alguma tecla foi pressionada
    return leitura_teclas;                               // retorna tecla pressionada
  }
  else {
    return ' ';                                          // se nao, retorna vazio.
  }
};
