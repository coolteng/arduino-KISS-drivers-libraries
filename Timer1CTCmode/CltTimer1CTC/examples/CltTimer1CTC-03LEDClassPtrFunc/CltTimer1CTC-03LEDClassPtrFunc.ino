// 開發簡易 Timer1 程式庫的階段性實作
// 作者：鄧崇林
class Timer
{
  public: Timer() {}
    void initTOP(unsigned int cltTOP) {
      cli(); 
      TCCR1A = 0;
      TCCR1B = 0; 
      TCCR1B |= (1<<WGM12);  // CTC mode; Clear Timer on Compare
      TCCR1B |= (1<<CS12) | (1<<CS10);  // Prescaler == 1024
      OCR1A = cltTOP;
      TCNT1=0;
    }
    void attachInterrupt(void (*isr)()) { 
      this->isrCallback = isr; // function pointer
      TIMSK1 |= _BV(OCIE1A);
    }
    // 必須宣告 static
    static void (*isrCallback)();
    //
  private:
    static void isrFunctionDumy() {}
};

//沒下一行會引發錯誤: undefined reference to `Timer::isrCallback'
void (*Timer::isrCallback)() = Timer::isrFunctionDumy;

void blinkLED(){
  digitalWrite(13, digitalRead(13) ^ 1);
}

Timer timer1;

ISR(TIMER1_COMPA_vect)
{
   timer1.isrCallback();
}

void setup( ) {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  timer1.initTOP(7812); // prescaler 為 1024
  timer1.attachInterrupt(blinkLED);
  interrupts();
}

void loop() {
  //... 
}
