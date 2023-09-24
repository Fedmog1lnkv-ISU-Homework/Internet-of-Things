const int ledPin = 9; // Пин, к которому подключен светодиод
const int fadeDelay = 10; // Задержка между шагами изменения яркости

void setup() {
  // Ничего особенного для настройки
}

void loop() {
  // Плавно увеличиваем яркость
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness); // Установка яркости светодиода
    delay(fadeDelay);
  }

  // Плавно уменьшаем яркость
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness); // Установка яркости светодиода
    delay(fadeDelay);
  }
}
