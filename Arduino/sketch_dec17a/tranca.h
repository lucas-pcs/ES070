/* ************************************************************************************************ */
/* File name:          tranca.h               
/* File description:   Arquivo com funções de controle da tranca                    
/* com senhas salvas
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */

class Tranca
{
    // variaveis
  private:
    int _Porta;
    bool _Estado;
    // metodos
  public:
    Tranca(int Porta);
    void Abre();
    void Fecha();
    void AbreeFecha();
};

/* ************************************************************************************************ */
/* Method name:        Tranca                     
/* Method description: Função para inicializar tranca
/* Input params:       int Porta: recebe pino onde esta ligado a tranca                      
/* Output params:      n/a                         
/* ************************************************************************************************ */
Tranca::Tranca(int Porta)
{
  _Porta = Porta;
  _Estado = false;
  pinMode(_Porta, OUTPUT);   //Define a porta como saída
  analogWrite(_Porta, 255);  // controla o estado inicial do relé
  Serial.print("A tranca está ligada ao pino: ");
  Serial.println(_Porta);
}

/* ************************************************************************************************ */
/* Method name:        Abre                     
/* Method description: Função para abrir a tranca
/* Input params:       n/a                    
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Tranca::Abre()
{
  analogWrite(_Porta, 0);
  Serial.println("Abril");
  _Estado = true;
}

/* ************************************************************************************************ */
/* Method name:        Fecha                     
/* Method description: Função para fechar a tranca
/* Input params:       n/a                      
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Tranca::Fecha()
{
  analogWrite(_Porta, 255);
  _Estado = false;
}

/* ************************************************************************************************ */
/* Method name:        AbreeFecha                     
/* Method description: Função para abrir e depois de um tempo fechar a tranca
/* Input params:       n/a                      
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Tranca::AbreeFecha()
{
  Abre();
  delay(3000);
  Fecha();
}
