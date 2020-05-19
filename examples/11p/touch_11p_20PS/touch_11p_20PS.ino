
#include <SCoop.h>

#define J1 11   //控制点击数字1的引脚,板子上的J1点击头，定义为arduino nano小板子上的D11引脚
#define J2 2    //控制点击数字2的引脚,板子上的J2点击头，定义为arduino nano小板子上的D2引脚
#define J3 3    //控制点击数字3的引脚,板子上的J3点击头，定义为arduino nano小板子上的D3引脚
#define J4 4    //控制点击数字4的引脚,板子上的J4点击头，定义为arduino nano小板子上的D4引脚
#define J5 5    //控制点击数字5的引脚,板子上的J5点击头，定义为arduino nano小板子上的D5引脚
#define J6 6    //控制点击数字6的引脚,板子上的J6点击头，定义为arduino nano小板子上的D6引脚
#define J7 7    //控制点击数字7的引脚,板子上的J7点击头，定义为arduino nano小板子上的D7引脚
#define J8 8    //控制点击数字8的引脚,板子上的J8点击头，定义为arduino nano小板子上的D8引脚
#define J9 9    //控制点击数字9的引脚,板子上的J9点击头，定义为arduino nano小板子上的D9引脚
#define J10 10  //控制点击数字0的引脚,板子上的J10点击头，定义为arduino nano小板子上的D10引脚
#define Jok 12  //控制点击输入密码完成后的确定的引脚,板子上的Jok点击头，定义为arduino nano小板子上的D12引脚

#define key   A0


#define touchTime   35    //点击屏的时间,注意，有的国产手机本身扫描点击的频率比较慢，所以达不到每秒20次，像魅族手机，这里要改成50

#define delayTime   35    //两次点击的间隔时间,魅族手机这里也请改成50

bool isStart = true;       //是否开启点击,默认上电即开启,当按下按键时关闭点击，再按下时启动点击


defineTask(Task1);
 void Task1::setup()
 {
  delay(100);
  //设置所有点击控制引脚为功能输出
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  pinMode(J10, OUTPUT);       
  pinMode(J1, OUTPUT);    
  pinMode(J2, OUTPUT);    
  pinMode(J3, OUTPUT);    
  pinMode(J4, OUTPUT);    
  pinMode(J5, OUTPUT);    
  pinMode(J6, OUTPUT);    
  pinMode(J7, OUTPUT);    
  pinMode(J8, OUTPUT);    
  pinMode(J9, OUTPUT);    
  pinMode(Jok, OUTPUT); 
  delay(1);
  Serial.begin(115200);
  //初始化所有点击都为非点击状态
  digitalWrite(J10, HIGH);  
  digitalWrite(J1, HIGH); 
  digitalWrite(J2, HIGH); 
  digitalWrite(J3, HIGH); 
  digitalWrite(J4, HIGH); 
  digitalWrite(J5, HIGH); 
  digitalWrite(J6, HIGH); 
  digitalWrite(J7, HIGH); 
  digitalWrite(J8, HIGH); 
  digitalWrite(J9, HIGH); 
  digitalWrite(Jok, HIGH); 
  delay(1);
 }
 
 void Task1::loop()
 {
   if(isStart){

    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次按下
    digitalWrite(J10,LOW);
    delay(1);
    digitalWrite(J1,LOW);
    delay(1);
    digitalWrite(J2,LOW);
    delay(1);
    digitalWrite(J3,LOW);
    delay(1);
    digitalWrite(J4,LOW);
    delay(1);
    digitalWrite(J5,LOW);
    delay(1);
    digitalWrite(J6,LOW);
    delay(1);
    digitalWrite(J7,LOW);
    delay(1);
    digitalWrite(J8,LOW);
    delay(1);
    digitalWrite(J9,LOW);
    delay(1);
    digitalWrite(Jok,LOW);
    //按下延时时间,可在touchTime那里修改，程序原始设置是20ms
    delay(touchTime-10); 
    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次不点击
    digitalWrite(J10,HIGH);
    delay(1);
    digitalWrite(J1,HIGH);
    delay(1);
    digitalWrite(J2,HIGH);
    delay(1);
    digitalWrite(J3,HIGH);
    delay(1);
    digitalWrite(J4,HIGH);
    delay(1);
    digitalWrite(J5,HIGH);
    delay(1);
    digitalWrite(J6,HIGH);
    delay(1);
    digitalWrite(J7,HIGH);
    delay(1);
    digitalWrite(J8,HIGH);
    delay(1);
    digitalWrite(J9,HIGH);
    delay(1);
    digitalWrite(Jok,HIGH);
    //不点击的时间,可在delayTime那里修改，程序原始设置是25ms
    delay(delayTime);
  }else{
    digitalWrite(J10,HIGH);
    digitalWrite(J1,HIGH);
    digitalWrite(J2,HIGH);
    digitalWrite(J3,HIGH);
    digitalWrite(J4,HIGH);
    digitalWrite(J5,HIGH);
    digitalWrite(J6,HIGH);
    digitalWrite(J7,HIGH);
    digitalWrite(J8,HIGH);
    digitalWrite(J9,HIGH);
    digitalWrite(Jok,HIGH);
  }
 }

//快速定义，按键检测进程,这个功能是一开始就开启每秒点22次，按一下功能键后就停止点击了，再按一下又会开启点击
 defineTaskLoop(Task2)
 {
   int keyType = digitalRead(key);
  if(!keyType){
    isStart = !isStart;       //按键被按了一次
    delay(1000);              //按键消抖延时1秒
  }
 }

////快速定义，按键检测进程，这个功能是当按键按下时会每秒点22次，不按时就不点
// defineTaskLoop(Task2)
// {
//   int keyType = digitalRead(key);
//  if(!keyType){
//    isStart = true;       //按键被按了一次
//  }else{
//    isStart = false;
//  }
// }

//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  //pinMode(key,INPUT_PULLUP); //key引脚未接电阻时，对key按键使用芯片内上拉电阻
  pinMode(key,INPUT);
  mySCoop.start();
}

//Arduino程序主循环loop()函数部分
void loop() {
  yield();
}
