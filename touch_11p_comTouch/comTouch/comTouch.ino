/*

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

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second: 
  pinMode(LED_BUILTIN, OUTPUT);  
  mySCoop.start();
}
bool isStart = false;

int touchNum = -1;

char tmp = '!';

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

defineTaskLoop(Task2)
 {
  if(isStart){
    return;
  }else{
    if(touchNum != -1)
    {
      touchOnePin(touchNum);
      touchNum = -1;
    }
  }
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
  Serial.begin(115200);     //设置串口波特率
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
        delay(1);
       if (Serial.available() > 0) {
        delay(1); // 等待数据传完
        char tmpnow = Serial.read();
//        delay(1);
        Serial.print(tmpnow);
//        delay(1);        // delay in between reads for stability
        tmp = tmpnow;
        switch(tmp){
          case '1':
          {
            touchNum = J1;
          }
          break;
          case '2':
          {
            touchNum = J2;
          }
          break;
          case '3':
          {
            touchNum = J3;
          }
          break;
          case '4':
          {
            touchNum = J4;
          }
          break;
          case '5':
          {
            touchNum = J5;
          }
          break;
          case '6':
          {
            touchNum = J6;
          }
          break;
          case '7':
          {
            touchNum = J7;
          }
          break;
          case '8':
          {
            touchNum = J8;
          }
          break;
          case '9':
          {
            touchNum = J9;
          }
          break;
          case 'a':
          {
            touchNum = J10;
          }
          break;
          case 'b':
          {
            touchNum = Jok;
          }
          break;
          default:
          {
            touchNum = -1;
          }
          break;
        }
       }
}
// the loop routine runs over and over again forever:
void loop() {
    yield();
}
