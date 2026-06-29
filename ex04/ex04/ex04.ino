// 定义触摸引脚 (T0对应GPIO4)
#define TOUCH_PIN 4
// 定义LED引脚 (ESP32 DevKit板载LED通常是GPIO2)
#define LED_PIN 2
// 中断模式设置：0为轮询模式，1为中断模式
#define EXT_ISR_MODE 0

int threshold = 800; 
int touchValue;

// 作业要求布尔型LED状态变量
bool ledState = false;
int lastTouch = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  
  // 上电同步触摸初始状态
  touchValue = touchRead(TOUCH_PIN);
  lastTouch = (touchValue < threshold) ? 1 : 0;
}

void loop() {
  touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  int currentTouch = (touchValue < threshold) ? 1 : 0;

  // 边沿检测：仅松开→触摸瞬间翻转LED
  if (lastTouch == 0 && currentTouch == 1) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println("=== 切换LED ===");
  }

  lastTouch = currentTouch;
  delay(100);
}
