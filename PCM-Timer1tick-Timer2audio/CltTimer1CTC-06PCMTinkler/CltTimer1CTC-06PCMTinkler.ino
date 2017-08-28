// 改寫>https://playground.arduino.cc/Code/PCMAudio
// 作者：鄧崇林

#include <CltTimer1CTC.h>
#include "CltTimer1CTC-06PCMTinklerData.h"
#include "CltTimer1CTC-06PCMTimer2Class.h"

int ledPin = 13;
int speakerPin = 3; //11; // Can be either 3 or 11, two PWM outputs connected to Timer 2
int triggerPin = A0;
volatile uint16_t sample;
Timer2 Timer2PWM;

void stopPlayAudio()
{
    Timer1CTC.detachInterrupt();
    Timer2PWM.noClkSource();
    digitalWrite(speakerPin, LOW);
}

//ISR(TIMER1_COMPA_vect) {
void tickSoundISR(void) {
  if (sample >= sizeof(sounddataPGM)) {
    stopPlayAudio();
  } else {
    Timer2PWM.putSample2Sound(speakerPin, sounddataPGM+sample);
    ++sample;
  }
}

void startPlayAudio() {
  // Set up Timer 2 to do pulse width modulation on the speaker pin.
  sample = 0;
  Timer2PWM.initMode3(speakerPin);

  // Set up Timer 1 to send a sample every interrupt.
  // sampling rate = 1/125us = 1/0.000125s = 8000hz
  Timer1CTC.initTOP(125); // us, microSeconds(微秒)，取樣率=8KHz
  Timer1CTC.attachInterrupt(tickSoundISR);
  interrupts();
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(speakerPin, OUTPUT);
  //pinMode(triggerPin, INPUT_PULLUP); // 用於按鍵式開關之類的應用場合①
}
  
void loop()
{
  //if(digitalRead(triggerPin) == LOW){ // 用於按鍵式開關之類的應用場合①
  // 在麥克風模組周遭近距離拍手，則 Arduino 即刻播放音效
  if(analogRead(triggerPin) > 400) {  // 外接麥克風模組的類比信號輸出腳位
    startPlayAudio();
    delay(3000);  //等待播放約三秒，在此期間拍手，才不會從頭播放而中斷原音效播放節奏
  }
}

