
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


#define touchTime   20    //点击屏的时间

#define delayTime   25    //两次点击的间隔时间

bool isStart = true;       //是否开启点击,默认上电即开启,当按下按键时关闭点击，再按下时启动点击



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

    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jok依次按下
    digitalWrite(n0,LOW);
    digitalWrite(n1,LOW);
    digitalWrite(n2,LOW);
    digitalWrite(n3,LOW);
    digitalWrite(n4,LOW);
    digitalWrite(n5,LOW);
    digitalWrite(n6,LOW);
    digitalWrite(n7,LOW);
    digitalWrite(n8,LOW);
    digitalWrite(n9,LOW);
    digitalWrite(ok,LOW);
    //按下延时时间,可在touchTime那里修改，程序原始设置是20ms
    delay(touchTime); 
    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jok依次不点击
    digitalWrite(n0,HIGH);
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,HIGH);
    digitalWrite(n4,HIGH);
    digitalWrite(n5,HIGH);
    digitalWrite(n6,HIGH);
    digitalWrite(n7,HIGH);
    digitalWrite(n8,HIGH);
    digitalWrite(n9,HIGH);
    digitalWrite(ok,HIGH);
    //不点击的时间,可在delayTime那里修改，程序原始设置是25ms
    delay(delayTime);
  }else{
    digitalWrite(n0,HIGH);
    digitalWrite(n1,HIGH);
    digitalWrite(n2,HIGH);
    digitalWrite(n3,HIGH);
    digitalWrite(n4,HIGH);
    digitalWrite(n5,HIGH);
    digitalWrite(n6,HIGH);
    digitalWrite(n7,HIGH);
    digitalWrite(n8,HIGH);
    digitalWrite(n9,HIGH);
    digitalWrite(ok,HIGH);
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
