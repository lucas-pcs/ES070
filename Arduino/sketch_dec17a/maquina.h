#include "teclado.h"
#include "tranca.h"
#include "lcd.h"
#include "rfid.h"
#include "senha.h"

//Estados
#define ESPERA     1
#define CADASTRO   2
#define ESCOLHER   3
#define REMOVER    4
#define LECARTAO   5
#define ABRESENHA  6
#define NOVASENHA  7
#define TROCASENHA 8
#define MENUMESTRE 9
#define EDITASENHA 10

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
  public:  // metodos
    Maquina();        // metodo que coloca a maquina de estados no estado ESPERA
    Maquina(Tranca *tranca2, Teclado *teclado2, Lcd *lcd2, RFID *rfid2);
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
};

// construtor 1
Maquina::Maquina()
{
  senInput = "";
  Estado = ESPERA;
  Serial.println("MAQUINA metodo 1 inicializada");
};

// construtor 2
Maquina::Maquina(Tranca *tranca2, Teclado *teclado2, Lcd *lcd2, RFID *rfid2)
{
  senInput = "";
  Estado = ESPERA;
  countTeclado = 0;
  tranca1 = tranca2;                  //cria o objeto traca
  teclado = teclado2;                 //cria o objeto teclado
  lcd = lcd2;                         //cria o objeto lcd
  rfid = rfid2;                       //cria o objeto lcd
  Serial.println("MAQUINA metodo 2");
};

void Maquina::setEstado(int estado)
{
  Estado = estado;
};

int Maquina::getEstado()
{
  return Estado;
};

void Maquina::Espera()
{
  char letra;
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


void Maquina::LeCartao()
{
  if (bancoSenha.ComparaRfid(readC)) {
    tranca1->AbreeFecha();
    lcd->escreveSenha("Card", "Correto");
  } else {
    lcd->escreveSenha("Card", "Incorreto");
  }
  senInput = "";
  Estado = ESPERA;
};

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
      if (bancoSenha.ComparaSenha(senInput)) {
        indexSenha = bancoSenha.ReturnIndexSenha(senInput);
        senInput = "";
        if (indexSenha == -1) {
          lcd->escreveSenha("Erro index", "");
          senInput = "";
          Estado = ESPERA;
        } else {
          Estado = TROCASENHA;
        }
      } else {
        lcd->escreveSenha("Senha", "Incorreta");
        Estado = ESPERA;
        senInput = "";
      }
      break;
    case 'C':
      if (bancoSenha.ComparaSenhaMestre(senInput)) {
        Estado = MENUMESTRE;
      } else {
        lcd->escreveSenha("Senha Mestre", "Incorreta");
        senInput = "";
        Estado = ESPERA;
      }
      Serial.print ("mestre");
      Serial.println (Estado);
      senInput = "";
      break;
    case '#':
      indexSenha = 0;
      Estado = ESPERA;
      senInput = "";
      break;
    default:
      break;
  }
};

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
    case '#':
      indexSenha = 0;
      Estado = ESPERA;
      senInput = "";
      break;
    case 'D':
      break;
    default:
      break;
  }
};

void Maquina::EditaSenha()
{
  char letra;
  countTeclado = 0;
  lcd->escreveSenha(String(indexSenha), bancoSenha.ReturnSenha(indexSenha));
  letra = teclado->leTeclado();
  switch (letra) {
    case 'A':
      Estado = TROCASENHA;
      senInput = "";
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
      indexSenha = 0;
      Estado = ESPERA;
      senInput = "";
      break;
    default:
      break;
  }
};

void Maquina::AbreSenha() {
  if (bancoSenha.ComparaSenha(senInput)) {
    lcd->escreveSenha("Senha", "Correto");
    tranca1->AbreeFecha();
  } else {
    lcd->escreveSenha("Senha", "Incorreta");
  }
  senInput = "";
  Estado = ESPERA;
};

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
    senInput = "";
    Estado = ESPERA;
  }
};

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
    bancoSenha.TrocaSenha(senInput, indexSenha);
    lcd->escreveSenha("Senha salva", "");
    senInput = "";
    Estado = ESPERA;
  }
};

void Maquina::Remove(){
  bancoSenha.RemoveSenha(indexSenha);
  lcd->escreveSenha("Senha removida", "");
}
