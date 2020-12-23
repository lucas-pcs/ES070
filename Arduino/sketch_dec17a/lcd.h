#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcd{
  private:
    byte Porta;
    LiquidCrystal_I2C *lcdInt;
  public:
    Lcd(byte porta);
    void escreveTela(String texto, int linha);
    void escreveSenha(String texto, String senha);
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
  lcdInt->setCursor(0, linha);
  lcdInt->print(texto);
};

void Lcd::limpaTela()
{
  lcdInt->clear();
  lcdInt->setCursor(0, 0); 
};

void Lcd::escreveSenha(String texto, String senha)
{
    limpaTela();
    escreveTela("senha", 0);
    escreveTela(senha, 1);
};
