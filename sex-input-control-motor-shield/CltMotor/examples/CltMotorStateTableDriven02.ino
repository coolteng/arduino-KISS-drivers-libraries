// L298N 馬達驅動板不含數位邏輯閘(74HC00)，並以 MotorA 為車頭右邊輪以及 MotorB 為車頭左邊輪
// 作者：鄧崇林
#include <CltMotor.h>

typedef void (* ptrFunction) ();
typedef struct CarObject {
  ptrFunction manipulate; // 驅動器操縱方式
  int duration;           // 驅動器操縱時段
};

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define MotorA_I1      8  //定義 I1 接腳
#define MotorA_I2      9  //定義 I2 接腳
#define MotorB_I3     10  //定義 I3 接腳
#define MotorB_I4     11  //定義 I4 接腳
#define MotorA_PWM     5  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWM     6  //宣告 PWMB (PWM調速) 接腳
// 基本程式模組是以車頭為準，論左右前後方向
CltMotor RMotor(MotorA_I1, MotorA_I2, MotorA_PWM);
CltMotor LMotor(MotorB_I3, MotorB_I4, MotorB_PWM);

void advance()    // 前進
{
  RMotor.Forward(),  RMotor.Speed(200);
  LMotor.Forward(),  LMotor.Speed(200);  
}

void back()    //後退
{
  RMotor.Reverse(),  RMotor.Speed(200);
  LMotor.Reverse(),  LMotor.Speed(200);   
}

void roundR()    // 原地右旋轉
{
  RMotor.Reverse(),   RMotor.Speed(80); 
  LMotor.Forward(),   LMotor.Speed(80);
}

void roundL()    //原地左旋轉
{
  RMotor.Forward(),  RMotor.Speed(80);
  LMotor.Reverse(),  LMotor.Speed(80);
}
void turnR()    // 右前彎
{
  RMotor.Forward(),  RMotor.Speed(80); 
  LMotor.Forward(),  LMotor.Speed(200);
}

void turnL()    // 左前彎
{
  RMotor.Forward(),  RMotor.Speed(200); 
  LMotor.Forward(),  LMotor.Speed(80);
}

void stopRL()  //停車
{
  RMotor.Stop();
  LMotor.Stop();
}

void setup() {
  delay(200);
  /* 創建 Table Driven Array */
  CarObject Drives[] ={
     {advance, 1500},
     {back,    1500},
     {roundR,  3000},
     {roundL,  3000},
     {turnR,   700},
     {turnL,   700},
     {turnR,   1200},
     {turnL,   1200},
     {back,    1500},
     {advance, 1500},
     {roundL,  3000},
     {roundR,  3000},     
     {stopRL,   200}
  };
  //以下將依序執行所有陣列裡的驅動器作用...
  for (int i=0; i<ARRAY_SIZE(Drives); i++) {
    Drives[i].manipulate();
    delay(Drives[i].duration);
  }
}

void loop() {
  // 
}
