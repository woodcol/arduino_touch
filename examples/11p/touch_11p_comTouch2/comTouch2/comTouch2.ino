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

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second: 
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(key, INPUT);  //设置按键引脚为输入功能
  mySCoop.start();
}

char tmp = '!';
const int pinkeys[11] = {J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,Jok}; //要点击的引脚和排号对应关系

//按键状态设置为按下
void touchPin(int pNum)
{
  digitalWrite(pinkeys[pNum], LOW);
}
//按键状态设置为弹起
void untouchPin(int pNum)
{
  digitalWrite(pinkeys[pNum], HIGH);
}

//所有按键状态改为按下
void touchAll()
{
  for(int i=0;i<11;i++){
    digitalWrite(pinkeys[i], LOW);
    delayMicroseconds(10);//延时10微妙,防止电流变化过快造成电源不稳定
  }
}
//所有按键状态改为弹起
void untouchAll()
{
  for(int i=0;i<11;i++){
    digitalWrite(pinkeys[i], HIGH);
    delayMicroseconds(10);//延时10微妙,防止电流变化过快造成电源不稳定
  }
}

//线程2,用于主按板上的按键是否被按下检测
defineTaskLoop(Task2)
 {
  delayMicroseconds(100);//延时100微妙,防止进程死锁
  int ktype = digitalRead(key);
  if(ktype < 0 and Serial.available() == 0){
    Serial.print('#');//当主控板上按键被按下时串口输出一个'#'字符给上位机,并延时40ms作为按键消抖
    Serial.flush();
    delay(40);
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
        // delayMicroseconds(500);
        delay(1);
        if (Serial.available() > 0) {
        // delay(1); 
        delayMicroseconds(100);//等待数据传完,延时100微妙
        char tmpnow = Serial.read();
        // delay(1);
        delayMicroseconds(100);
        tmp = tmpnow;
        Serial.print(tmp);
        Serial.flush();
        // delay(1);        // delay in between reads for stability
        delayMicroseconds(100);
        switch (tmp) {
            //J1
                  case '0':
                    touchPin(0);
                    break;
                  case '1':
                    untouchPin(0);
                    break;
                    
            //J2
                  case '2':
                    touchPin(1);
                    break;
                  case '3':
                    untouchPin(1);
                    break;
                    
            //J3
                  case '4':
                    touchPin(2);
                    break;
                  case '5':
                    untouchPin(2);
                    break;
                    
            //J4
                  case '6':
                    touchPin(3);
                    break;
                  case '7':
                    untouchPin(3);
                    break;
                    
            //J5
                  case '8':
                    touchPin(4);
                    break;
                  case '9':
                    untouchPin(4);
                    break;
                    
            //J6
                  case 'a':
                    touchPin(5);
                    break;
                  case 'b':
                    untouchPin(5);
                    break;
                    
            //J7
                  case 'c':
                    touchPin(6);
                    break;
                  case 'd':
                    untouchPin(6);
                    break;
                    
            //J8
                  case 'e':
                    touchPin(7);
                    break;
                  case 'f':
                    untouchPin(7);
                    break;
                    
            //J9
                  case 'g':
                    touchPin(8);
                    break;
                  case 'h':
                    untouchPin(8);
                    break;
                    
            //J10
                  case 'i':
                    touchPin(9);
                    break;
                  case 'j':
                    untouchPin(9);
                    break;
                    
            //Jok
                  case 'k':
                    touchPin(10);
                    break;
                  case 'l':
                    untouchPin(10);
                    break;
            
            //all touch
                  case 'x':
                    touchAll();
                    break;
            
            //all untouch
                  case 'y':
                    untouchAll();
                    break;
            
                  default:
                    // do something
                    break;
            
              }
       }
}
// the loop routine runs over and over again forever:
void loop() {
    yield();
}
