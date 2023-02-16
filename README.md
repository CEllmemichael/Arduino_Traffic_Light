# Arduino_traffic_light
基于Arduino的多功能智能交通信号灯的设计与实现
>对盲人语音播报，红灯结束时铃声提醒，信号灯倒计时和闯红灯语音劝阻

> 效果视频  https://www.bilibili.com/video/BV1gE411g715/?spm_id_from=333.999.0.0

# 1．系统设计思路

a: 满足基本信号灯的功能

1）绿灯常亮6秒，绿灯闪烁3秒，黄灯常亮3秒，红灯常亮5秒，红灯闪烁3秒，回到绿灯常亮状态。

2）要求用数码管显示时间的倒计时。

3）如果有按键按下，表示有紧急车辆通过（救火车等），亮红灯，蜂鸣器响，如果另外一个按键按下则恢复正常。

b：体现人文关怀，增加语音提示，使交通灯能通过声音使盲人也可以使用。

c: 注重提醒行人交通安全，减少交通事故发生, 在绿灯快要结束时发出提示声音提醒行人加快步伐快速通过, 通过超声波判断是否闯红灯，并通过警示灯发出警告。

# 2．系统硬件实现
数字输入输出端口0---13

模拟输入端口A0—A5

3.3V   5V电压输出
Tx rx 与其他单片机的串口

LED灯长脚正极，短脚负极

定义11，12，13接口为红绿黄三个led的接口

0-8为显示管的接口，10为蜂鸣器接口

A0，A1为超声波测距仪接口

A2为LED警示灯接口

A3，A4为按键接口

使接地接口和5V接口质于面包板的+，-接口使各仪器供电和接地直接在面包板上连接即可

通过计算各个仪器在5V电压下可以正常运行；
以下两图为电路连接图和实物连接图

> 当时做的时候画的图过于草率

![](https://user-images.githubusercontent.com/66575985/219271504-135aaa40-ce51-4205-821b-23ae5a14fa41.png)

                                                图1 电路原理图

![图片](https://user-images.githubusercontent.com/66575985/219271545-ca4ec164-5771-46e8-a3bc-8932775d9faf.png)

                                                图2 实物连接图
 

![图片](https://user-images.githubusercontent.com/66575985/219271671-db9be2a4-62ed-421e-881e-0b5de9309d10.png)

                                                图3 显示管端口连接图


3．系统软件实现
1.基本函数解释
Reset:程序无论到了哪一步都恢复到开始程序的那一步
PinMode:定义输入输出
pinMode(13,OUTPUT):13端口是输出端口；
Digitalwrite(13,LOW)：13输出低电平；灭；
LOW:低电平【没有，灭】（（（0
HIGH：高电平【有，不灭】（（（1-----3.3/5V 
Digitalwrite:控制高低电平
Delay{毫秒}
Digitalread读取电平
Eg:IntX=digitalread(2)
模拟信号的实质就是电压，arduino的模拟端口可以采集0-5V的电压，并且按比例以1-1023表示，机5V=1023；
模拟信号的传感器也是以电压形式传输信号的，
模拟电路的输入函数analogRead(0);
2.语音信号实现
使盲人在无法看到信号灯使一样可以通过路口
使用for循环嵌套语音输出倒计时和红路灯常亮
for (int x = 0; x < 60; x++) //循环60次，统计60次音符播放时间为6秒
  { digitalWrite(g, 0);使红灯常亮
    int a = 5 - (x / 10);
    deal(dofly_DuanMa[a]);通过函数实现倒计时数值与for循环和时间的关系
    tone(tonePin, tune[x]); //依次播放tune数组元素，即每个音符
delay(100 * duration[x]); //每个音符持续的时间，即节拍duration，    noTone(tonePin);//停止当前音符，进入下一音符
3. 路灯将结束时提示铃声
使行人在信号灯快结束时有意识地加快步伐预防交通事故
在闪烁循环中插入蜂鸣函数使其延迟时间和灯光延迟时间之和与for循环变量的乘积等于闪烁时长
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
# 4. 声波测距提示不要闯红灯
初始声波发出器接受器并通过函数换算成厘米单位
digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
  distanceCm = duration1 * 0.034 / 2;
if (distanceCm <= 50)当测距小于50厘米时实现该程序
    {
      digitalWrite(LED, LOW);
    }
# 5.铃声播放
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

for (int x = 0; x < 60; x++) //循环音符的次数
  { digitalWrite(g, 0);
    int a = 5- (x / 10);
    deal(dofly_DuanMa[a]);
    tone(tonePin, tune[x]); //依次播放tune数组元素，即每个音符
    delay(100 * duration[x]); //每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快
    noTone(tonePin);//停止当前音符，进入下一音符
 


#6．参考文献

【1】CSDN博主「TonyIOT」葫芦娃音调部分
