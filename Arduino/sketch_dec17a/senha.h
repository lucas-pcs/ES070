#include <EEPROM.h>
#include <string.h>

class Senha
{
    // variaveis
  private:
    // variaveis mocadas para teste
    // byte readCard[4] = {0x5A, 0xA8, 0xED, 0x80};  //tag do nosso RFID -> classe senha
    
    byte noCard[4] = {0x00, 0x00, 0x00, 0x00};  //leitura vazia do RFID = nocard
    byte memoriaSenha[10];
    byte memoriaCard[10];
    // metodos
  public:
    Senha();
    bool ComparaSenha(String input);
    String NovaSenha(String input);
    String ReturnSenha(int index);
    int ReturnIndexSenha(String input);
    void TrocaSenha(String input, int index);
    void TrocaSenhaMestre(String input);
    bool ComparaSenhaMestre(String input);
    void RemoveSenha(int index);
    bool ComparanoRfid(byte *Card);
    bool ComparaRfid(byte *Card);
    String NovoCard(byte * Card);
    void RemoveCard(int index);
};

Senha::Senha()
{
  //Ultilizar para cadastrar as senhas iniciais

    //   LIMPA VETOR E CRIA SENHA INICIAL
     for (int i = 0; i < 255; i++) {
      Serial.print (EEPROM.read(i));
      EEPROM.write(i, 0);
    }
    NovaSenha("1234");
    NovaSenha("1235");
    String input = "1212";
    int enderecoSenha = 110;
    for (int y = 0; y < 4; y++) {
      EEPROM.write(enderecoSenha + y, input[y]);
      Serial.print (EEPROM.read(enderecoSenha + y));
      Serial.println (input[y]);
    }
    Serial.println ("");
    for (int i = 0; i < 255; i++) {
      Serial.print (EEPROM.read(i));
    }
    Serial.println ("");
}

bool Senha::ComparaSenha(String input)
{
  String mensagem = "";
  char pos;
  for (int i = 0; i < 10; i++) {
    Serial.print ("Espaço ");
    Serial.println (EEPROM.read(i));
    memoriaSenha[i] = EEPROM.read(i);
    if (memoriaSenha[i] == 1) {
      for (int y = 0; y < 4; y++) {
        int enderecoSenha = (i * 4) + 10 + y;
        pos = EEPROM.read(enderecoSenha);
        mensagem = mensagem + pos; // Montamos string de saídaa
      }
      Serial.print ("Senha ");
      Serial.println (mensagem);
      if (mensagem.compareTo(input) == 0) {
        return true;
      }
      mensagem = "";
    }
  }
  return false;
}

String Senha::NovaSenha(String input)
{
  for (int i = 0; i < 10; i++) {
    Serial.print ("Espaço ");
    Serial.println (EEPROM.read(i));
    memoriaSenha[i] = EEPROM.read(i);
    if (memoriaSenha[i] == 0) {
      for (int y = 0; y < 4; y++) {
        int enderecoSenha = (i * 4) + 10 + y;
        EEPROM.write(enderecoSenha, input[y]);
      }
      EEPROM.write(i, 1);
      return "senha salva";
    }
  }
  return "memoria cheia";
}

void Senha::TrocaSenha(String input, int index)
{
  for (int y = 0; y < 4; y++) {
    int enderecoSenha = (index * 4) + 10 + y;
    EEPROM.write(enderecoSenha, input[y]);
  }
  EEPROM.write(index, 1);
}

void Senha::RemoveSenha(int index)
{
  int enderecoSenha = (index * 4) + 10;
  for (int i = enderecoSenha; i < enderecoSenha + 4; i++) {
    Serial.print (EEPROM.read(i));
    EEPROM.write(index, 0);
  }
}

int Senha::ReturnIndexSenha(String input)
{
  String mensagem = "";
  char pos;
  for (int i = 0; i < 10; i++) {
    memoriaSenha[i] = EEPROM.read(i);
    if (memoriaSenha[i] == 1) {
      for (int y = 0; y < 4; y++) {
        int enderecoSenha = (i * 4) + 10 + y;
        pos = EEPROM.read(enderecoSenha);
        mensagem = mensagem + pos; // Montamos string de saídaa
      }
      if (mensagem.compareTo(input) == 0) {
        return i;
      }
      mensagem = "";
    }
  }
  return -1;
}

String Senha::ReturnSenha(int index)
{
  String mensagem = "";
  char pos;
  memoriaSenha[index] = EEPROM.read(index);
  if (memoriaSenha[index] == 1) {
    for (int y = 0; y < 4; y++) {
      int enderecoSenha = (index * 4) + 10 + y;
      pos = EEPROM.read(enderecoSenha);
      mensagem = mensagem + pos; // Montamos string de saídaa
    }
    return mensagem;
  }
  mensagem = "";
  return mensagem;
}

bool Senha::ComparaSenhaMestre(String input)
{
  String mensagem = "";
  char pos;
  for (int y = 0; y < 4; y++) {
    int enderecoSenha = 110 + y;
    pos = EEPROM.read(enderecoSenha);
    mensagem = mensagem + pos; // Montamos string de saída
  }
  Serial.print ("mestre");
  Serial.println (mensagem);
  if (mensagem.compareTo(input) == 0) {
    return true;
  }
  mensagem = "";
  return false;
}

bool Senha::ComparanoRfid(byte * Card)
{
  bool compare = true;
  for (int i = 0; i < sizeof(noCard); i++) {
    if (noCard[i] != Card[i]) {
      compare = false;
    }
  }
  if (compare) {
    return false;
  }
}

bool Senha::ComparaRfid(byte * Card)
{
  bool compare = true;
  for (int i = 200; i < 210; i++) {
    memoriaCard[i] = EEPROM.read(i);
    if (memoriaCard[i] == 1) {
      compare = true;
      for (int y = 0; y < sizeof(noCard); y++) {
        int enderecoSenha = (i * 4) + 210 + y;
        if (EEPROM.read(enderecoSenha) != Card[y]) {
          compare = false;
        }
      }
      if (compare) {
        return true;
      }
    }
  }
  return false;
}

String Senha::NovoCard(byte * Card)
{
  for (int i = 200; i < 210; i++) {
    Serial.print ("Espaço ");
    Serial.println (EEPROM.read(i));
    memoriaSenha[i] = EEPROM.read(i);
    if (memoriaSenha[i] == 0) {
      for (int y = 0; y < 4; y++) {
        int enderecoSenha = (i * 4) + 210 + y;
        EEPROM.write(enderecoSenha, Card[y]);
      }
      EEPROM.write(i, 1);
      return "senha salva";
    }
  }
  return "memoria cheia";
}

void Senha::RemoveCard(int index)
{
  int enderecoSenha = (index * 4) + 210;
  for (int i = enderecoSenha; i < enderecoSenha + 4; i++) {
    Serial.print (EEPROM.read(i));
    EEPROM.write(i, 0);
  }
  EEPROM.write(index, 0);
}
