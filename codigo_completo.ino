//HRSR04 sensor
const byte HRSR04_trig_pin = 7;
const byte HRSR04_echo_pin = 6;
float distancy;

//Motor DC
int IN1 = 5; //roxo
int IN2 = 4; //cinza
int IN3 = 3; //azul
int IN4 = 2; //amarelo

//TCRT5000 sensor
int pinoLed = 12;
int pinoSensor = 8;

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

  Serial.begin(9600);
}

void loop()
{
  distancy = getUltrassonicDistance();

  Serial.print("Distancia em cm: ");
  Serial.println(distancy);
  delay(200);

  if (distancy <= 20) {
    // Motor lado esquerdo parado
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // Motor lado direito parado
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

  }
  else {
    //Gira o Motor A no sentido horario
    digitalWrite(IN1, HIGH);
    delay(2000);
    digitalWrite(IN2, LOW);


    //Gira o Motor B no sentido horario
    digitalWrite(IN3, LOW);
    delay(2000);
    digitalWrite(IN4, HIGH);
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

bool hasLight(){
  return (digitalRead(pinoSensor) == 1);
}