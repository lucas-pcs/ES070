#include <Keypad.h>
//#include <SoftwareSerial.h>

byte nlinhas = 4; // n de linhas
byte ncolunas = 4; //n de colunas
char dicionarioTeclado[4][4] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

class Teclado {
  private:
    byte *linhas;
    byte *colunas;
    Keypad *teclado_personalizado;
    //SoftwareSerial *serial;
  public:
    //SoftwareSerial *serial;
    Teclado(byte *linha, byte *coluna, int tx, int rx);
    char leTeclado();
};

Teclado::Teclado(byte *linha, byte *coluna, int tx, int rx)
{
  linhas = linha;
  colunas = coluna;
  teclado_personalizado = new Keypad(makeKeymap(dicionarioTeclado), linha, coluna, nlinhas, ncolunas);
  //serial = new SoftwareSerial(tx, rx);
  //serial-> begin(9600);
  Serial.println("Teclado INICIALIZADO");
};

char Teclado::leTeclado()
{
  char leitura_teclas = teclado_personalizado->getKey(); // Atribui a variavel a leitura do teclado
  if (leitura_teclas) {                                  // Se alguma tecla foi pressionada
    Serial.println(leitura_teclas);
    return leitura_teclas;                               // retorna tecla pressionada
  }
// código usado para simular teclado via serial
  leitura_teclas = Serial.read();
  if (((leitura_teclas >= '0') && (leitura_teclas <= '9')  ) || ((leitura_teclas == 'A') || (leitura_teclas == 'B') || (leitura_teclas == 'C') || (leitura_teclas == 'D') || (leitura_teclas == '#'))) {
    Serial.println(leitura_teclas);
    return leitura_teclas;
  }
  return ' ';                                          // se nao, retorna vazio.
};
