const int ledPin = 2;
unsigned long lastTime = 0;
int state = 0;
// 时长：短亮200ms，长亮600ms，间隔300ms，SOS结束停顿2000ms
const unsigned long tShort = 200;
const unsigned long tLong = 600;
const unsigned long tGap = 300;
const unsigned long tEndPause = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long now = millis();
  if (now - lastTime >= getTimeByState(state)) {
    lastTime = now;
    state++;
    // 0灭 1短亮 2灭 3短亮 4灭 5短亮 6灭
    // 7长亮 8灭 9长亮 10灭 11长亮 12灭
    // 13短亮 14灭 15短亮 16灭 17短亮 18灭 19长停顿
    // 一轮结束重置
    if(state > 19){
      state = 0;
      digitalWrite(ledPin, LOW);
    }else{
      // 亮灯状态
      if(state == 1 || state == 3 || state == 5 ||
         state == 7 || state == 9 || state == 11 ||
         state == 13 || state == 15 || state == 17){
        digitalWrite(ledPin, HIGH);
        Serial.println("LED ON");
      }else{
        digitalWrite(ledPin, LOW);
        Serial.println("LED OFF");
      }
    }
  }
}

// 根据当前阶段返回对应时长
unsigned long getTimeByState(int s){
  switch(s){
    case 1:case 3:case 5:case 13:case 15:case 17:
      return tShort;
    case 7:case 9:case 11:
      return tLong;
    case 19:
      return tEndPause;
    default:
      return tGap;
  }
}
