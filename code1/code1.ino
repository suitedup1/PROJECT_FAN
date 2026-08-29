/*
int pir = 13;
int led = 16;
volatile bool motion = false;
volatile unsigned long long t;
void ICACHE_RAM_ATTR on_motion()
{
  motion = true;
  t = millis();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("LOADING");
  delay(60000);
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  attachInterrupt(digitalPinToInterrupt(pir), on_motion, RISING);
}   

void loop() {
  // put your main code here, to run repeatedly:
  if (motion == true)
  {
    digitalWrite(led, HIGH);
    Serial.println("led on");
  }
  if (motion == true && millis() - t > 2000)
  {
    digitalWrite(led, LOW);
    motion = false;
  }
}
*/
