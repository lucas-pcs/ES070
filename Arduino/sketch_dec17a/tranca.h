class Tranca
{
    // variaveis
  private:
    int _Porta;
    bool _Estado;
    // metodos
  public:
    Tranca(int Porta);
    int Porta();
    bool Estado();
    void Abre();
    void Fecha();
    void AbreeFecha();
};

Tranca::Tranca(int Porta)
{
  _Porta = Porta;
  _Estado = false;
  pinMode(_Porta, OUTPUT);   //Define a porta como saída
  analogWrite(_Porta, 255);  // controla o estado inicial do relé
  Serial.print("A tranca está ligada ao pino: ");
  Serial.println(_Porta);
}

int Tranca::Porta()
{
  return _Porta;
}

bool Tranca::Estado()
{
  return _Estado;
}

void Tranca::Abre()
{
  analogWrite(_Porta, 0);
  Serial.println("Abril");
  _Estado = true;
}

void Tranca::Fecha()
{
  analogWrite(_Porta, 255);
  _Estado = false;
}

void Tranca::AbreeFecha()
{
  Abre();
  delay(3000);
  Fecha();
}
