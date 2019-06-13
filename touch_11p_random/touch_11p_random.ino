#include <SCoop.h>       //Arduino多线程库

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


#define touchTime   25    //点击屏的时间


#define delayTimeMin   1000     //两次点击的间隔最短时间，1,单位为秒

#define delayTimeMax   20000    //两次点击的间隔最长时间，20,单位为秒

const int pinkeys[11] = {J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,Jok}; //要点击的引脚和排号对应关系

unsigned long pinRD[11] = {0,0,0,0,0,0,0,0,0,0,0};   //所有引脚的下次点击延时时间

int nextPinTouch = 0;      //下次点击延时最短的引脚ID,


bool isStart = true;       //是否开启点击,默认上电即开启,当按下按键时关闭点击，再按下时启动点击
bool isTouchNow = false;


void touchOnePin(int pinNum)
{
  if(isStart){
      isTouchNow = true;
      digitalWrite(pinNum,LOW);
      digitalWrite(LED_BUILTIN,HIGH);
      //按下延时时间,可在touchTime那里修改，程序原始设置是20ms
      delay(touchTime); 
      digitalWrite(pinNum,HIGH);
      digitalWrite(LED_BUILTIN,LOW);
      Serial.println(pinNum);
      Serial.flush();
      delay(touchTime); 
      isTouchNow = false;
      
  }else{
    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次不点击
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
    //不点击的时间,可在delayTime那里修改，程序原始设置是25ms
  }
}

int findMinDelayTouchPin()
{
  unsigned long minDelay = pinRD[0];
  int tmptouch = 0;
  for(int i = 0;i < 11;i++)
  {
    if(minDelay > pinRD[i]){
      tmptouch = i;
      minDelay = pinRD[i];
    }
  }
  return tmptouch;
}

int initAllFirstDelayTime()
{
  unsigned long nowtime=millis();  //系统开始运行的时间;
  for(int i = 0;i < 11;i++)
  {
      pinRD[i] = nowtime + random(delayTimeMin,delayTimeMax);
  }
}
int updateNowTouch(int pinID)
{
  unsigned long nowtime=millis();  //系统开始运行的时间;
  pinRD[pinID] =  nowtime + random(delayTimeMin,delayTimeMax);
}

 defineTaskLoop(Task1)
 {
  if(isStart){
    if(!isTouchNow){
        unsigned long nowtime=millis();  //系统开始运行的时间;
         for(int i = 0;i < 11;i++)
         {
            if(nowtime >= pinRD[i]){
              updateNowTouch(i);
              touchOnePin(pinkeys[i]);
            }
         }
      }
  }else{
    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次按下
    digitalWrite(J10,LOW);
    digitalWrite(J1,LOW);
    digitalWrite(J2,LOW);
    digitalWrite(J3,LOW);
    digitalWrite(J4,LOW);
    digitalWrite(J5,LOW);
    digitalWrite(J6,LOW);
    digitalWrite(J7,LOW);
    digitalWrite(J8,LOW);
    digitalWrite(J9,LOW);
    digitalWrite(Jok,LOW);
    //按下延时时间,可在touchTime那里修改，程序原始设置是20ms
    delay(touchTime); 
    //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次不点击
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
    //不点击的时间,可在delayTime那里修改，程序原始设置是25ms
    delay(touchTime);
  }
      
 }



//快速定义，按键检测进程,这个功能是一开始就开启每秒点22次，按一下功能键后就停止点击了，再按一下又会开启点击
 defineTaskLoop(Task0)
 {
   int keyType = digitalRead(key);
  if(!keyType){
    isStart = !isStart;       //按键被按了一次
    delay(1000);              //按键消抖延时1秒
  }
 }


//
//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  pinMode(key,INPUT);
  randomSeed(analogRead(A5));
  delay(100);
  //设置所有点击控制引脚为功能输出
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  delay(1);
  Serial.begin(115200);

  delay(1);
  nextPinTouch = initAllFirstDelayTime();
  delay(1);
  mySCoop.start();
}

//Arduino程序主循环loop()函数部分
void loop() {
  yield();
}
