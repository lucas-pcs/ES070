class SensorPIR
{
    // variaveis
  private:
    int _iPorta;
	  int _iDetectaPresenca;
    // metodos
  public:
    SensorPIR(int iPorta);
    int leSensorPIR();
    int returnPorta();
};

SensorPIR::SensorPIR(int iPorta)
{
  _iPorta = iPorta;
  _iDetectaPresenca = 0;
  pinMode(iPorta, INPUT_PULLUP);
  //pinMode(_iPorta, INPUT);   //Define a porta como saída
  Serial.print("O sensor de presença foi inicializado na porta: ");
  Serial.println(_iPorta);
}
int SensorPIR::returnPorta()
{
  return _iPorta;
}

int SensorPIR::leSensorPIR()
{
  _iDetectaPresenca = digitalRead(_iPorta); // Lê o estado do sensor de presença em que 1 = sensor ativado
  return _iDetectaPresenca;
}
