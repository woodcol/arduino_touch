
#define Tout 8   //点击头输出控制引脚
#define key1 2  //按键1，按一下点击一下
#define key2 3  //控鍵2，按住会每秒9次的连点



#define touchTime   25    //点击屏的时间

#define delayTime   86    //连续点击的间隔时间90毫秒，1000/9 ～= 111 = 25 + 85


//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  
  delay(100);
  //初始化引脚功能
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  pinMode(key1, INPUT_PULLUP);    
  pinMode(key2, INPUT_PULLUP);   
  pinMode(Tout, OUTPUT);    

//  Serial.begin(9600);

  //初始化点击头为非点击状态
  digitalWrite(Tout, HIGH); 
  delay(1);           //设置板子上的8脚为输出高低电平的功能,引脚输出状态由后边的loop()函数控制
  
}

bool isTouch = false;

//Arduino程序主循环loop()函数部分
void loop() {

  int isKey1 = digitalRead(key1);       //是否按键1被按下,当被按下时读取的信号为低
  int isKey2 = digitalRead(key2);;       //是否按键2被按下

  
  if(!isKey2){
  //按下连点键
  digitalWrite(Tout, LOW);            //8脚输出低电平，点击头发生点击动作
  digitalWrite(LED_BUILTIN, HIGH);   // 让Arduino的LED灯亮起
  delay(touchTime);                   //延时25毫秒，（也就是让程序暂停25毫秒，点击头点击屏幕25毫秒）
  digitalWrite(Tout, HIGH);           //8脚输出设置为高电平，点击头停止触发点击屏幕
  digitalWrite(LED_BUILTIN, LOW);      // 让Arduino板子上的LED灯熄灭
  delay(delayTime);                   //延时90毫秒
  }else{
    //按一下点击一下被按下
    if(!isKey1 && (!isTouch)){
      isTouch = true;
      digitalWrite(Tout, LOW);            //8脚输出低电平，点击头发生点击动作
      digitalWrite(LED_BUILTIN, HIGH);    // 让Arduino的LED灯亮起
      delay(touchTime);                   //延时50毫秒，（也就是让程序暂停50毫秒，点击头点击屏幕50毫秒）
      digitalWrite(Tout, HIGH);           //8脚输出设置为高电平，点击头停止触发点击屏幕
      digitalWrite(LED_BUILTIN, LOW);     // 让Arduino板子上的LED灯熄灭
      delay(30);                          //延时30毫秒
      
    }else if(isKey1){
      isTouch = false;
      delay(30);                          //延时30毫秒
    }
  }
}
