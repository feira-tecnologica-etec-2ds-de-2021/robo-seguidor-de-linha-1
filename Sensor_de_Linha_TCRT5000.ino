int pinoLed = 12; //PINO DIGITAL UTILIZADO PELO LED  
int pinoSensor = 8; //PINO DIGITAL UTILIZADO PELO SENSOR

void setup() {
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA   
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
}

void loop() {
  if (digitalRead(pinoSensor) == LOW){ 
        digitalWrite(pinoLed, HIGH); //ACENDE O LED
  }else{
        digitalWrite(pinoLed, LOW); //apaga O LED
  } 
}
