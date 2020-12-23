class Tranca
{
  private:
    int _Porta;
    bool _Estado;   
  public:
    Tranca(int Porta);
    int Porta();
    bool Estado();
    void Abre();
    void Fecha();
    void AbreeFecha()
};

Tranca::Tranca(int Porta)
{
  _Porta = Porta;
  _Estado = false;
  pinMode(_Porta, OUTPUT);   //Define a porta como saída
  analogWrite(_Porta, 255);
  Serial.print("O tranca1 esta: ");
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
  _Estado = true;
}

void Tranca::Fecha()
{
  analogWrite(_Porta, 255);
  _Estado = false;
}

void Tranca::AbreeFecha()
{
      tranca1->Abre();
      delay(3000);
      tranca1->Fecha();
}
