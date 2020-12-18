#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcd{
  private:
    byte Porta;
    LiquidCrystal_I2C *lcdInt;
  public:
    Lcd(byte porta);
    void escreveTela(String texto, int linha);
    void limpaTela();
};

Lcd::Lcd(byte porta)
{
  Porta = porta;
  lcdInt = new LiquidCrystal_I2C(Porta, 2,1,0,4,5,6,7,3, POSITIVE); 
  lcdInt->begin (16,2);
// Alterar o endereço conforme modulo I2C
};

void Lcd::escreveTela(String texto, int linha)
{
  lcdInt->setCursor(linha, 0);
  lcdInt->print(texto);
};

void Lcd::limpaTela()
{
  lcdInt->clear(); 
};
