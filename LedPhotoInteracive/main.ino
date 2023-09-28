#define led_pin 8
#define sensor_pin A0

char command = ' ';
bool shouldReadSensor = false;
bool alarmMode = false;
bool lightControlMode = false;
bool send_one_value = false;

int lightThreshold = 850; // Пороговое значение освещенности
unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
    Serial.begin(9600);
    pinMode(led_pin, OUTPUT);
}

void loop()
{
    long current_time = millis();

    // Обработка команд
    if (Serial.available() > 0)
    {
        command = Serial.read();
        switch (command)
        {
        case 'p': // Поток значений
            shouldReadSensor = true;
            break;
        case 's': // Отправка одиночного значения
            shouldReadSensor = false;
            send_one_value = true;
            break;
        case 'a': // Сигнализация
            alarmMode = true;
            lightControlMode = false;
            break;
        case 'l': // вкл/выкл от в зависимости от освещения
            alarmMode = false;
            lightControlMode = true;
            break;
        case 'r': // reset
            alarmMode = false;
            lightControlMode = false;
            shouldReadSensor = false;
            digitalWrite(led_pin, LOW);
            break;
        case 'n': // Включение
            alarmMode = false;
            lightControlMode = false;
            digitalWrite(led_pin, HIGH);
            break;
        case 'f': // Выключение
            alarmMode = false;
            lightControlMode = false;
            digitalWrite(led_pin, LOW);
            break;
        }
    }

    if (alarmMode)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            digitalWrite(led_pin, !digitalRead(led_pin));
        }
    }
    else if (lightControlMode)
    {
        int lightValue = analogRead(sensor_pin);
        if (lightValue > lightThreshold)
        {
            digitalWrite(led_pin, LOW);
        }
        else
        {
            digitalWrite(led_pin, HIGH);
        }
    }

    if (shouldReadSensor)
    {
        int val = analogRead(sensor_pin);
        Serial.print("Sensor value: ");
        Serial.println(val);
    }

    // Отправка одиночного значения при необходимости
    if (send_one_value)
    {
        int val = analogRead(sensor_pin);
        Serial.print("Sensor value: ");
        Serial.println(val);
        send_one_value = false;
    }
}
