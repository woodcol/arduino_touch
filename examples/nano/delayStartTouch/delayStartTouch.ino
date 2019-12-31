#include <MsTimer2.h>               //定时器库的 头文件

#define Dpin 8
#define touchTimes 2              //一共点击屏多少次

#define initDelay     (70*60)         //初始延时70分钟
#define lastDelay     (2*60)          //后期延时2分钟


int touchCount = 0;

//延时70分钟
 
//经过的秒数
int timecount = initDelay;  //初始延时

int isLEDOpen = false;
 
void flash()                        //中断处理函数，改变灯的状态
{                        
  digitalWrite(LED_BUILTIN, isLEDOpen);   // 让Arduino的LED灯关闭
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
  MsTimer2::stop();                //开始计时
  isTimerRun = false;
}

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  pinMode(Dpin, INPUT);             //设置板子上的8脚为输出高低电平的功能,引脚输出状态由后边的loop()函数控制

  digitalWrite(LED_BUILTIN, LOW);   // 让Arduino的LED灯关闭
//  pinMode(Dpin, OUTPUT);             //设置板子上的8脚为输出高低电平的功能,引脚输出状态由后边的loop()函数控制
//  digitalWrite(Dpin, HIGH);            // 点击初始化为不点击
  Serial.begin(115200);
  MsTimer2::set(1000, flash);        // 中断设置函数，每 1s 进入一次中断
  MsTimer2::start();                //开始计时
}

int isSetOUPPin = false;
void touchOnce()
{
  if(!isSetOUPPin)
  {
    pinMode(Dpin, OUTPUT);             //设置板子上的8脚为输出高低电平的功能,引脚输出状态由后边的loop()函数控制
    isSetOUPPin = true;
  }
  digitalWrite(Dpin, LOW);    //8脚输出低电平，点击头发生点击动作
  digitalWrite(LED_BUILTIN, HIGH);   // 让Arduino的LED灯亮起
  delay(35);               //延时35毫秒，（也就是让程序暂停35毫秒，点击头点击屏幕35毫秒）
  digitalWrite(Dpin, HIGH);  //8脚输出设置为高电平，点击头停止触发点击屏幕
  digitalWrite(LED_BUILTIN, LOW);   // 让Arduino板子上的LED灯熄灭
  touchCount++;
}

//Arduino程序主循环loop()函数部分
void loop() {

  if(isTimerRun && timecount<=0){
    stopTimer();
    touchOnce();
    if( touchCount < touchTimes )
    {
      startTimer(lastDelay);   //设置两分定时器
    } 
  }
}
