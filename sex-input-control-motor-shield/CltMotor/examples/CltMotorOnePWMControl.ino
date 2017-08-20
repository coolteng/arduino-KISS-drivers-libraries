// L298N 馬達驅動板不含數位邏輯閘(74HC00)
// 作者：鄧崇林
#include <CltMotor.h>

#define MotorA_I1      8  //定義 I1 接腳
#define MotorA_I2      9  //定義 I2 接腳
#define MotorA_PWM     5  //定義 PWMA (PWM調速) 接腳
CltMotor OneMotor(MotorA_I1, MotorA_I2, MotorA_PWM);
boolean flagForward = true;
void setup()
{
  delay(200);
}
void loop()
{ 
  for (int iPwm= 50; iPwm<256; iPwm+=5) {
    if (flagForward) {
      OneMotor.Forward(),  OneMotor.Speed(iPwm);
    } else {
      OneMotor.Reverse(),  OneMotor.Speed(iPwm);
    }
    delay(100);
  }
  flagForward = !flagForward;
  OneMotor.Stop();  delay(500);

} //Loop End
