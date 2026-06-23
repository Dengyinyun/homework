const int ledPin = 2;
unsigned long lastTime = 0;
const unsigned long interval = 500;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println(ledState ? "LED ON" : "LED OFF");
  }
}
