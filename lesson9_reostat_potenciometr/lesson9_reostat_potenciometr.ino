// analogRead(pin(номер пина без буквы А)); - возвращает значение 0..1023 в зависимости от напряжения на пине от 0 до опорного напряжения(грубо 5 В)
// mao(val, nim, max, new_min, new_max);
// val - входная величина
// min, max - минимальное и максимальное значение на входе в map
// new_min, new_max - новые мин макс

#define potent_pin 0

int bod_speed = 9600;
float old_min = 1;
float old_max = 1023;
float new_min = 0;
float new_max = 5;
float val;

void setup() {
  Serial.begin(bod_speed);
  pinMode(2, OUTPUT);
}

void loop() {
  val = analogRead(potent_pin);
  // val = map(val, old_min, old_max, new_min, new_max);
  // constrain(val, new_min, new_max);
  val = ((val - old_min) / (old_max - old_min)) * new_max;
  if (val > 3.0){
    digitalWrite(2, 1);
  }
  else{
    digitalWrite(2, 0);
  }
  Serial.println(val);
  delay(30);
}
