// 作者：鄧崇林
#ifndef CltTimer2PWM_h
#define CltTimer2PWM_h

#include "Arduino.h"

class CltTimer2PWM
{
  public:
    void initMode3(int pwmPin);
    void putPgm2Sound(int soundPin, const unsigned char *cltPointer);
    // overload method
    void putPgm2Sound(int soundPin, const unsigned char (*cltPointer)[256]);
    void putByte2Sound(int soundPin, byte sampleByte);
    void noClkSource();
};

// 沒有下一行會引發編譯錯誤: 'Timer2PWM' was not declared in this scope
extern CltTimer2PWM Timer2PWM;

#endif
