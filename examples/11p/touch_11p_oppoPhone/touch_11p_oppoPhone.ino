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


#define touchTime   35    //点击屏的时间,单位毫秒

#define delayTime   35    //两次点击的间隔时间,单位毫秒

#define   dTime1    100     //J1点击后的间隔时间,单位毫秒
#define   dTime2    100     //J2点击后的间隔时间,单位毫秒
#define   dTime3    100    //J3点击后的间隔时间,单位毫秒
#define   dTime4    1000    //J4点击后的间隔时间,单位毫秒


//所有点击头点击一次,用时100ms
void touchOnceWithPinNum(int pin){
  //j10,j1,j2,j3,j4,j5,j6,j7,j8,j9,jJok依次按下
    digitalWrite(LED_BUILTIN, HIGH);   //led点亮
    digitalWrite(pin,LOW);             //pin按下
    //按下延时时间,可在touchTime那里修改，程序原始设置是30ms
    delay(touchTime); 
    digitalWrite(pin,HIGH);           //pin不按下
    //不点击的时间,可在delayTime那里修改，程序原始设置是35ms
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);   //led灭
}


//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  pinMode(key,INPUT);
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

//Arduino程序主循环loop()函数部分
void loop() {

   int keyType = digitalRead(key);
   if(!keyType){
        touchOnceWithPinNum(J1);   //J1点击一次
        delay(dTime1);             //延时间隔时间dTime1
        touchOnceWithPinNum(J2);   //J2点击一次
        delay(dTime2);             //延时间隔时间dTime2
        touchOnceWithPinNum(J3);   //J3点击一次
        delay(dTime3);             //延时间隔时间dTime3
        touchOnceWithPinNum(J4);   //J4点击一次
        delay(dTime4);             //延时间隔时间dTime4
  
   }else{
      //按钮非按下，并且没有逻辑在跑时所有点击头都设置为非按下状态
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
      
      digitalWrite(LED_BUILTIN, LOW);   //led灭
   }

}
