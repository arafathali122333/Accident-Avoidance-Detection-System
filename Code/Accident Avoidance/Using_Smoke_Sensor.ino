int motor = 10;
int smokeA0 = A5;
int sensorThres = 300;
void setup() {
  pinMode(motor, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}
void loop() {
  int analogSensor = analogRead(smokeA0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  if (analogSensor > sensorThres)
  {
    digitalWrite(motor, LOW);
    exit(0);
  }
  else
  {
    digitalWrite(motor, HIGH);
  }
}
