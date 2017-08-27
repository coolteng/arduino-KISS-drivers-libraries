// 簡易 Timer1 程式庫，採CTC模式以ORC1A儲存TOP，引發ISR(TIMER1_COMPA_vect)
// 作者：鄧崇林
#ifndef CltTimer1CTC_h
#define CltTimer1CTC_h

//#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define TOPMAXIMUM 65536   

class CltTimer1CTC
{
  public:
    void initTOP(long microSeconds);
    void attachInterrupt(void (*isr)());
    void detachInterrupt();
    //static 不需要
    void (*isrCallback)();
};

// 沒有下一行會引發編譯錯誤: 'Timer1CTC' was not declared in this scope
extern CltTimer1CTC Timer1CTC;

#endif
