//多功能智能交通灯程序
//鲁东大学
//********
//魏树鸿
//2019/12/25
//---------------------显示管部分---------------------------------
int LEDCount = 8;
const unsigned char dofly_DuanMa[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
int LEDPins[] = {    0, 1, 2, 3, 4, 5, 6, 7, };
const int trigPin = A0;
const int echoPin = A1;
int LED = A3;
int buttonApin = A4;
int buttonBpin = A5;
long duration1;
int distanceCm;
//声音部分代码------------------------------------------------------//截取网络中歌曲代替提示音

//对应音符和频率值
#define NOTE_D0 -1
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112

#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

int tune[] =
{
  NOTE_DH1, NOTE_D6, NOTE_D5, NOTE_DH1, NOTE_D6, NOTE_D0,
  NOTE_D1, NOTE_D1, NOTE_D3,
  NOTE_D1, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D6,
  NOTE_D5, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_DH1, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D6,
  NOTE_D5, NOTE_D1, NOTE_D2, NOTE_D0,
  NOTE_D7, NOTE_D7, NOTE_D5, NOTE_D3,
  NOTE_D5,
  NOTE_DH1, NOTE_D0, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D5, NOTE_D6, NOTE_D6,
  NOTE_D0, NOTE_D5, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_DH1, NOTE_D0, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D5, NOTE_D6, NOTE_D6,
};

//曲子的节拍，即音符持续时间
float duration[] =
{
  1, 1, 1, 1, 1, 1,
  1, 1, 1 ,
  1, 1, 1 , 1,
  1, 1, 1, 1, 1,
  1, 1, 1 , 1,
  1, 1, 1, 1, 1 ,
  1, 1, 1 , 1,
  1 , 1, 1, 1,
  1 ,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
};

int length;//定义一个变量用来表示共有多少个音符
int tonePin = 10; //蜂鸣器的pin
//交通灯部分代码----------------------------------------------------------------
int g = 11;
int r = 12;
int y = 13;

void setup() {//初始值设定（setup)
  //声音部分-------------------------------------------------------------------
  pinMode(tonePin, OUTPUT); //设置蜂鸣器的pin为输出模式
  //交通灯部分-----------------------------------------------------------------
  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  digitalWrite(g, 1);
  digitalWrite(r, 1);
  digitalWrite(y, 1);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int thisLED = 0; thisLED < LEDCount; thisLED++)
  {
    pinMode(LEDPins[thisLED], OUTPUT);
  }
}
void deal(unsigned char value) {
  for (int i = 0; i < 8; i++)
    digitalWrite(LEDPins[i], !bitRead(value, i));
  // put your setup code here, to run once:
  pinMode(A4, INPUT_PULLUP);  // 按钮设置为input的状态
  pinMode(A5, INPUT_PULLUP);  // 按钮设置为input的状态
}

void loop()//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
{
  //------------------------------按键部分
for(int m=0:digitalRead(buttonApin) == LOW;m++)
 {digitalWrite(g, 1);
  digitalWrite(r, 0);
  digitalWrite(y, 1);
  if(digitalRead(buttonBpin) == LOW)
break;
 } 

    //---------------------------在绿灯亮起的6秒钟内，提醒盲人声音同时亮起【此处使用音乐代替】，显示管进行倒计时
    for (int x = 0; x < 60; x++) //循环音符的次数
    { digitalWrite(g, 0);
      int a = 5 - (x / 10);
      deal(dofly_DuanMa[a]);
      tone(tonePin, tune[x]); //依次播放tune数组元素，即每个音符
      delay(100 * duration[x]); //每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快
      noTone(tonePin);//停止当前音符，进入下一音符
    }
    //------------------------绿灯闪烁3秒，使用蜂鸣音提醒行人加快步伐，快速通过交通路口
    for (int i = 0; i < 6; i++)
    { digitalWrite(g, 1);
      delay(125);
      digitalWrite(tonePin, 1);
      delay(125);
      digitalWrite(g, 0);
      delay(125);
      digitalWrite(tonePin, 0);
      delay(125);
    }
    //---------------------黄灯长亮3秒
    digitalWrite(g, 1);
    digitalWrite(y, 0);
    delay(3000);
    digitalWrite(y, 1);
    //--------------------红灯常亮5秒，提示音【此处使用倒序音乐代替且做区别】响，提醒盲人不要通过
//------------------------------超声波部分-
    digitalWrite(trigPin, LOW);
    delay(2);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);
    duration1 = pulseIn(echoPin, HIGH);
    distanceCm = duration1 * 0.034 / 2;
    for (int x = 50; x > 0; x--) //循环音符的次数
    { digitalWrite(r, 0);
      int b = x / 10;
      if (distanceCm <= 50)
      {
        digitalWrite(LED, LOW);
      }
      deal(dofly_DuanMa[b]);
      tone(tonePin, tune[x]); //依次播放tune数组元素，即每个音符
      delay(100 * duration[x]); //每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快
      noTone(tonePin);//停止当前音符，进入下一音符
    }
    digitalWrite(r, 1);
    //-------------------红灯闪烁
    for (int i = 0; i < 6; i++)
    { digitalWrite(r, 1);
      delay(250);
      digitalWrite(r, 0);
      delay(250);
    }
    digitalWrite(r, 1);
    // put your main code here, to run repeatedly:
  }
}
