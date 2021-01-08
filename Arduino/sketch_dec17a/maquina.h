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

Maquina::Maquina(Tranca *tranca2, Teclado *teclado2, Lcd *lcd2, RFID *rfid2, SensorPIR *sensorpir1)
{
  senInput = "";
  Estado = ESPERA;
  countTeclado = 0;
  tranca1 = tranca2;                  //cria o objeto traca
  teclado = teclado2;                 //cria o objeto teclado
  lcd = lcd2;                         //cria o objeto lcd
  rfid = rfid2;                       //cria o objeto lcd
  sensorpir = sensorpir1;
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
  Serial.println("ESTADO: Espera");
  char letra;
  letra = teclado->leTeclado();
  // readC = rfid->LeTag();
  
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
  Serial.println("ESTADO: LeCartao");
  if (bancoSenha.ComparaRfid(readC)) {
    lcd->escreveSenha("Card", "Correto");
    tranca1->AbreeFecha();
  } else {
    lcd->escreveSenha("Card", "Incorreto");
  }
  goToEspera();
};

void Maquina::Escolher()
{
  Serial.println("ESTADO: Escolher");
  char letra;
  countTeclado = 0;
  letra = teclado->leTeclado();
  if (letra != ' '){
  switch (letra) {
    case 'A':
      Estado = ABRESENHA;
      break;
     case 'B':
      if (bancoSenha.ComparaSenha(senInput)) {
        indexSenha = bancoSenha.ReturnIndexSenha(senInput);
        if (indexSenha == -1) {
          lcd->escreveSenha("Erro index", "");
          goToEspera();
        } else {
          countTeclado = 0;
          senInput = "";
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
    Serial.print("ESCOLHER FOI PRO DEFAULT e a letra escolhida é: ");
    Serial.println(letra);
      break;
  }
  }
};

void Maquina::MenuMestre()
{
  Serial.println("ESTADO: MenuMestre");
  char letra = teclado->leTeclado();
  countTeclado = 0;
  senInput = "";
  switch (letra) {
    case 'A': // Troca senha mestra
      indexSenha = 25;
      Estado = TROCASENHA;
      break;
    case 'D'://Editar qualquer senha
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
    case 'B':
      break;
    default:
      break;
  }
};

void Maquina::EditaSenha()
{
  Serial.println("ESTADO: EditaSenha");
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

void Maquina::AbreSenha() {
  Serial.println("ESTADO: AbreSenha");
  if (bancoSenha.ComparaSenha(senInput)) {
    lcd->escreveSenha("Senha", "Correto");
    tranca1->AbreeFecha();
  } else {
    lcd->escreveSenha("Senha", "Incorreta");
  }
  goToEspera();
};

void Maquina::NovaSenha() {
  Serial.println("ESTADO: NovaSenha");
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
    lcd->escreveSenha(retorno," ");
    goToEspera();
  }
};

void Maquina::TrocaSenha() {
  Serial.println("ESTADO: TrocaSenha");
  char letra;
  letra = teclado->leTeclado();
  lcd->escreveSenha("Digite a Senha", senInput);
  if (((letra >= '0') && (letra <= '9')  ) || ((letra == 'A') || (letra == 'B') || (letra == 'C') || (letra == 'D') || (letra == '#'))) {
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

void Maquina::Remove() {
  Serial.println("ESTADO: Remove");
  bancoSenha.RemoveSenha(indexSenha);
  lcd->escreveSenha("Senha removida", "");
  goToEspera();
};

void Maquina::CadastraCard() {
  Serial.println("ESTADO: CadastraCard");
  readC = rfid->LeTag();
  if (bancoSenha.ComparanoRfid(readC)) {
    bancoSenha.NovoCard(readC);
    goToEspera();
  }
};

void Maquina::goToEspera() {
  Serial.println("ESTADO: goToEspera");
  countTeclado = 0;
  senInput = "";
  Estado = ESPERA;
};
