byte digits[10] = {
  0b00111111, 
  0b00000110, 
  0b01011011, 
  0b01001111, 
  0b01100110, 
  0b01101101, 
  0b01111101, 
  0b00000111, 
  0b01111111, 
  0b01101111
};

int pins[8]={
  2,3,4,5,6,7,8,9
};

void displayDigit(byte digitByte) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pins[i], !bitRead(digitByte, i));
  }
}

void setup() {
  for (int i=0;i<=7;i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    displayDigit(digits[i]);
    delay(1000); 
  }
}
