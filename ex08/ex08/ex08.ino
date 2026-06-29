#include <WiFi.h>
#include <WebServer.h>

// WiFi配置（和ex07保持一致）
const char* wifiName = "Deng1314";
const char* wifiPwd = "12332145";

WebServer server(80);
const int ledPin = 2;
const int touchPin = 4;
const int touchLimit = 500;

// 全局状态变量（作业要求）
bool isArm = false;    // 布防标记
bool isAlarm = false;  // 报警锁定标记

// 完整闭合HTML字符串，不会报 unterminated raw string 错误
String webHtml = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>安防报警器</title>
<style>
button{font-size:24px;padding:15px 40px;margin:20px;}
form{display:inline-block;}
</style>
</head>
<body style="text-align:center;margin-top:120px;">
<h2>ESP32物联网安防报警器</h2>
<p>当前系统状态：<span id="state">未布防</span></p >
<form action="/arm">
<button type="submit">布防(Arm)</button>
</form>
<form action="/disarm">
<button type="submit">撤防(Disarm)</button>
</form>
</body>
</html>
)HTML";

// 主页
void handleIndex(){
  String page = webHtml;
  if(isArm){
    page.replace("未布防", "已布防");
  }
  server.send(200, "text/html", page);
}

// 布防接口
void handleArm(){
  isArm = true;
  Serial.println("系统布防完成，触摸引脚可触发报警");
  String page = webHtml;
  page.replace("未布防", "已布防");
  server.send(200, "text/html", page);
}

// 撤防接口：关闭报警、重置状态
void handleDisarm(){
  isArm = false;
  isAlarm = false;
  digitalWrite(ledPin, LOW);
  Serial.println("系统撤防，报警解除");
  String page = webHtml;
  page.replace("已布防", "未布防");
  server.send(200, "text/html", page);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);

  // 连接WiFi
  WiFi.begin(wifiName, wifiPwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功，IP：");
  Serial.println(WiFi.localIP());

  // 绑定网页路由
  server.on("/", handleIndex);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
  Serial.println("网页服务已启动");
}

void loop() {
  server.handleClient();

  // 读取触摸值
  int touchVal = touchRead(touchPin);

  // 仅在布防且未报警时，检测触摸触发报警
  if(isArm && !isAlarm){
    if(touchVal < touchLimit){
      isAlarm = true;
      Serial.println("触发入侵，锁定报警！");
    }
  }

  // 报警锁定状态：高频闪烁LED
  if(isAlarm){
    digitalWrite(ledPin, HIGH);
    delay(80);
    digitalWrite(ledPin, LOW);
    delay(80);
  }
}
