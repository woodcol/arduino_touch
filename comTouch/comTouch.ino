/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#define D8 8

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //  Serial.end();
  delay(100);
  pinMode(D8, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(1);
  digitalWrite(D8, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
}

// the loop function runs over and over again forever

char tmp = '0';

void loop() {
  
  if (Serial.available() > 0) {
    delay(5); // 等待数据传完
    tmp = Serial.read();
    delay(3);
    Serial.write(tmp);
    delay(3);
  }else{
    tmp = '0';
  }
 switch(tmp){
    case '1':
    {
      //第一个引脚，点一下
      digitalWrite(D8, LOW);
      delay(35);
      digitalWrite(D8, HIGH);
      break;
    }
    case '2': 
    {
      //第二个引脚，点一下
      digitalWrite(D8, LOW);
      delay(35);
      digitalWrite(D8, HIGH);
      break;
    }
    default: { 
     digitalWrite(D8, HIGH);
     break;
    }
 }
}
