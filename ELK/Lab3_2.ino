const int SER = 8;
const int RCLK = 7;
const int SRCLK = 6;

byte digits[10] = {
  0b00000011, // 0
  0b10011111, // 1
  0b00100101, // 2
  0b00001101, // 3
  0b10011001, // 4
  0b01001001, // 5
  0b01000001, // 6
  0b00011111, // 7
  0b00000001, // 8
  0b00001001  // 9
};

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    displayDigit(digits[i]);
    delay(1000);
  }
}

void displayDigit(byte value) {
  digitalWrite(RCLK, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, value); 
  digitalWrite(RCLK, HIGH);
}
