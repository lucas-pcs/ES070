/* ************************************************************************************************ */
/* File name:          maquina.h               
/* File description:   Arquivo com funções da máquina de estado                       
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */
#include "teclado.h"
#include "tranca.h"
#include "lcd.h"
#include "rfid.h"
#include "senha.h"
#include "sensor_pir.h"

//Estados
#define ESPERA         1
#define CADASTRO       2
#define ESCOLHER       3
#define REMOVER        4
#define LECARTAO       5
#define ABRESENHA      6
#define NOVASENHA      7
#define TROCASENHA     8
#define MENUMESTRE     9
#define EDITASENHA    10
#define CADASTRACARD  11

byte *readC;  //tag lida

class Maquina
{
  private:
    int Estado;
    int countTeclado;   // conta quantas vezes o teclado foi apertado
    String senInput;    // senha que o usuario colocou
    int indexSenha;
    Tranca *tranca1;    //Cria ponteiro para objeto do tipo tranca
    Teclado *teclado;   //Cria ponteiro para objeto do tipo teclado
    Lcd *lcd;           //Cria ponteiro para objeto do tipo lcd
    RFID *rfid;         //Cria ponteiro para objeto do tipo rfid
    Senha bancoSenha;
    SensorPIR *sensorpir; ////Cria ponteiro para objeto do tipo sensorPIR
  public:  // metodos
    Maquina();        // metodo que coloca a maquina de estados no estado ESPERA
    Maquina(Tranca *tranca2, Teclado *teclado2, Lcd *lcd2, RFID *rfid2, SensorPIR *sensorpir1);
    int getEstado();
    void setEstado(int estado);
    void Espera();
    void Escolher();
    void LeCartao();
    void AbreSenha();
    void NovaSenha();
    void TrocaSenha();
    void MenuMestre();
    void EditaSenha();
    void Remove();
    void goToEspera();
    void CadastraCard();
};

/* ************************************************************************************************ */
/* Method name:        Maquina                     
/* Method description: Construtor do objeto máquina de estados
/* Input params:       Tranca *tranca2: recebe ponteiro que aponta para objeto que controla Tranca, 
/* Teclado *teclado2: recebe ponteiro que aponta para objeto que controla o teclado, Lcd *lcd2: recebe 
/* ponteiro que aponta para objeto que controla LCD, RFID *rfid2: recebe ponteiro que aponta para objeto 
/* que controla RFID                      
/* Output params:      n/a                         
/* ************************************************************************************************ */
Maquina::Maquina(Tranca *tranca2, Teclado *teclado2, Lcd *lcd2, RFID *rfid2, SensorPIR *sensorpir1)
{
  senInput = "";
  Estado = ESPERA;
  countTeclado = 0;
  tranca1 = tranca2;                  //cria o objeto traca
  teclado = teclado2;                 //cria o objeto teclado
  lcd = lcd2;                         //cria o objeto lcd
  rfid = rfid2;                       //cria o objeto lcd
  Serial.println("MAQUINA metodo 2");
  sensorpir = sensorpir1;
};

/* ************************************************************************************************ */
/* Method name:        setEstado                     
/* Method description: Função para setar variavel Estado
/* Input params:       int estado: Estado que sera definido                         
/* Output params:      n/a                         
/* ************************************************************************************************ */
void Maquina::setEstado(int estado)
{
  Estado = estado;
};

/* ************************************************************************************************ */
/* Method name:        getEstado                     
/* Method description: Função que retorna valor do estado atual da máquina
/* Input params:       n/a                          
/* Output params:      Int Estado: retorna valor do estado atual                        
/* ************************************************************************************************ */
int Maquina::getEstado()
{
  return Estado;
};

/* ************************************************************************************************ */
/* Method name:        Espera                     
/* Method description: Função do estado que aguarda usuário digitar a senha
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::Espera()
{
  char letra;
  int sensorPIRteste;

  sensorPIRteste = sensorpir->leSensorPIR();
  if(sensorPIRteste == HIGH){
    Serial.println("sensor de movimento ativado");
  }
  letra = teclado->leTeclado();
   readC = rfid->LeTag();
  
  if (bancoSenha.ComparanoRfid(readC)) {
    Estado = LECARTAO;
  }
  //retorna diferente de  null se uma tecla foi pressionada
  if (letra != ' ') {
    senInput += letra;
    lcd->escreveSenha("senha", senInput);
    countTeclado ++;
  }
  if (countTeclado == 4) {
    Estado = ESCOLHER;
  }
};

/* ************************************************************************************************ */
/* Method name:        LeCartao                     
/* Method description: Função que le cartão e compara com cards salvos no banco
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::LeCartao()
{
  if (bancoSenha.ComparaRfid(readC)) {
    lcd->escreveSenha("Card", "Correto");
    tranca1->AbreeFecha();
  } else {
    lcd->escreveSenha("Card", "Incorreto");
  }
  goToEspera();
};

/* ************************************************************************************************ */
/* Method name:        Escolher                     
/* Method description: Estado que espera input do usuário apos digitar a senha
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::Escolher()
{
  char letra;
  countTeclado = 0;
  letra = teclado->leTeclado();
  switch (letra) {
    case 'A':
      Estado = ABRESENHA;
      break;
    case 'B':
      senInput = "";
      if (bancoSenha.ComparaSenha(senInput)) {
        indexSenha = bancoSenha.ReturnIndexSenha(senInput);
        if (indexSenha == -1) {
          lcd->escreveSenha("Erro index", "");
          goToEspera();
        } else {
          Estado = TROCASENHA;
        }
      } else {
        lcd->escreveSenha("Senha", "Incorreta");
        goToEspera();
      }
      break;
    case 'C':
      if (bancoSenha.ComparaSenhaMestre(senInput)) {
        Estado = MENUMESTRE;
      } else {
        lcd->escreveSenha("Senha Mestre", "Incorreta");
        goToEspera();
      }
      Serial.print ("mestre");
      Serial.println (Estado);
      senInput = "";
      break;
    case '#':
      goToEspera();
      break;
    default:
      break;
  }
};

/* ************************************************************************************************ */
/* Method name:        MenuMestre                     
/* Method description: Menu de escolha após digitar a senha mestre, permite a troca da senha mestre
/* cadastro de card e acesso ao menu de edição das senhas.
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::MenuMestre()
{
  char letra;
  countTeclado = 0;
  letra = teclado->leTeclado();
  switch (letra) {
    case 'A':
      indexSenha = 25;
      Estado = TROCASENHA;
      senInput = "";
      break;
    case 'B'://Editar senha
      indexSenha = 0;
      Estado = EDITASENHA;
      break;
    case 'C'://Editar senha
      indexSenha = 0;
      Estado = CADASTRACARD;
      break;
    case '#':
      goToEspera();
      break;
    case 'D':
      break;
    default:
      break;
  }
};

/* ************************************************************************************************ */
/* Method name:        EditaSenha                     
/* Method description: Menu de edição das senhas, permite a edição da senhas salvas remoção das 
/* senhas e a troca das senhas
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::EditaSenha()
{
  char letra;
  countTeclado = 0;
  lcd->escreveSenha(String(indexSenha), bancoSenha.ReturnSenha(indexSenha));
  letra = teclado->leTeclado();
  switch (letra) {
    case 'A':
      Estado = TROCASENHA;
      countTeclado = 0;
      senInput = "";
      Serial.print(indexSenha);
      break;
    case 'B'://Editar senha
      Estado = REMOVER;
      break;
    case 'C':
      indexSenha++;
      if (indexSenha > 9) {
        indexSenha = 0;
      }
      break;
    case 'D':
      indexSenha--;
      if (indexSenha < 0) {
        indexSenha = 9;
      }
      break;
    case '#':
      goToEspera();
      break;
    default:
      break;
  }
};

/* ************************************************************************************************ */
/* Method name:        AbreSenha                     
/* Method description: Verifica se a senha está correta, case esteja, abre a tranca
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::AbreSenha() {
  if (bancoSenha.ComparaSenha(senInput)) {
    lcd->escreveSenha("Senha", "Correto");
    tranca1->AbreeFecha();
  } else {
    lcd->escreveSenha("Senha", "Incorreta");
  }
  goToEspera();
};

/* ************************************************************************************************ */
/* Method name:        NovaSenha                     
/* Method description: Recebe input da nova senha a ser cadastrada
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::NovaSenha() {
  char letra;
  letra = teclado->leTeclado();
  readC = rfid->LeTag();
  if (bancoSenha.ComparanoRfid(readC)) {
    Estado = LECARTAO;
  } else if (letra != ' ') {
    lcd->escreveSenha("Digite a Senha", senInput);
    Serial.print(letra);
    senInput += letra;
    lcd->escreveSenha("senha", senInput);
    countTeclado ++;
  }
  if (countTeclado == 4) {
    String retorno = bancoSenha.NovaSenha(senInput);
    lcd->escreveSenha(retorno, "");
    goToEspera();
  }
};

/* ************************************************************************************************ */
/* Method name:        TrocaSenha                     
/* Method description: Recebe input da nova senha a ser cadastrada, e realiza a troca com senha antiga
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::TrocaSenha() {
  char letra;
  letra = teclado->leTeclado();
  if (letra != ' ') {
    lcd->escreveSenha("Digite a Senha", senInput);
    Serial.print(letra);
    senInput += letra;
    lcd->escreveSenha("senha", senInput);
    countTeclado ++;
  }
  if (countTeclado == 4) {
    Serial.print(indexSenha);
    bancoSenha.TrocaSenha(senInput, indexSenha);
    lcd->escreveSenha("Senha salva", "");
    goToEspera();
  }
};

/* ************************************************************************************************ */
/* Method name:        Remove                     
/* Method description: Remove senha do banco
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::Remove() {
  bancoSenha.RemoveSenha(indexSenha);
  lcd->escreveSenha("Senha removida", "");
  goToEspera();
};

/* ************************************************************************************************ */
/* Method name:        CadastraCard                     
/* Method description: Cadastra card rfid no banco
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::CadastraCard() {
  readC = rfid->LeTag();
  if (bancoSenha.ComparanoRfid(readC)) {
    bancoSenha.NovoCard(readC);
    goToEspera();
  }
};

/* ************************************************************************************************ */
/* Method name:        goToEspera                     
/* Method description: função que limpa variaveis de senha e imput e seta estado como espera
/* Input params:       n/a                          
/* Output params:      n/a                        
/* ************************************************************************************************ */
void Maquina::goToEspera() {
  countTeclado = 0;
  senInput = "";
  Estado = ESPERA;
};
