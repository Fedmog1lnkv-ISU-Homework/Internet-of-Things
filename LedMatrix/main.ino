const int PIN_7 = 7;
const int PIN_8 = 8;
const int PIN_11 = 11;
const int PIN_12 = 12;

void setLeds(int pin1, int pin2, int pin3, int pin4)
{
  digitalWrite(PIN_7, pin1);
  digitalWrite(PIN_8, pin2);
  digitalWrite(PIN_11, pin3);
  digitalWrite(PIN_12, pin4);
}

void reset()
{
  setLeds(0, 0, 1, 1);
}

int basicStates[][4]{
    {LOW, LOW, LOW, LOW},    // 0
    {HIGH, LOW, LOW, HIGH},  // 1
    {HIGH, LOW, HIGH, LOW},  // 2
    {LOW, HIGH, LOW, HIGH},  // 3
    {LOW, HIGH, HIGH, LOW},  // 4
    {HIGH, LOW, LOW, LOW},   // 1,2
    {LOW, HIGH, LOW, LOW},   // 3,4
    {HIGH, HIGH, LOW, HIGH}, // 1,3
    {HIGH, HIGH, HIGH, LOW}, // 2,4
};

int hardStates[][2][4]{
    {{HIGH, LOW, LOW, HIGH}, {LOW, HIGH, HIGH, LOW}}, // 1,4
    {{HIGH, LOW, HIGH, LOW}, {LOW, HIGH, LOW, HIGH}}, // 2,3
    {{HIGH, LOW, LOW, LOW}, {LOW, HIGH, LOW, HIGH}},  // 1,2,3
    {{HIGH, LOW, HIGH, LOW}, {LOW, HIGH, LOW, LOW}},  // 2,3,4
    {{HIGH, LOW, LOW, HIGH}, {LOW, HIGH, LOW, LOW}},  // 3,4,1
    {{HIGH, LOW, LOW, LOW}, {LOW, HIGH, HIGH, LOW}},  // 4,1,2
    {{HIGH, LOW, LOW, LOW}, {LOW, HIGH, LOW, LOW}},   // 1,2,3,4
    {{LOW, LOW, LOW, LOW}, {LOW, LOW, LOW, LOW}},     // LEDs off
};

void run(int pin1, int pin2, int pin3, int pin4)
{
  reset();
  setLeds(pin1, pin2, pin3, pin4);
  delay(1000);
}

void run(int pin11, int pin12, int pin13, int pin14, int pin21, int pin22, int pin23, int pin24)
{
  for (int j = 0; j < 1000; j++)
  {
    setLeds(pin11, pin12, pin13, pin14);
    delay(1);
    setLeds(pin21, pin22, pin23, pin24);
    delay(1);
  }
}

void setup()
{
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_11, OUTPUT);
  pinMode(PIN_12, OUTPUT);
}

void loop()
{
  for (int i = 0; i < sizeof(basicStates) / sizeof(basicStates[0]); i++)
  {
    run(basicStates[i][0], basicStates[i][1], basicStates[i][2], basicStates[i][3]);
  }
  reset();

  for (int i = 0; i < sizeof(hardStates) / sizeof(hardStates[0]); i++)
  {
    run(hardStates[i][0][0], hardStates[i][0][1], hardStates[i][0][2], hardStates[i][0][3], hardStates[i][1][0], hardStates[i][1][1], hardStates[i][1][2], hardStates[i][1][3]);
    reset();
  }
}
