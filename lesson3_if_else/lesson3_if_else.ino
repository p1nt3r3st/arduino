int bodSpeed = 9600;
int value;

void setup() {
  Serial.begin(bodSpeed);
}

void loop() {
  if (Serial.available()){
    value = Serial.parseInt();
    // if (value == 1 || value == 5){
    //   Serial.println("Вы ввели 1 или 5");
    // } else {
    //   Serial.println("Вы ввели другое число");
    // }
    switch (value){
      case 1: Serial.println("Число 1");
      break;
      case 2: Serial.println("Число 2");
      break;
    }
  }
}
