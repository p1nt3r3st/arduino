// Аналоговые порты 0-5 умеют работать как цифровые(можно подключать цифровые датчики, реле, светодиоды)(а6 и а7 - нет)
// Аналоговые порты умеют измерять напряжение АЦП, к ним можно подключать аналоговые датчики

// arduino UNO, NANO - цифровые 3, 5, 6, 9, 10, 11 - также могут измерять ШИМ сигнал - широтно-импульсная модуляция

// любой порт Ардуино может работать как ВХОД, так и ВЫХОД. По умолчанию - как ВХОД


// pinMode(pin, mode); - перенастроить пин (номер пина, режим работы)
// pin - номер порта:
//       цифровые: 0-13 
//       аналоговые: 14-19 (А0-А5)
// mode: INPUT
//       OUTPUT(выдаёт 0 или 5 Вольт)
//       INPUT_PULLUP(Подключение внутреннего подтягивающего резистора 5 В)

// digitalWrite(pin, signal); - подать цифровой сигнал
// pin - пин, куда подаём сигнал
// signal - какой сигнал подаём:
//          LOW / 0 / false - 0 В
//          HIGH / 1 / true - 5 В

// digitalRead(pin); - прочитать цифровой сигнал
// pin - номер пина, с которого считываем


int bodSpeed = 9600;

void setup() {
  Serial.begin(bodSpeed);
  // pinMode(A2, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(13, OUTPUT);

  // digitalWrite(13, HIGH);
  // digitalWrite(12, HIGH);
  // digitalWrite(A5, LOW);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT);

}

void loop() {
  boolean button1 = !digitalRead(2);
  boolean button2 = !digitalRead(3);

  digitalWrite(4, button1);
  digitalWrite(5, button2);

  Serial.print("Button1: "); Serial.print(button1);
  Serial.print(",  Button2: "); Serial.println(button2);

}
