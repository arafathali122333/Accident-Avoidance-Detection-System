#define trigPin 2
#define echoPin 3
#define motor 10
#define motor2 12
void setup(){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(motor2, OUTPUT);
}
void loop(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 10){
    digitalWrite(motor,LOW);
    digitalWrite(motor2,HIGH);
    delay(4000);
    digitalWrite(motor,LOW);
    digitalWrite(motor2,LOW);
    exit(0);
  }
  else {
    digitalWrite(motor,HIGH);
    digitalWrite(motor2,LOW);
  }
  
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
