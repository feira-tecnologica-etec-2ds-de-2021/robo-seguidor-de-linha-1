//HRSR04 sensor
const byte HRSR04_trig_pin = 7;
const byte HRSR04_echo_pin = 6;
float distancy;

//TCRT5000 sensor
int pinoLed = 12;
int pinoSensor = 8;

//Definição dos pinos de controle do motor
#define IN1 2 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta ATV_A ponte H;
#define IN2 3 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta ATV_B ponte H;
#define IN3 4 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define IN4 5 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_S1 9
#define pin_S2 8
bool Sensor1 = 0;
bool Sensor2 = 0;

//variável responsável por controlar a velocidade dos motores
#define velocidade 200   
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
  digitalWrite(IN1, 255);
  digitalWrite(IN2, 255);
  digitalWrite(IN3, 255);
  digitalWrite(IN4, 255);

  //Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  Serial.begin(9600);
}

void loop() {
  distancy = getUltrassonicDistance();
  //Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);

  if (distancy <= 5)
  { // Se a distância lida pelo sensor for menor ou igual que 20 centimetros

    // Motor lado esquerdo parado
    analogWrite(IN1, 255);
    analogWrite(IN2, 255);

    // Motor lado direito parado
    analogWrite(IN3, 255);
    analogWrite(IN4, 255);
  }
  else
  { // Se não, ou seja, se a distância for maior que 20 centimetros
    //Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
    if ((Sensor1 == 0) && (Sensor2 == 0))
    { // Se detectar na extremidade das faixas duas cores brancas

        analogWrite(IN1, velocidade); // Ambos motores ligam na mesma velocidade
        analogWrite(IN2, velocidade);
        analogWrite(IN3, velocidade); 
        analogWrite(IN4, velocidade);
    }
    if ((Sensor1 == 1) && (Sensor2 == 0))
    { // Se detectar um lado preto e o outro branco

      analogWrite(IN4,255 ); // O motor 1 desliga
      analogWrite(IN3, 255); 
      analogWrite(IN2, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar
      analogWrite(IN1, velocidade); 
    }
    if ((Sensor1 == 0) && (Sensor2 == 1))
    { // Se detectar um lado branco e o outro preto

      analogWrite(IN4, velocidade); //O motor 1 fica ligado
      analogWrite(IN3, velocidade);
      analogWrite(IN2, 255);
      analogWrite(IN1, 255);          // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
    }
  }
}

float getUltrassonicDistance() {
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

bool hasLight() {
  return (digitalRead(pinoSensor) == 1);
}
