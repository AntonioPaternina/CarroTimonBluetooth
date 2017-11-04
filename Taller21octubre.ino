#include "Arduino.h"
// PINES DE MOTOR SHIELD
int PIN_PWM_A = 3;
int PIN_PWM_B = 11;
int PIN_DIR_A = 12;
int PIN_DIR_B = 13;
int PIN_BRAKE_A = 9;
int PIN_BRAKE_B = 8;

// CONSTANTES PARA VELOCIDAD DEL CARRO
int PWM_AVANCE = 255;
int PWM_GIRO = 255;

void setup() {
  // ESTABLECER PINES DE SALIDA (AL MOTOR)
  pinMode(PIN_PWM_A, OUTPUT);
  pinMode(PIN_PWM_B, OUTPUT);
  pinMode(PIN_DIR_A, OUTPUT);
  pinMode(PIN_DIR_B, OUTPUT);
  pinMode(PIN_BRAKE_A, OUTPUT);
  pinMode(PIN_BRAKE_B, OUTPUT);

  Serial.begin(9600);

  digitalWrite(PIN_DIR_A, HIGH);
  digitalWrite(PIN_DIR_B, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    int input = Serial.read();
    digitalWrite(PIN_PWM_A, getPWMAfromByte(input));
    digitalWrite(PIN_PWM_B, getPWMBfromByte(input));
  }
}

int getPWMAfromByte(int input) {
  if (input == 255) {
    return 0;
  }
  if (input == 127) {
    return 255;
  } else if (input < 127) {
    return 255;
  } else {
    return (((input - 127) / 127) * 255);
  }
}

int getPWMBfromByte(int input) {
  if (input == 255) {
    return 0;
  }
   if (input == 127) {
    return 255;
  } else if (input < 127) {
    return ((-(input - 127) / 127) * 255);
  } else {
    return 255;
  }
}

