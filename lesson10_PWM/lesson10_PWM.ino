int bod_speed = 9600;
int pwm;

void setup() {
  Serial.begin(bod_speed);
}

void loop() {
  pwm = analogRead(0);
  pwm = map(pwm, 0, 1023, 0, 40);
  pwm = constrain(pwm, 0, 40);
  analogWrite(3, pwm);
}
