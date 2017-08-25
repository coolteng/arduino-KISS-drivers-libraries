// 開發簡易 Timer1 程式庫的階段性實作，目前程式庫業已完成，現進行驗收
// 作者：鄧崇林

#include <CltTimer1CTC.h>

void blinkLED(void)
{
  digitalWrite(13, digitalRead(13) ^ 1);
}
//
void setup(void)
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Timer1CTC.initTOP(1000000); // 一秒=10^6us, microSeconds
  Timer1CTC.attachInterrupt(blinkLED);
  interrupts();
}

void loop(void)
{
  //...
}
