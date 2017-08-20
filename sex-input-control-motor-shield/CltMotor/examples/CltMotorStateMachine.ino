// L298N 馬達驅動板不含數位邏輯閘(74HC00)，並以 MotorA 為車頭右邊輪以及 MotorB 為車頭左邊輪
// 作者：鄧崇林
#include <CltMotor.h>

#define MotorA_I1      8  //定義 I1 接腳
#define MotorA_I2      9  //定義 I2 接腳
#define MotorB_I3     10  //定義 I3 接腳
#define MotorB_I4     11  //定義 I4 接腳
#define MotorA_PWM     5  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWM     6  //宣告 PWMB (PWM調速) 接腳

// 基本程式模組是以車頭為準，論左右前後方向
CltMotor RMotor(MotorA_I1, MotorA_I2, MotorA_PWM);
CltMotor LMotor(MotorB_I3, MotorB_I4, MotorB_PWM);

typedef void *(*StateFunc)();

// States
void *advance();
void *back();
void *turnR();
void *turnL();
void *roundR();
void *roundL();
void *stopRL();

//  集成程式模組是以車手為準，論左右前後駕駛方向

void *advance()    // 前進
{
  RMotor.Forward(),  RMotor.Speed(200);
  LMotor.Forward(),  LMotor.Speed(200);  
  delay(1000);
  return back; // next state
}

void *back()    //後退
{
  RMotor.Reverse(),  RMotor.Speed(200);
  LMotor.Reverse(),  LMotor.Speed(200);
  delay(1000);
  return roundR; // next state     
}


void *roundR()    // 原地右旋轉
{
  RMotor.Reverse(),   RMotor.Speed(80); 
  LMotor.Forward(),   LMotor.Speed(80);
  delay(3000);
  return roundL; // next state
}

void *roundL()    //原地左旋轉
{
  RMotor.Forward(),  RMotor.Speed(80);
  LMotor.Reverse(),  LMotor.Speed(80);
  delay(3000);
  return turnR; // next state
}
void *turnR()    // 右前彎
{
  RMotor.Forward(),  RMotor.Speed(80); 
  LMotor.Forward(),  LMotor.Speed(200);
  delay(500);
  return turnL; // next state
}

void *turnL()    // 左前彎
{
  RMotor.Forward(),  RMotor.Speed(200); 
  LMotor.Forward(),  LMotor.Speed(80);
  delay(500);
  return stopRL; // next state
}

void *stopRL()  //停車
{
  RMotor.Stop();
  LMotor.Stop();
  delay(1000);
  return advance; // next state
}
//
void setup()
{
  delay(200);
}

void loop()
{
  StateFunc statefunc = advance;
  while(1) {
    statefunc = (StateFunc)(*statefunc)();
  }
} //Loop End
