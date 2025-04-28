int cnt=0;
 
void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(LED_BUILTIN,OUTPUT);

  int cnt=0;

}
 
void loop() {

  cnt=cnt+1;

  Serial.println(cnt);

  if (cnt%10 == 0){

    digitalWrite(LED_BUILTIN,HIGH);

  }

  else

  {

    digitalWrite(LED_BUILTIN,LOW);

  }

  delay(500);

}
 
