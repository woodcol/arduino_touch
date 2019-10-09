
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

#define key   A2   //继电器开关所接的引脚

/**
下边有5个时间设置参数，是一个响应音频信号触发后的点击动作周期完整时间
**/
#define delaystart   0     //音频端有信号时延时开始的时间，单位:毫秒,为0表示无启动延时
#define touchtime1   35    //第一个点击头按屏时间:35毫秒
#define midDelay     3000  //第一个点击头停止的延时时间3000毫秒，即3秒
#define touchtime2   35    //第二个点击头按屏时间:35毫秒
#define delayend     0     //一套动作响应结束后的延时等待时间，0表示不等，直接进入一次音频信号检测

//初始化所有点击头
void initALLOutPutPin(){
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

//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  delay(100);
  Serial.begin(115200);
  pinMode(key,INPUT_PULLUP);//key引脚未接电阻时，对key按键使用芯片内上拉电阻
}

//Arduino程序主循环loop()函数部分
void loop() {
  //读取引脚key的信号是否开关闭合，开关闭合时引脚上的电压为低电平，否则为高电平
  int keyType = digitalRead(key);
  
  //当开关Key开关闭合时，keyType值为false,否则为true
  if(!keyType){
    delay(delaystart);     //开关信号后启动延时
    digitalWrite(J1,LOW);  //第一个点击头点住屏
    delay(touchtime1);     //第一个点击头点屏时间
    digitalWrite(J1,HIGH); //第一个点击头不点屏
    delay(midDelay);       //第一个头点击结束的等待时间
    digitalWrite(J2,LOW);  //第二个点击头按住屏
    delay(touchtime2);     //第二个点击头按住屏时间
    digitalWrite(J2,HIGH); //第二个点击头不点屏
    delay(delayend);       //一次点击相应动作结束后延时时间
  }
}
