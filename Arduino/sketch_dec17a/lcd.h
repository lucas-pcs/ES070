/* ************************************************************************************************ */
/* File name:          lcd.h               
/* File description:   arquivo de controle do LCD                       
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcd {
  private:
    byte Porta;
    LiquidCrystal_I2C *lcdInt;
  public:
    Lcd(byte porta);
    void escreveTela(String texto, int linha);
    void escreveSenha(String texto, String senha);
    void limpaTela();
};

/* ************************************************************************************************ */
/* Method name:        Lcd                     
/* Method description: Construtor do objeto
/* Input params:       byte porta: porta que está ligado o hardware                          
/* Output params:      n/a                         
/* ************************************************************************************************ */
Lcd::Lcd(byte porta)
{
  Porta = porta;
  lcdInt = new LiquidCrystal_I2C(Porta, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
  lcdInt->begin (16, 2);
  // Alterar o endereço conforme modulo I2C
};

/* ************************************************************************************************ */
/* Method name:        escreveTela                     
/* Method description: Exibe o texto no LCD
/* Input params:       String texto: texto a ser escrito, int linha: linha em que será escrito texto                          
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Lcd::escreveTela(String texto, int linha)
{
  lcdInt->setCursor(0, linha);
  lcdInt->print(texto);
};

/* ************************************************************************************************ */
/* Method name:        limpaTela                     
/* Method description: apaga toda informação do LCD
/* Input params:       n/a                          
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Lcd::limpaTela()
{
  lcdInt->clear();
  lcdInt->setCursor(0, 0);
};

/* ************************************************************************************************ */
/* Method name:        escreveSenha                     
/* Method description: Função para escrever senha que está sendo digitada
/* Input params:       String texto: texto a ser escrito na linha 1, String senha: senha que esta 
/* sendo digitada                          
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Lcd::escreveSenha(String texto, String senha)
{
  limpaTela();
  escreveTela(texto, 0);
  Serial.print("DEBUG: ");
  Serial.println(texto);
  escreveTela(senha, 1);
  Serial.print("DEBUG: ");
  Serial.println(senha);
};
