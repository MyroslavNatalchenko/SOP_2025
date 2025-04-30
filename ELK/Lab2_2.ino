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
 
  for (int i=0;i<=255;i++){
    analogWrite(3,i);
    Serial.println(i);
  }
  for (int i=255;i>=0;i--){
    analogWrite(3,i);
    Serial.println(i);
  }
  delay(1000);
}
