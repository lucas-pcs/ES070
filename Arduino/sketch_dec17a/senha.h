/* ************************************************************************************************ */
/* File name:          senha.h               
/* File description:   Arquivo com funções de gravação e escrita no banco EEPROM, e de comparação                     
/* com senhas salvas
/* Author name:        Luiz Furlan                       
/* Author name:        Lucas Pereira                     
/* Author name:        Gabriel Murizine                  
/* Creation date:                               
/* Revision date:                               
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        Senha                     
/* Method description: IConstrutor da classe (usada para setar senhas iniciais)
/* Input params:       n/a                         
/* Output params:      n/a                         
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        ComparaSenha                     
/* Method description: Compara senha recebida com banco e informa se esta correta ou não
/* Input params:       String input : senha digitada pelo usuário                      
/* Output params:      bool : retorna true em caso da senha correta, e false caso incorreta                        
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        NovaSenha                     
/* Method description: Adiciona senha recebida, caso haja espaço, no bd
/* Input params:       String input : senha digitada pelo usuário                        
/* Output params:      String : retorna informação de sucesso ou erro                       
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        TrocaSenha                     
/* Method description: Troca a senha dalva no bd
/* Input params:       String input: senha digitada pelo usuário, int index: pocição da senha no vetor                        
/* Output params:      n/a                     
/* ************************************************************************************************ */
void Senha::TrocaSenha(String input, int index)
{
  for (int y = 0; y < 4; y++) {
    int enderecoSenha = (index * 4) + 10 + y;
    EEPROM.write(enderecoSenha, input[y]);
  }
  EEPROM.write(index, 1);
}

/* ************************************************************************************************ */
/* Method name:        RemoveSenha                     
/* Method description: Remove senha de acordo com index
/* Input params:       int index: lugar na memória que está salvo a senha                        
/* Output params:      n/a                     
/* ************************************************************************************************ */
void Senha::RemoveSenha(int index)
{
  int enderecoSenha = (index * 4) + 10;
  for (int i = enderecoSenha; i < enderecoSenha + 4; i++) {
    Serial.print (EEPROM.read(i));
    EEPROM.write(index, 0);
  }
}

/* ************************************************************************************************ */
/* Method name:        ReturnIndexSenha                     
/* Method description: Retorna o index do lugar da memória onde está salva a senha, caso ela exista
/* Input params:       String input: senha digitada pelo usuário                       
/* Output params:      int : retorna index da senha caso exista                     
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        ReturnSenha                     
/* Method description: Retorna senha de acordo com index enviado
/* Input params:       int index: index da senha                      
/* Output params:      String : retorna string da senha                     
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        ComparaSenhaMestre                     
/* Method description: Verifica se a senha enviada e a senha do admin
/* Input params:       String input: recebe senhadigitada pelo usuário                      
/* Output params:      bool : retorna true se a senha for correta, e false se incorreta                    
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        ComparanoRfid                     
/* Method description: Verifica se foi aproximado um card (caso o valor seja o valor NoCard). Toda
/* a vez que a função le card do rfid é chamada, ele pode retornar o valor do card (case ele seja aproximado)
/* ou um valor vazio. Essa função verifica se o valor é vazio
/* Input params:       byte * Card: recebe leitura de card                     
/* Output params:      bool : retorna false se o valor do card for vazio, e true se for correto                    
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        ComparaRfid                     
/* Method description: Verifica se o card aproximado é um dos cards salvos no banco
/* Input params:       byte * Card: recebe leitura de card                      
/* Output params:      bool : retorna false se o valor do card for vazio, e true se for correto                   
/* ************************************************************************************************ */
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

/* ************************************************************************************************ */
/* Method name:        NovoCard                     
/* Method description: Adiciona novo card no banco
/* Input params:       byte * Card: recebe leitura de card                      
/* Output params:      String : retorna mensagem de sucesso, ou de erro no cadastro                   
/* ************************************************************************************************ */
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


/* ************************************************************************************************ */
/* Method name:        RemoveCard                     
/* Method description: Adiciona novo card no banco
/* Input params:       int index: indica index do card a ser removido                      
/* Output params:      n/a                  
/* ************************************************************************************************ */
void Senha::RemoveCard(int index)
{
  int enderecoSenha = (index * 4) + 210;
  for (int i = enderecoSenha; i < enderecoSenha + 4; i++) {
    Serial.print (EEPROM.read(i));
    EEPROM.write(i, 0);
  }
  EEPROM.write(index, 0);
}
