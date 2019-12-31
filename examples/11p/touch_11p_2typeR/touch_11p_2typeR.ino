#include <SCoop.h>       //Arduino多线程库
#include <MsTimer2.h>               //定时器库的 头文件

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


#define touchTimeMin   40    //点击屏的时间最短，单位毫秒

#define touchTimeMax   50    //点击屏的时间最长，单位毫秒

#define runTimesMax (36*60)     //程序运行36*60秒,即36分钟


const int pinkeys[11] = {J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,Jok}; //要点击的引脚和排号对应关系

const int delaytimes[3] = {4800,5000,5600};                   //三个随机间隔的时间,时间单位为毫秒

#define dTimeCount 3          //表示有三个随机时间,也就是是上边数组的长度


unsigned long pinRD = 0;   //下次点击延时时间

bool isStart = true;       //是否开启点击,默认上电即开启,当按下按键时关闭点击，再按下时启动点击
bool isTouchNow = false;


//经过的秒数
int timecount = runTimesMax;  //程序远行36分钟后停止

int isLEDOpen = false;
 
void flash()                        //中断处理函数，改变灯的状态
{                        
  digitalWrite(LED_BUILTIN, isLEDOpen);   // 让Arduino的LED灯每秒闪一次
  isLEDOpen = !isLEDOpen;
  timecount--;
  Serial.println(timecount);
}

int isTimerRun = true;

void startTimer(int secend)
{
  timecount = secend;
  MsTimer2::start();                //开始计时
  isTimerRun = true;
  
}

void stopTimer()
{
  MsTimer2::stop();                //停止计时
  isTimerRun = false;
}



void touchOnePin(int pinNum)
{
      isTouchNow = true;
      int touchTime = random(touchTimeMin,touchTimeMax);
      digitalWrite(pinNum,LOW);
      digitalWrite(LED_BUILTIN,HIGH);
      //按下延时时间,可在touchTime那里修改，程序原始设置是20ms
      sleep(touchTime); 
      digitalWrite(pinNum,HIGH);
      digitalWrite(LED_BUILTIN,LOW);
      sleep(25); 
      isTouchNow = false;
}

void initDelayTime()
{
  unsigned long nowtime=millis();  //系统开始运行的时间;
  int delaytype = random(0,dTimeCount);
  int delaytimetmp = delaytimes[delaytype];
  pinRD = nowtime + delaytimetmp;
}

 defineTaskLoop(Task1)
 {
  if(isStart){
    if(timecount > 0){
      if(!isTouchNow){
        unsigned long nowtime=millis();  //系统开始运行的时间;
        if(nowtime >= pinRD){
          initDelayTime();
            for(int i = 0;i < 11;i++)
            {
                 touchOnePin(pinkeys[i]);
            }
        }
      }
    }else{
      stopTimer();    //停止工作记时器
    }
  }else{
    if(isTimerRun){
      timecount = runTimesMax;     //按键按下，重新设置定时器时间
    }else{
      startTimer(runTimesMax);    //按键按下，重新启动计时器
    }
    isStart = true;
  }
 }



//快速定义，按键检测进程,这个功能是一开始就开启每秒点22次，按一下功能键后就停止点击了，再按一下又会开启点击
 defineTaskLoop(Task0)
 {
   int keyType = digitalRead(key);
  if(!keyType){
    isStart = !isStart;       //按键被按了一次
    sleep(1000);              //按键消抖延时1秒
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
  for(int i = 0;i < 11;i++)
  {
    pinMode(pinkeys[i], OUTPUT);
  }
  delay(1);
  Serial.begin(115200);

  delay(1);
  initDelayTime();
  delay(1);
  mySCoop.start();

  MsTimer2::set(1000, flash);        //中断设置函数，每 1s 进入一次中断
  MsTimer2::start();                //开始计时
  
}

//Arduino程序主循环loop()函数部分
void loop() {
  yield();
}
