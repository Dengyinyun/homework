// ex05 多档位呼吸灯（灵敏不卡顿，和你ex04手感一致）
#define TOUCH_PIN 4

#define LED_PIN 2
#define EXT_ISR_MODE 0

int threshold = 800;
int touchValue;
int speedGear = 1;

int lastTouch = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  touchValue = touchRead(TOUCH_PIN);
  lastTouch = (touchValue < threshold) ? 1 : 0;
}

void loop() {
  touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);
  int currentTouch = (touchValue < threshold) ? 1 : 0;

  // 触摸瞬间切换档位
  if (lastTouch == 0 && currentTouch == 1) {
    speedGear += 1;
    if (speedGear > 3) speedGear = 1;
    Serial.print("切换档位：");
    Serial.println(speedGear);
  }
  lastTouch = currentTouch;

  int step, delayTime;
  switch (speedGear) {
    case 1: step = 1;  delayTime = 20; break;
    case 2: step = 3;  delayTime = 10; break;
    case 3: step = 6;  delayTime = 3;  break;
  }

  // 渐亮
  for (int val = 0; val <= 255; val += step) {
    analogWrite(LED_PIN, val);
    delay(delayTime);
  }
  // 渐暗
  for (int val = 255; val >= 0; val -= step) {
    analogWrite(LED_PIN, val);
    delay(delayTime);
  }
}
