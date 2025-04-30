int buttonState = 0;
int lastButtonState = 0;
bool ledOn = false;

void setup() {
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(2);

  if (buttonState == 0 && lastButtonState == 1) {
    ledOn = !ledOn; 
    delay(100); 
  }
  lastButtonState = buttonState;

  int val = analogRead(A0);
  int brightness = map(val, 0, 1023, 0, 255);

  if (ledOn) {
    analogWrite(3, brightness);
  } else {
    analogWrite(3, 0);
  }
}
