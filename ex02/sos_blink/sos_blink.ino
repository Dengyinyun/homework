// 定义ESP32板载LED引脚GPIO2
const int ledPin = 2;

void setup() {
  // 串口波特率115200，和实验要求一致
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // S：短闪3次，亮200ms
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
    delay(200);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(500); // S与O之间间隔

  // O：长闪3次，亮600ms
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
    delay(600);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(500); // O与S之间间隔

  // S：短闪3次
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
    delay(200);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(2000); // 完整一轮SOS结束，停顿2秒循环
}
