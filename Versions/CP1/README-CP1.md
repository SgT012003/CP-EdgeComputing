# CP1 EdgeComputing ESPR
|  Group Members  |
|:--------------:|
| Diogo          | 
| João Pedro     |
| Victor Didoff  | 
| Victor Marques | 
| Vinicius Silva |

## About this project

This project was developed with the aim of solving the wine manufacturing problems of the company "Vinheria Agnello".

* Focus : light during the fermentation process can spoil the wine.

The project can be found on the [Tinkercad page](https://www.tinkercad.com/things/8I0yLO2iu7y-sizzling-jaban-inari/editel?sharecode=OmVJ87-UvctAihjdQgwiKVrBAiRXO5C5j4NxCy4afRk)

## Scheme View
![photo from Tinkercad](https://i.imgur.com/9cxrQ8x.png)

## Eletrical View
![photo from Tinkercad of the eletric view](https://i.imgur.com/aT5Xrrq.png)

## Video

https://github.com/SgT012003/CP-EdgeComputing/assets/82065998/99ea7eff-a1a5-49c8-b0da-e73d6b1e351d



## Code

```cpp
/* declare "buzzer" variables */
int buzzer = 5;
int melody = 196;

/* declare "led" variables */
int verde = 4;
int azul = 3;
int vermelho = 2;

/* declare "ldr" variable */
int value = 0;

void setup() {
/* declare serial ini */
  Serial.begin(9600);

/* Setup Input */
  pinMode(A0, INPUT);

/* Setup Output's */
  pinMode(buzzer, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(vermelho, OUTPUT);
}

void loop() {
/* Recive data from A0 and send it to serial output */
  value = analogRead(A0);
  Serial.println(value);

/* Process case-a-case */
  if (value < 600) {
    caso(1);
  }
  else if (value < 800) {
    caso(2);
  }
  else if (value > 800) {
    caso(3);
  }
}

/* declare methode "caso" that define case per case [ default is not used ] */
void caso(int nivel) {
  switch (nivel) {
  	case 1:
    	led(1);
    	break;
    case 2:
    	led(2);
    	tone(buzzer, melody, 3000);
    	delay(3000);
    	noTone(buzzer);
    	delay(2000);
    	break;
    case 3:
    	led(3);
    	tone(buzzer, melody, 3000);
    	delay(3000);
    	noTone(buzzer);
    	break;
    default:
    	led(-1);
    	break;
  }
}

/* declare methode "led" that define led color output [ default is not used ] */
void led(int cor) {
  switch (cor) {
    case 1: // Green
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, LOW);
      break;
    case 2: // Yellow
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, HIGH);
      break;
    case 3: // Red
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, HIGH);
      break;
    default: // all output's off [ turn off | not used ]
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, LOW);
      break;
  }
}
```

## Notes

On arduino is mostly used the `#define [variable name] [variable value] ` but i decided to use int as default.

Can be used mult declaration's on the same type as example below:

```diff
-/* declare "buzzer" variables */
-int buzzer = 5;
-int melody = 196;

-/* declare "led" variables */
-int verde = 4;
-int azul = 3;
-int vermelho = 2;

-/* declare "ldr" variable */
-int value = 0;

+#define Analog A0
+int buzzer = 5, melody = 196, verde = 4, azul = 3, vermelho = 2, value = 0;
```

## Advice's

* The showed code is for a rgb LED [ Light Emissor Diode ], for the single led operations see the folders above!

* The LDR resistence may vary piece by piece verify the datasheet for your own!

## DataSheet's

|  Components  |
|:--------------|
| 3x [Resistor 220Ω](https://www.digchip.com/datasheets/parts/datasheet/1838/CFR-25JB-220R.php) |
| 1x [Resistor 4.7kΩ]() |
| 1x [LED RGB(Light Emissor Diode)](https://components101.com/diodes/rgb-led-pinout-configuration-circuit-datasheet) |
| 1x [Buzzer](https://category.alldatasheet.com/index.jsp?sSearchword=Buzzer%20datasheet&gclid=CjwKCAjwgsqoBhBNEiwAwe5w0-AXSM-Jwz2fJnvWkg2uLc6ktvxCOBWuCnBB7DBtk4p8hWObUk4owxoCM5oQAvD_BwE)  | 
| 1x [Arduino R3](https://datasheet.octopart.com/A000066-Arduino-datasheet-170320520.pdf?_gl=1*22gmcz*_ga*ODU5ODM2OTE1LjE2OTU3NjI2NDM.*_ga_SNYD338KXX*MTY5NTc2MjY0NC4xLjAuMTY5NTc2MjY1My4wLjAuMA..) | 
| 1x [LDR(Light Dependent Resistor)](https://components101.com/sites/default/files/component_datasheet/LDR%20Datasheet.pdf) |

| Optional |
|:----------|
| 1x [Diode](https://category.alldatasheet.com/index.jsp?sSearchword=Diode%20datasheet&gclid=CjwKCAjwgsqoBhBNEiwAwe5w0xUBcM1RhuJFK4lxRC_CcuzRB_5t4q-abkr-WCbo8pIZ7QTzFb2mORoCHvQQAvD_BwE) |
| 1x [Diode Zener 5.1v](https://www.arrow.com/en/products/bzt52c5v1-7-f/diodes-incorporated?region=europe&utm_source=FindChips&utm_medium=Aggregator&utm_term=InvListing-Product&utm_content=Arrow-Region&utm_campaign=FindChips-2023)|
| 3x [LED's Colored](https://category.alldatasheet.com/index.jsp?sSearchword=Led%20datasheet&gclid=CjwKCAjwgsqoBhBNEiwAwe5w03M2hviuDyh2d-DJcZ34nNcV3Zxo8u1WtoYNIC6t8M4QPOpv6Jq09RoCRDEQAvD_BwE) |

## Licence

* This Project has "The Unlicense" protection as a licence. [lincence link](https://github.com/SgT012003/CP-EdgeComputing/blob/main/LICENSE)
