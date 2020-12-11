#ifndef LCDInput_h
#define LCDInput_h
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

    const byte endereco = 0x27;
    const byte carcter = 4; 
    const byte linhas = 2; 
    LiquidCrystal_I2C lcd(endereco,carcter,linhas);
    
class LCD{
  private:
   
  public:
    void init(){
      lcd.begin(16, 2);
    };

    void escreveTela(String texto, int linha){
      lcd.setCursor(linha, 0);
      lcd.print(texto);
    };
    
    void limpaTela(){
      lcd.clear(); 
    };
 
};
#endif
