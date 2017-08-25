// 開發簡易 Timer1 程式庫的階段性實作
// 作者：鄧崇林
class Timer
{
  public: Timer() {}
    void initTOP(unsigned int cltTOP) {
      cli();  // 禁止中斷
      TCCR1A = 0;
      TCCR1B = 0; 
      TCCR1B |= (1<<WGM12);  // CTC mode; Clear Timer on Compare
      TCCR1B |= (1<<CS11) | (1<<CS10);  // Prescaler = 64
      OCR1A = cltTOP;
      TCNT1=0; 
      TIMSK1 |= (1 << OCIE1A);  // enable CTC for TIMER1_COMPA_vect
    }
};

void isrCallback(){
  digitalWrite(13, digitalRead(13) ^ 1);
}
//
ISR(TIMER1_COMPA_vect)
{
   isrCallback();
}
void setup( ) {
  pinMode(13, OUTPUT);
  Timer timer;
  timer.initTOP(24999); // prescaler = 64, 0.1 sec
  interrupts();
  digitalWrite(13, HIGH);
}

void loop() {
  //... 
}
