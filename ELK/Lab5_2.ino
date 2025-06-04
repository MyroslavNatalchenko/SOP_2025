#include <Servo.h>
Servo myservo;
int val = 0;


void setup() {
  myservo.attach(3);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
  float volt = val * (5.0 / 1023.0);
  Serial.println(volt);
  int degree = map(volt, 0, 5, 0, 180);
  myservo.write(degree);
}
