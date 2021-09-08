//sensor HCSR-04
const byte HRSR04_trig_pin = 7;
const byte HRSR04_echo_pin = 6;
float distancia;


float ultrassonicDistancy;

void setup(){
    //sensor HCSR-04
    pinMode(HRSR04_trig_pin, OUTPUT);
    pinMode(HRSR04_echo_pin, INPUT);
    
    //Motor DC
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop(){
   //sensor HCSR-04
   distancia = getUltrassonicDistance(); 
  
   //Motor DC
   //motor A = preto e branco
   //motor B = verde e cinza

}

//Sensor HCSR-04 código
float getUltrassonicDistance(){
  digitalWrite(HRSR04_trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(HRSR04_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(HRSR04_trig_pin, LOW);
  float timeEcho = pulseIn(HRSR04_echo_pin, HIGH);
  float distancy = (timeEcho * 340.90) / 2;
  float distancyInCentimeters = distancy / 10000;
  Serial.begin(9600);
  Serial.print("Distancia em cm: ");
  Serial.println(distancia);
  delay(200);
    
    if (distancyInCentimeters <= 20) {// Se a distância lida pelo sensor for menor ou igual que 40 centimetros
 
         // Motor lado esquerdo parado
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, LOW);
         
         // Motor lado direito parado
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
         
         }
     else {// Se não, ou seja, se a distância for maior que 20 centimetros
          
            //Gira o Motor A no sentido horario
           digitalWrite(IN1, HIGH);
           delay(2000);
           digitalWrite(IN2, LOW);
           
           
           //Gira o Motor B no sentido horario
           digitalWrite(IN3, LOW);
           delay(2000);
           digitalWrite(IN4, HIGH);
     }
    
  return distancyInCentimeters;
}

//Motor DC 3 A 6V código
