#include <LiquidCrystal.h>
#include <DHT.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int leds[3] = { 8, 7, 6 };

#define ldr A0

#define buzzer 9
#define melody 196

DHT Dht(10, DHT11);

float temperature[5] = { 12, 12, 12, 12, 12 };
float humidity[5] = { 70, 70, 70, 70, 70 };
int light[5] = { 500, 500, 500, 500, 500 };

float results[3] = { 0, 0, 0 };

unsigned long start;
unsigned long sensors;
unsigned long current;
unsigned long cooldown;

int lcdc = 0;
int sensorsc = 0;

float play;
bool pass = false;
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(ldr, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Apresentando:");
  lcd.setCursor(0, 1);
  lcd.print("Media dos Dados");

  start = millis();
  sensors = millis();
}

void loop() {
  current = millis() - start;
  cooldown = millis() - sensors;

  for (int w = 0; w < 3; w++) {
    results[w] = average(w);
    switch (w) {
      case 0:
        if (results[w] > 15) {
          tone(buzzer, melody, 3000);
          play = 3000;
          if (millis() - start >= play) {
            noTone(buzzer);
            play = 0;
          }
        } else if (results[w] < 10) {
          tone(buzzer, melody, 1000);
        } else {
          noTone(buzzer);
        }
        break;
      case 1:
        if (results[w] > 80) {
          tone(buzzer, melody, 3000);
          play = 3000;
          if (millis() - start >= play) {
            noTone(buzzer);
            play = 0;
          }
        } else if (results[w] < 60) {
          tone(buzzer, melody, 1000);
        } else {
          noTone(buzzer);
        }
        break;
      case 2:
        if (results[w] > 800) {
          ledcolor(2);
        } else if (results[w] > 730) {
          ledcolor(1);
        } else {
          ledcolor(0);
        }
    }
  }

  if (cooldown >= 2000) {
    temperature[sensorsc] = Dht.readTemperature();
    humidity[sensorsc] = Dht.readHumidity();
    light[sensorsc] = analogRead(ldr);
    sensorsc++;
    if (sensorsc > 5) { sensorsc = 0; }
    sensors = millis();
  }

  if (current >= 5000) {
    lcdcontroller(lcdc);
    lcdc++;
    if (lcdc > 2) { lcdc = 0; }
    start = millis();
  }
}

void ledcolor(int color) {
  switch (color) {
    case 0:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      break;
    case 1:
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], LOW);
      break;
    case 2:
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], HIGH);
      break;
    default:
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      break;
  }
}

void lcdcontroller(int type) {

  int value = average(type);

  switch (type) {
    case 0:
      digitalWrite(leds[0], HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      if (value > 15) {
        lcd.print("Temp. Alta");
      } else if (value < 10) {
        lcd.print("Temp. Baixa");
      } else {
        lcd.print("Temperatura OK");
      }
      lcd.setCursor(0, 1);
      lcd.print("Temp. = ");
      lcd.print(value);
      lcd.print("C");
      break;
    case 1:
      digitalWrite(leds[1], HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      if (value > 80) {
        lcd.print("Umidade Alta");
      } else if (value < 60) {
        lcd.print("Umidade Baixa");
      } else {
        lcd.print("Umidade OK");
      }
      lcd.setCursor(0, 1);
      lcd.print("Umidade = ");
      lcd.print(value);
      lcd.print("%");
      break;
    case 2:
      digitalWrite(leds[2], HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Luminozidade");
      lcd.setCursor(0, 1);
      if (value > 800) {
        lcd.print("Alta");
      } else if (value > 730) {
        lcd.print("Fora do Ideal");
      } else {
        lcd.print("Ideal");
      }
      break;
  }
}

float average(int type) {
  int i = 0;
  switch (type) {
    case 0:
      for (int j = 0; j < 5; j++) {
        i += temperature[j];
      }
      return i / 5;
      break;
    case 1:
      for (int k = 0; k < 5; k++) {
        i += humidity[k];
      }
      return i / 5;
      break;
    case 2:
      for (int x = 0; x < 5; x++) {
        i += light[x];
      }
      return i / 5;
      break;
  }
}