
#include <SCoop.h>

#define n2 2    //控制点击数字2的引脚，定义为板子上的D2引脚
#define n3 3    //控制点击数字3的引脚，定义为板子上的D3引脚
#define n4 4    //控制点击数字4的引脚，定义为板子上的D4引脚
#define n5 5    //控制点击数字5的引脚，定义为板子上的D5引脚
#define n6 6    //控制点击数字6的引脚，定义为板子上的D6引脚
#define n7 7    //控制点击数字7的引脚，定义为板子上的D7引脚
#define n8 8    //控制点击数字8的引脚，定义为板子上的D8引脚
#define n9 9    //控制点击数字9的引脚，定义为板子上的D9引脚
#define n0 10   //控制点击数字0的引脚，定义为板子上的D10引脚
#define n1 11   //控制点击数字2的引脚，定义为板子上的D11引脚
#define ok 12   //控制点击输入密码完成后的确定的引脚，定义为板子上的D12引脚

#define key   A0


#define touchTime   30    //点击屏的时间

#define delayTime   30    //两次点击的间隔时间

bool isStart = false;       //是否开启点击



defineTask(Task1);
 void Task1::setup()
 {
  delay(100);
  //设置所有点击控制引脚为功能输出
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  pinMode(n0, OUTPUT);       
  pinMode(n1, OUTPUT);    
  pinMode(n2, OUTPUT);    
  pinMode(n3, OUTPUT);    
  pinMode(n4, OUTPUT);    
  pinMode(n5, OUTPUT);    
  pinMode(n6, OUTPUT);    
  pinMode(n7, OUTPUT);    
  pinMode(n8, OUTPUT);    
  pinMode(n9, OUTPUT);    
  delay(1);
  Serial.begin(115200);
  //初始化所有点击都为非点击状态
  digitalWrite(n0, HIGH);  
  digitalWrite(n1, HIGH); 
  digitalWrite(n2, HIGH); 
  digitalWrite(n3, HIGH); 
  digitalWrite(n4, HIGH); 
  digitalWrite(n5, HIGH); 
  digitalWrite(n6, HIGH); 
  digitalWrite(n7, HIGH); 
  digitalWrite(n8, HIGH); 
  digitalWrite(n9, HIGH); 
  delay(1);
 }
 void Task1::loop()
 {
   if(isStart){

    //j10点一次
    digitalWrite(n0,LOW);
    delay(touchTime);
    digitalWrite(n0,HIGH);
    delay(delayTime);

    //j1点一次
    digitalWrite(n1,LOW);
    delay(touchTime);
    digitalWrite(n1,HIGH);
    delay(delayTime);

    //j2点一次
    digitalWrite(n2,LOW);
    delay(touchTime);
    digitalWrite(n2,HIGH);
    delay(delayTime);

    //j3点一次
    digitalWrite(n3,LOW);
    delay(touchTime);
    digitalWrite(n3,HIGH);
    delay(delayTime);

    //j4点一次
    digitalWrite(n4,LOW);
    delay(touchTime);
    digitalWrite(n4,HIGH);
    delay(delayTime);

    //j5点一次
    digitalWrite(n5,LOW);
    delay(touchTime);
    digitalWrite(n5,HIGH);
    delay(delayTime);

    //j6点一次
    digitalWrite(n6,LOW);
    delay(touchTime);
    digitalWrite(n6,HIGH);
    delay(delayTime);

    //j7点一次
    digitalWrite(n7,LOW);
    delay(touchTime);
    digitalWrite(n7,HIGH);
    delay(delayTime);

    //j8点一次
    digitalWrite(n8,LOW);
    delay(touchTime);
    digitalWrite(n8,HIGH);
    delay(delayTime);

    //j9点一次
    digitalWrite(n9,LOW);
    delay(touchTime);
    digitalWrite(n9,HIGH);
    delay(delayTime);

    //jok点一次
    digitalWrite(ok,LOW);
    delay(touchTime);
    digitalWrite(ok,HIGH);
    delay(delayTime);
  }
 }

//快速定义，按键检测进程
 defineTaskLoop(Task2)
 {
   int keyType = digitalRead(key);
  if(!keyType){
    isStart = !isStart;       //按键被按了一次
    delay(1000);              //按键消抖延时1秒
  }
 }

//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  pinMode(key,INPUT);
  mySCoop.start();
}

//Arduino程序主循环loop()函数部分
void loop() {
  
  yield();
}
