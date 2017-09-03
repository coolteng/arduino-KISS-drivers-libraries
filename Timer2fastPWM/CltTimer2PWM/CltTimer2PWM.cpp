// 作者：鄧崇林
#ifndef CltTimer2PWM_cpp
#define CltTimer2PWM_cpp

#include "CltTimer2PWM.h"
//
CltTimer2PWM Timer2PWM;             // 簡易 Singleton Pattern

    void CltTimer2PWM::initMode3(int pwmPin) {
      ASSR &= ~(_BV(EXCLK) | _BV(AS2));
      TCCR2A |= _BV(WGM21) | _BV(WGM20);
      TCCR2B &= ~_BV(WGM22); //set Timer2 to fast PWM mode (doubles PWM frequency)
    
      // 使用 timer2 計時器，該計時器是運用 pin 11(OC2A) 與 pin 3(OC2B) 做 PWM 模擬發出聲音頻率
      if(pwmPin==11){
        // Do non-inverting PWM on pin OC2A
        // On the Arduino UNO this is pin 11.
        TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0); // set COM2A CS bits to 10 - Non inverted PWM
        TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
        // Clock Select Bit set prescaler to (CS22:0=001)No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS22) | _BV(CS21)) | _BV(CS20)); 
        } else {
        // Do non-inverting PWM on pin OC2B
        // On the Arduino UNO this is pin 3.
        TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
        TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
        // No prescaler
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
      }
    }
	
    void CltTimer2PWM::putPgm2Sound(int soundPin, const unsigned char *cltPointer) {
      if(soundPin==11)
        OCR2A = pgm_read_byte(cltPointer) ; // duty cycle of fast PWM
      else 
        OCR2B = pgm_read_byte(cltPointer) ; 
    }
    // overload putPgm2Sound mathod
    void CltTimer2PWM::putPgm2Sound(int soundPin, const unsigned char (*cltPointer)[256]) {
      if(soundPin==11)
        OCR2A = pgm_read_byte(cltPointer) ; // duty cycle of fast PWM
      else
        OCR2B = pgm_read_byte(cltPointer) ; 
    }
    void CltTimer2PWM::putByte2Sound(int soundPin, byte sampleByte) {
      if(soundPin==11)
        OCR2A = sampleByte; // duty cycle of fast PWM
      else 
        OCR2B = sampleByte; 
    }

	  void CltTimer2PWM::noClkSource() {
      // Disable the PWM timer.(001)->(000)
      TCCR2B &= ~_BV(CS20);
    }
#endif
