// L298N Motor shield library
// copyright @鄧崇林, 2017
// this code is public domain, enjoy!

#include "CltMotor.h"

// ---------------------------------------------------------------------------
// CltMotor constructor
// ---------------------------------------------------------------------------
CltMotor::CltMotor(uint8_t pin1, uint8_t pin2, uint8_t pPWM) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pPWM = pPWM;
  pinMode(this->pin1, OUTPUT);
  pinMode(this->pin2, OUTPUT);
  pinMode(this->pPWM, OUTPUT);
}

void CltMotor::Forward(void) {
  digitalWrite(this->pin1, HIGH); 
  digitalWrite(this->pin2, LOW); 
}

void CltMotor::Reverse(void) {
  digitalWrite(this->pin1, LOW); 
  digitalWrite(this->pin2, HIGH); 
}

void CltMotor::Speed(int speed) {
   analogWrite(this->pPWM, speed);
}

void CltMotor::Stop(void) {
  digitalWrite(this->pin1, HIGH);
  digitalWrite(this->pin2, HIGH); 
}
