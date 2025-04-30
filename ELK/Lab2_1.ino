int status;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  status = digitalRead(2);
  if (status == 1){
    digitalWrite(3,LOW);
  }
  else {
    digitalWrite(3,HIGH);
  }
}
