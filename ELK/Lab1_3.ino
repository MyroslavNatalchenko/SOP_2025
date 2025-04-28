char morze;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  int cnt=0;
}

void loop() {
  if (Serial.available() > 0){
    morze = Serial.read();
    Serial.println(morze);
    if (morze == '-'){
      digitalWrite(2,HIGH);
      delay(3000);
      digitalWrite(2,LOW);
      delay(100);
    }
    if (morze == '.'){
      digitalWrite(2,HIGH);
      delay(1000);
      digitalWrite(2,LOW);
      delay(100);
    }
    if (morze == ' '){
      delay (3000);
    }
  }
  
}
