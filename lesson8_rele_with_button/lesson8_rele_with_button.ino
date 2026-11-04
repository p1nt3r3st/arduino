int speedBod = 9600;

void setup() {
  Serial.begin(speedBod);
  pinMode(A0, INPUT_PULLUP);
  pinMode(7, OUTPUT);
}

void loop() {
  bool button1 = !digitalRead(A0);
  digitalWrite(7, button1);

  Serial.print("button1 ");
  Serial.println(button1);

  delay(100);
}