const byte HRSR04_trig_pin = 7;
const byte HRSR04_echo_pin = 6;

float ultrassonicDistancy;

void setup(){
    pinMode(HRSR04_trig_pin, OUTPUT);
    pinMode(HRSR04_echo_pin, INPUT);
}

void loop(){



}

float getUltrassonicDistance(){
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
