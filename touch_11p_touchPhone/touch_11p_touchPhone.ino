
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

#define key   A0  //板子上的按键引脚，这个示例程序中没有用到

#define StartN 0        //开始的数字，小于1000的数字前边的0省略了，0表示为0000
#define EndN   9999     //结束的数字，9999

//以下三个为时间相关定义，所有时间的单位都为毫秒，1秒=1000毫秒
#define touchTime   35    //点击一次屏幕的时间中按下的时间
#define touchUpTime 330    //一次点击之后不按下的时间,这个时间决定了两次点击屏之间的时间间隔
#define loopTime    800   //当完成一次4位或者6位密码连续输入之后，开始进行下一轮密码输入的时间间隔

#define isOKButton  1      //输入完成后是否有确认需要点击，有这里设置为1，没有设置为0.当设置为1时，密码输入完成后会触发点击ok

//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {

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
  pinMode(ok, OUTPUT);    
  
  pinMode(key,INPUT);     //当前示例虽然没有用到按键，感觉这里还是把按键引脚设置为输入状态会比较好
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
  digitalWrite(ok, HIGH);   
  delay(1);
  
}

int lastTouch = -1;   //上一个点击的引脚
long lastNumber = -1;  //上一个输入的数字


//清除所有为不点击
void cleanAllTouch()
{
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
  digitalWrite(ok, HIGH);   

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
      touchPin = n0; 
      break;
    }
    case 1:
    {
      touchPin = n1;
      break;
    }
    case 2:
    {
      touchPin = n2;
      break;
    }
    case 3:
    {
      touchPin = n3;
      break;
    }
    case 4:
    {
      touchPin = n4;
      break;
    }
    case 5:
    {
      touchPin = n5;
      break;
    }
    case 6:
    {
      touchPin = n6;
      break;
    }
    case 7:
    {
      touchPin = n7;
      break;
    }
    case 8:
    {
      touchPin = n8;
      break;
    }
    case 9:
    {
      touchPin = n9;
      break;
    }
    default:
    {
      touchPin = ok;
      break;
    }
  }
  digitalWrite(touchPin, LOW);
  lastTouch = touchPin;
  delay(touchTime);
  digitalWrite(touchPin, HIGH);
  if(touchPin == ok){
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
  if(isOKButton){
    touchOnePinAction(ok);
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
