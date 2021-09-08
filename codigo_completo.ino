//HRSR04 sensor
#define HRSR04_trig_pin 7
#define HRSR04_echo_pin 6
float distancy;

//Motor DC
int IN1 = 5; //roxo
int IN2 = 4; //cinza
int IN3 = 3; //azul
int IN4 = 2; //amarelo

//Definição dos pinos de controle do motor
#define IN2 4 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta ATV_A ponte H;
#define IN4 2 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta ATV_B ponte H;
#define IN1 5 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define IN3 3 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_S1 9
#define pin_S2 8
bool Sensor1 = 0;
bool Sensor2 = 0;

//variável responsável por controlar a velocidade dos motores
int velocidade = 150;

void setup()
{
  //sensor HCSR-04
  pinMode(HRSR04_trig_pin, OUTPUT);
  pinMode(HRSR04_echo_pin, INPUT);

  //Motor DC
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //sensor TCRT5000
  pinMode(pinoSensor, INPUT);
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoLed, LOW);

  //Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);

  //Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  Serial.begin(9600);
}

void loop()
{
  distancy = getUltrassonicDistance();

  //Motor DC
  //motor A = preto e branco
  //motor B = verde e cinza

  //Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
  Sensor1 = hasLight(pin_S1);
  Sensor2 = hasLight(pin_S2);

  Serial.print("Distancia em cm: ");
  Serial.println(distancy);
  Serial.print("sensor esquerdo ligado? - ");
  Serial.println(Sensor1);
  Serial.print("sensor direito ligado? - ");
  Serial.println(Sensor2);

  delay(200);

  if (distancy <= 20)
  { // Se a distância lida pelo sensor for menor ou igual que 20 centimetros

    // Motor lado esquerdo parado
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // Motor lado direito parado
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else
  { // Se não, ou seja, se a distância for maior que 20 centimetros
    //Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
    if ((Sensor1 == 0) && (Sensor2 == 0))
    { // Se detectar na extremidade das faixas duas cores brancas

      analogWrite(IN2, velocidade); // Ambos motores ligam na mesma velocidade
      analogWrite(IN4, velocidade);
    }
    if ((Sensor1 == 1) && (Sensor2 == 0))
    { // Se detectar um lado preto e o outro branco

      analogWrite(IN2, 0);          // O motor 1 desliga
      analogWrite(IN4, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar
    }
    if ((Sensor1 == 0) && (Sensor2 == 1))
    { // Se detectar um lado branco e o outro preto

      analogWrite(IN2, velocidade); //O motor 1 fica ligado
      analogWrite(IN4, 0);          // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
    }
  }
}

float getUltrassonicDistance()
{
  digitalWrite(HRSR04_trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(HRSR04_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(HRSR04_trig_pin, LOW);
  float timeEcho = pulseIn(HRSR04_echo_pin, HIGH);
  float distancy = (timeEcho * 340.90) / 2;
  float distancyInCentimeters = distancy / 10000;

  return distancyInCentimeters;
}

bool hasLight(byte pin)
{
  return (digitalRead(pin) == 0);
}
