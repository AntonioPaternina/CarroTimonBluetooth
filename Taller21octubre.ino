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
  // si el timón está girado hacia la izquierda
  if (input <= 127) {
    return 255; // maxima velocidad
  }
  else {
    // si el timón está girado hacia la derecha es necesario retrasar PWMA
    // si input == 128 entonces se disminuye a 253 el PWMA, si el input == 255 se disminuye a 0 el PWMA
    return 255 - ((input - 127.0) / 128) * 255;
  }
}

int getPWMBfromByte(int input) {
  // si el timón está girado hacia la derecha
  if (input >= 127) {
    return 255; // maxima velocidad
  }
  else {
    // si el timón está girado hacia la izquierda es necesario retrasar PWMB
    // si input == 126 entonces se disminuye a 253 el PWMB, si el input == 255 se disminuye a 0 el PWMB
    return 255 - ((127.0 - input) / 127) * 255;
  }
}

