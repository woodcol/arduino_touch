
//Arduino开机或者复位后只运行一次的初始化函数setup()
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);   //设置板子上的控制LED的引脚为输出高低电平的功能，引脚输出高电平时板子上的LED灯会亮
  pinMode(8, OUTPUT);             //设置板子上的8脚为输出高低电平的功能,引脚输出状态由后边的loop()函数控制
  
}

//Arduino程序主循环loop()函数部分
void loop() {

  delay(29);               //延时50毫秒
  digitalWrite(8, LOW);    //8脚输出低电平，点击头发生点击动作
  digitalWrite(LED_BUILTIN, HIGH);   // 让Arduino的LED灯亮起
  delay(20);               //延时50毫秒，（也就是让程序暂停50毫秒，点击头点击屏幕50毫秒）
  digitalWrite(8, HIGH);  //8脚输出设置为高电平，点击头停止触发点击屏幕
  digitalWrite(LED_BUILTIN, LOW);   // 让Arduino板子上的LED灯熄灭

  delay(1);             //等1000毫秒，也就是1秒后，再让程序重新运行loop()函数

}
