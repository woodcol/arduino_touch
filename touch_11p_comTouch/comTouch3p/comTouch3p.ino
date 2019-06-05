/*
 https://fengmm521.taobao.com
 本例子为通过电脑上的串口给板子发送消息，然后板子会解析消息后驱动相应的点击头
 串口发送字符，板子点击对应点击头
  '1',点击J1点击头
  '2',点击J2点击头
  '3',点击J3点击头
  '4',点击J4点击头
  '5',点击J5点击头
  '6',点击J6点击头
  '7',点击J7点击头
  '8',点击J8点击头
  '9',点击J9点击头
  'a',点击J10点击头
  'b',点击Jok点击头
*/
#include <SCoop.h> //SCoop库为arduino的一个多线程库



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


#define touchTime   35    //点击屏的时间,即模仿手指点击时在手屏上的停留时间，单位：毫秒

#define delayTime   35    //点击后停止时间，单位：毫秒

char tmp = '0';         //串口收到了消息
bool isStart = false;   //当前是否有点击头正在动作

void stopAllPin()
{
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
  isStart = false;
}

void touchOnePin(int pNum)
{
  isStart = true;
  digitalWrite(pNum, HIGH);
  digitalWrite(LED_BUILTIN, HIGH); 
  digitalWrite(pNum, LOW);
  delay(touchTime);
  digitalWrite(pNum, HIGH);
  digitalWrite(LED_BUILTIN, LOW); 
  delay(delayTime);
  isStart = false;
}

defineTask(Task1);
void Task1::setup()
{
    delay(100); //延时100ms等待刚上电后电源稳定
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
  Serial.begin(9600);     //设置串口波特率
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

bool isData = false;

defineTaskLoop(Task2)
 {
   //读串口值
  if (Serial.available() > 0) {
    delay(2); // 等待数据传完
    char tmpnow = Serial.read();
//    delay(2);
    Serial.print(tmpnow);
    delay(2);
    if(tmpnow == 'x')
    {
      isData = true;
    }
    if(!isStart && isData){
      tmp = tmpnow;
      isData = false;
      stopAllPin();
      
    }
  }

  
  
 }

void Task1::loop()
{
  
 switch(tmp){
    case '1'://当串口接收到数字1，控制J1点击头点击一次
    {
      //J1点击头，点一下
      touchOnePin(J1);
      tmp = '0';
      
    }
    break;
    case '2': 
    {
      //J2点击头，点一下
      touchOnePin(J2);
      tmp = '0';
      break;
    }
    case '3': 
    {
      //J3点击头，点一下
      touchOnePin(J3);
      tmp = '0';
      break;
    }
    case '4': 
    {
      //J4点击头，点一下
      touchOnePin(J4);
      tmp = '0';
      
    }
    break;
    case '5': 
    {
      //J5点击头，点一下
      touchOnePin(J5);
      tmp = '0';
      
    }
    break;
    case '6': 
    {
      //J6点击头，点一下
      touchOnePin(J6);
      tmp = '0';
      break;
    }
    case '7': 
    {
      //J7点击头，点一下
      touchOnePin(J7);
      tmp = '0';
      break;
    }
    case '8': 
    {
      //J8点击头，点一下
      touchOnePin(J8);
      tmp = '0';
      break;
    }
    case '9': 
    {
      //J9点击头，点一下
      touchOnePin(J9);
      tmp = '0';
      break;
    }
    case 'a': 
    {
      //J10点击头，点一下
      touchOnePin(J10);
      tmp = '0';
      break;
    }
    case 'b': 
    {
      //Jok点击头，点一下
      touchOnePin(Jok);
      tmp = '0';
      break;
    }
    default: { 
      stopAllPin();
      delay(delayTime);
      tmp = '0';
      break;
    }
  }
}
void setup() {
   mySCoop.start();
}

void loop() {
  yield();
}
