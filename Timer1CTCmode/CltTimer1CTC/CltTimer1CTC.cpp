// 簡易 Timer1 程式庫，採CTC模式以ORC1A儲存TOP，引發ISR(TIMER1_COMPA_vect)
// 作者：鄧崇林
#ifndef CltTimer1CTC_cpp
#define CltTimer1CTC_cpp

#include "CltTimer1CTC.h"
//
CltTimer1CTC Timer1CTC;  // 簡易 Singleton Pattern

ISR(TIMER1_COMPA_vect)
{
   Timer1CTC.isrCallback();
}

void CltTimer1CTC::initTOP(long microSeconds) { //us 
  unsigned char prescaleBits;
  long valueTOP = (F_CPU / 1000000) * microSeconds; // 一秒=1000milliSeconds(毫秒, ms)=1000000microSeconds(微秒, us)
  if(valueTOP < TOPMAXIMUM)              prescaleBits = _BV(CS10);              // prescale = 1
  else if((valueTOP >>= 3) < TOPMAXIMUM) prescaleBits = _BV(CS11);              // prescale = 8
  else if((valueTOP >>= 3) < TOPMAXIMUM) prescaleBits = _BV(CS11) | _BV(CS10);  // prescale = 64
  else if((valueTOP >>= 2) < TOPMAXIMUM) prescaleBits = _BV(CS12);              // prescale = 256
  else if((valueTOP >>= 2) < TOPMAXIMUM) prescaleBits = _BV(CS12) | _BV(CS10);  // prescale = 1024
  else     valueTOP = TOPMAXIMUM - 1,    prescaleBits = _BV(CS12) | _BV(CS10);  // 最大上限
		
  cli();
  TCCR1A = 0;
  TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
  TCCR1B |= prescaleBits;
  TCCR1B |= _BV(WGM12);  // CTC mode; Clear Timer on Compare
  OCR1A = valueTOP -1; 
  TCNT1 = 0;
}

void CltTimer1CTC::attachInterrupt(void (*isr)()) {
  this->isrCallback = isr; // function pointer
  // Set Timer1 interrupt mode (Set interrupt on OCR1A compare match)
  TIMSK1 |= _BV(OCIE1A);
}

void CltTimer1CTC::detachInterrupt() {
  TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
  TIMSK1 &= ~_BV(OCIE1A); 
}
#endif
