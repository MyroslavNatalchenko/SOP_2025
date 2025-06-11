int buttonState = 0;
int lastButtonState = 0;
bool ledOn = false;

void setup()
{
  pinMode(3, OUTPUT);      
  pinMode(4, OUTPUT);     
  pinMode(2, INPUT_PULLUP); 
}

void loop()
{
  int value_without_map = analogRead(A0);
  int value = map(value_without_map, 0, 1023, 0, 255);
  int value_reversed = 255-value;

  buttonState = digitalRead(2);

  if (buttonState==0 && lastButtonState==1) {
    ledOn=!ledOn; 
    delay(100); 
  }
  lastButtonState=buttonState;

  if (!ledOn) {
    analogWrite(3, value);
    analogWrite(4, value_reversed);
  } else {
    analogWrite(3, value_reversed);
    analogWrite(4, value);
  }
}
