#ifndef ReleInput_h
#define ReleInput_h

class Rele{
  private:
    const int pinoRele = 3; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ
    int statusSolen = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ (LIGADO / DESLIGADO) 
  public:
    void init(){
      //pino 3
      pinMode(pinoRele, OUTPUT); //DEFINE O PINO COMO SAÍDA
      digitalWrite(pinoRele, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
    }
    
    void abre(){
      digitalWrite(pinoRele, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      statusSolen = 1; //VARIÁVEL RECEBE O VALOR 1
      delay(2000); //INTERVALO DE 2000 MILISSEGUNDOS
      digitalWrite(pinoRele, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA APAGA)
      statusSolen = 0; //VARIÁVEL RECEBE O VALOR 0
      delay(2000); //INTERVALO DE 2000 MILISSEGUNDOS 
    }
 
};
#endif
