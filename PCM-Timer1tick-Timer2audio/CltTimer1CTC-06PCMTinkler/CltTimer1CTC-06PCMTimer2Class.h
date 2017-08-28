class Timer2
{
  public: Timer2() {}
    void initMode3(int pwmPin) {
      ASSR &= ~(_BV(EXCLK) | _BV(AS2));
      TCCR2A |= _BV(WGM21) | _BV(WGM20);
      TCCR2B &= ~_BV(WGM22); //set Timer2 to fast PWM mode
	    // Boyh OC2A(pin 11) and OC2B(pin 3) in non-inverting mode
      if(pwmPin==11){
        TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0); // set COM2A CS bits to 10 - Non inverted PWM
        TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
        //Setting the CS bits to 001 sets No prescaler
        TCCR2B = (TCCR2B & ~(_BV(CS22) | _BV(CS21)) | _BV(CS20));
      } else {
        TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
        TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
        TCCR2B = (TCCR2B & ~(_BV(CS22) | _BV(CS21))) | _BV(CS20);
      }
    }
	  void putSample2Sound(int soundPin, const unsigned char *cltPointer) {
      if(soundPin==11)
        OCR2A = pgm_read_byte(cltPointer); 
      else 
        OCR2B = pgm_read_byte(cltPointer); 
    }
    void noClkSource() {
      // Disable the PWM timer.(001)->(000)
      TCCR2B &= ~_BV(CS20);
    }
};
