// 開發簡易 Timer1 程式庫的階段性實作
// 作者：鄧崇林

const int initTOP = 7812;  // 大約 0.5 秒(prescaler = 1024)

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(13, digitalRead(13) ^ 1);
}
void setup( ) {
  pinMode(13, OUTPUT);
  cli();  // 禁止中斷
  TCCR1A = 0;
  TCCR1B = 0; 
  TCCR1B |= (1<<WGM12);  // CTC mode; Clear Timer on Compare
  TCCR1B |= (1<<CS10) | (1<<CS12);  // prescaler = 1024
  OCR1A = initTOP;
  TCNT1=0;  // counter 歸零 
  TIMSK1 |= (1 << OCIE1A);  // enable CTC for TIMER1_COMPA_vect
  interrupts();
}
void loop() {
  //...
}
