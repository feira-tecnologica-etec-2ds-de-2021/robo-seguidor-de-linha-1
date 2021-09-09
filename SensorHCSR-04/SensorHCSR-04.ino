//sensor HCSR-04
const byte HRSR04_trig_pin = 7;
const byte HRSR04_echo_pin = 6;
float distancia;

float ultrassonicDistancy;

void setup() {
  // put your setup code here, to run once:
  //sensor HCSR-04
    pinMode(HRSR04_trig_pin, OUTPUT);
    pinMode(HRSR04_echo_pin, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
     //sensor HCSR-04
   distancia = getUltrassonicDistance(); 
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
  delay(500);

  return distancyInCentimeters;
}
