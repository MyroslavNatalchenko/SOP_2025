int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  int brightness = map(val, 0, 1023, 0, 255);
  Serial.println(brightness);
  analogWrite(6,brightness);
}
