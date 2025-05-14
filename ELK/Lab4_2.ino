/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

unsigned long time;
unsigned long time_1000;
unsigned long time_500;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  time = millis();
  time_1000 = time/1000;
  time_500 = time/500;    

  digitalWrite(3, time_1000%2==0);
  digitalWrite(4, time_500%2==0);
  if (time%2500 <= 2000) digitalWrite(5, HIGH);     // 2 | 0.5   
  else digitalWrite(5, LOW); 

  if (time%2500 <= 1500) digitalWrite(6, HIGH);    // 1.5 | 1 
  else digitalWrite(6, LOW); 

  if (time%3000 <= 2000) digitalWrite(7, HIGH);    // 2 | 1  
  else digitalWrite(7, LOW); 
}
