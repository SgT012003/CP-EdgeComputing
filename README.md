# CP2 EdgeComputing ESPR
|  Group Members  |
|:--------------:|
| Diogo          | 
| João Pedro     |
| Victor Didoff  | 
| Vinicius Silva |

## About this project

This project was developed with the aim of solving the wine manufacturing problems of the company "Vinheria Agnello".

* Focous 1 : light during the fermentation process can spoil the wine.
* Focous 2 : the humidity can degradete the bottle sticker.
* Focous 3 : Temperature can make more easy to spread bacterias and spoil the wine.

The project can be found on the [Tinkercad page](https://www.tinkercad.com/things/1XuuWg6gJUA-cp2-edge/editel?sharecode=jZfPdpYhqcpGB45mb0AorN83rniaXjn3l-Et6Z3Osr8)

## Scheme View
![photo from Tinkercad](https://imgur.com/gXIMkyM.png)

If you compare the DataSheet's components u will repair that was missing a DHT11, but on tinkercad doens't have it so we replace it as a potenciometer.

## Eletrical View
![photo from Tinkercad of the eletric view](https://imgur.com/kI7gpZ9.png)

## Video




## Code
```cpp
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
```

## Advice's

* The showed code is for a [3x] single LED [ Light Emissor Diode ]!
* The LDR resistence may vary piece by piece verify the datasheet for your own!
* The DHT11 may vary piece by piece verify the datasheet for your own!
* The Sound of Piezo may vary piece by piece verify the datasheet for your own!


## DataSheet's

|  Components  |
|:--------------|
| 4x [Resistor 220Ω](https://www.digchip.com/datasheets/parts/datasheet/1838/CFR-25JB-220R.php) |
| 1x [Resistor 4.7kΩ](https://www.digchip.com/datasheets/parts/datasheet/1838/CFR-25JB-220R.php) |
| 1x [Variable Resistor (Potenciometer 10K - B)](https://www.digchip.com/datasheets/parts/datasheet/1838/CFR-25JB-220R.php) |
| 1x [DHT11](https://www.alldatasheet.com/view.jsp?Searchword=Dht11%20datasheet&gad_source=1&gclid=CjwKCAjw7oeqBhBwEiwALyHLM-jJbEI_BVINUC5lWzTEIHCr9oMhbcwniKUp1TxM35JRujqR1ASLQhoCNzwQAvD_BwE) |
| 1x [LCD 16x2 (RT162-7)](https://www.usinainfo.com.br/display-arduino/display-lcd-16x2-com-fundo-verde-2954.html) |
| 1x [LED RGB(Light Emissor Diode)](https://components101.com/diodes/rgb-led-pinout-configuration-circuit-datasheet) |
| 1x [Buzzer](https://category.alldatasheet.com/index.jsp?sSearchword=Buzzer%20datasheet&gclid=CjwKCAjwgsqoBhBNEiwAwe5w0-AXSM-Jwz2fJnvWkg2uLc6ktvxCOBWuCnBB7DBtk4p8hWObUk4owxoCM5oQAvD_BwE)  | 
| 1x [Arduino R3](https://datasheet.octopart.com/A000066-Arduino-datasheet-170320520.pdf?_gl=1*22gmcz*_ga*ODU5ODM2OTE1LjE2OTU3NjI2NDM.*_ga_SNYD338KXX*MTY5NTc2MjY0NC4xLjAuMTY5NTc2MjY1My4wLjAuMA..) | 
| 1x [LDR(Light Dependent Resistor)](https://components101.com/sites/default/files/component_datasheet/LDR%20Datasheet.pdf) |
