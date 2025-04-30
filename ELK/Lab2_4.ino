int buzzerPin = 11;

int frequencies[] = {
  330, 330, 330,   // eee
  330, 330, 330,   // eee
  330, 392, 262, 294, 330, // egcde
  349, 349, 349,   // fff
  349, 330, 330,   // ffee
  330, 330, 392, 392, 349, 294, 262 // eeggfdc
};

int rhythm[] = {
  2,2,3,1, 2,2,3,1, 2,2,3,1,4,4, 2,2,3,0, 1,2,2,2,0, 1,1,2,2,2,2,4,4
};

int noteCount = sizeof(frequencies) / sizeof(frequencies[0]);

void setup() {
  for (int i = 0; i < noteCount; i++) {
    int duration = 260 * rhythm[i];  
    if (frequencies[i] != 0) {
      tone(buzzerPin, frequencies[i], duration);
    }
    delay(duration);  
    noTone(buzzerPin);
  }
}

void loop() {
}
