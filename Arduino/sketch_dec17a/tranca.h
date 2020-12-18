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
};

Tranca::Tranca(int Porta)
{
  _Porta = Porta;
  _Estado = false;
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
  digitalWrite(_Porta, HIGH);
  _Estado = true;
}

void Tranca::Fecha()
{
  digitalWrite(_Porta, LOW);
  _Estado = false;
}
