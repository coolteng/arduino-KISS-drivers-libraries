#ifndef CltMotor_h
#define CltMotor_h

#include <Arduino.h>
#if defined (__AVR__)
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif

class CltMotor
{ 

  private:
    uint8_t pin1; uint8_t pin2; uint8_t pPWM;

  public:
    CltMotor(uint8_t pin1, uint8_t pin2, uint8_t pPWM);
    void Forward(void);
    void Reverse(void);
    void Speed(int speed);
    void Stop(void);
};

#endif
