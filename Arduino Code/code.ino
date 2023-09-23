int buzzer = 5; // Pino do buzzer
int melody = 196; // Valor da melodia
int verde = 4;     // Pino para a cor verde
int azul = 3;  // Pino para a cor amarela
int vermelho = 2; // Pino para a cor vermelha
int value = 0; // valor da porta A0

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(vermelho, OUTPUT);
}

void loop() {
  value = analogRead(A0);
  Serial.println(value);
  
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

void led(int cor) {
  switch (cor) {
    case 1: // Verde
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, LOW);
      break;
    case 2: // Amarelo
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, HIGH);
      break;
    case 3: // Vermelho
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, HIGH);
      break;
    default:
      // Caso seja um número inválido, desligar todas as cores
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      digitalWrite(vermelho, LOW);
      break;
  }
}
