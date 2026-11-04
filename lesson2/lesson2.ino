// Урок 2
// 2.1 Вывод данных в порт
// Serial - объект библиотеки Serial для работы с последовательным портом(COM портом)
// Serial.begin(<Скорость>); - открыть порт, скорость измеряется в бодах
// Serial.print(); - Вывод в порт
// Serial.println(); - Вывести с переводом на новую строку
// Serial.println(number, 2); - Вывести с двумя знаками после запятой
// Serial.println(n, DEC/HEX/OCT/BIN); - Вывести в 10/16/8/2 СС
// String word = "word"; - строковый тип данных

// 2.2 Ввод данных
// Данные с компьютера попадают в буфер размером 64 байта и ждут обработки
// Serial.available(); - проверить буфер на наличие входящих данных, возвращает кол-во байт, которые лежат в буфере
// Serial.read(); - прочитать входящие данные в симфольном формате ASCII
// Serial.read() - '0'; - прочитать данные в целочисленном формате, по одной цифре
// Serial.parseInt(); - Прочитать данные в целочисленном формате, складывает все цифры в число
// Serial.flush(); - очистить буфер порта


void intPrintln(int integer){
  Serial.println(integer);
}

void stringPrintln(String line){
  Serial.println(line);
}

int standardSpeed = 9600;

void setup() {
  Serial.begin(standardSpeed);
  Serial.println("HELLO, WORLD!");

  // float pi = 3.14159;
  // intPrintln(pi);
  // Serial.println(pi);
  // Serial.println(pi, 4); // Вывести 3 знака после запятой
  // stringPrintln("КУСЬ");

}

void loop() {
  if (Serial.available() > 0){
    int in_data = Serial.parseInt();
    Serial.print("Входящие данные: ");
    Serial.println(in_data);
  }
}
