
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

#define key   A0  //板子上的按键引脚，这个示例程序中没有用到

#define StartN 0        //开始的数字，小于1000的数字前边的0省略了，0表示为0000
#define EndN   9999     //结束的数字，9999

//以下三个为时间相关定义，所有时间的单位都为毫秒，1秒=1000毫秒
#define touchTime   35    //点击一次屏幕的时间中按下的时间
#define touchUpTime 330    //一次点击之后不按下的时间,这个时间决定了两次点击屏之间的时间间隔
#define loopTime    800   //当完成一次4位或者6位密码连续输入之后，开始进行下一轮密码输入的时间间隔

#define isJokButton  1      //输入完成后是否有确认需要点击，有这里设置为1，没有设置为0.当设置为1时，密码输入完成后会触发点击Jok

//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {

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
  
  pinMode(key,INPUT);     //当前示例虽然没有用到按键，感觉这里还是把按键引脚设置为输入状态会比较好
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

int lastTouch = -1;   //上一个点击的引脚
long lastNumber = -1;  //上一个输入的数字


//清除所有为不点击
void cleanAllTouch()
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

  lastTouch = -1;
}

void touchOnePinAction(int num)
{
  cleanAllTouch();
  int touchPin = -1;
  switch(num)
  {
    case 0:
    {
      touchPin = J10; 
      break;
    }
    case 1:
    {
      touchPin = J1;
      break;
    }
    case 2:
    {
      touchPin = J2;
      break;
    }
    case 3:
    {
      touchPin = J3;
      break;
    }
    case 4:
    {
      touchPin = J4;
      break;
    }
    case 5:
    {
      touchPin = J5;
      break;
    }
    case 6:
    {
      touchPin = J6;
      break;
    }
    case 7:
    {
      touchPin = J7;
      break;
    }
    case 8:
    {
      touchPin = J8;
      break;
    }
    case 9:
    {
      touchPin = J9;
      break;
    }
    default:
    {
      touchPin = Jok;
      break;
    }
  }
  digitalWrite(touchPin, LOW);
  lastTouch = touchPin;
  delay(touchTime);
  digitalWrite(touchPin, HIGH);
  if(touchPin == Jok){
    delay(loopTime);
  }else{
    delay(touchUpTime);
  }
  
}

void touchNumer(long number)
{
  digitalWrite(LED_BUILTIN, HIGH); 
  int t1 = number%10;   //要输入的个位数
  int t2 = floor((number%100)/10);   //要输入的十位数
  int t3 = floor((number%1000)/100);   //要输入的百位数
  int t4 = floor((number%10000)/1000);   //要输入的千位数
  int t5 = -1;
  int t6 = -1;
  if(EndN > 9999){
    t5 = floor((number%100000)/10000);   //要输入的万位数
    t6 = floor((number%1000000)/100000);   //要输入的十万位数
  }
  Serial.println(number);
  if(t6 >= 0){
    touchOnePinAction(t6);
  }
  if(t5 >= 0){
    touchOnePinAction(t5);
  }
  touchOnePinAction(t4);
  Serial.print(t4);
  touchOnePinAction(t3);
  Serial.print(t3);
  touchOnePinAction(t2);
  Serial.print(t2);
  touchOnePinAction(t1);
  Serial.println(t1);
  digitalWrite(LED_BUILTIN, LOW);
  if(isJokButton){
    touchOnePinAction(Jok);
  }else{
    delay(loopTime);
  }
  
}

bool touchNextNumber()
{
  if(lastNumber < 0 || lastNumber < StartN){
    lastNumber = StartN;
  }else{
    lastNumber++;
  }
  if(lastNumber <= EndN){
    touchNumer(lastNumber);
  }else{
    lastNumber = EndN + 1;
    return false;
  }
  return true;
}

//Arduino程序主循环loop()函数部分
void loop() {
  delay(100);
  bool isNotEnd = true;
  while(isNotEnd){
    isNotEnd = touchNextNumber();
  }

  while(true){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
}
