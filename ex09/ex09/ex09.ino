#include <WiFi.h>
#include <WebServer.h>

const char* wifiName = "Deng1314";
const char* wifiPwd = "12332145";
WebServer server(80);
const int touchPin = 4;

void handleRoot() {
  int touchValue = touchRead(touchPin);
  // meta标签自动0.2秒刷新整页，不用任何独立接口
  String htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta http-equiv="refresh" content="0.2">
<style>
body{text-align:center;margin-top:100px;font-size:30px;}
#num{font-size:90px;color:red;font-weight:bold;}
</style>
</head>
<body>
<h2>ESP32 触摸传感器实时仪表盘</h2>
<p>当前触摸原始数值：</p >
<div id="num>)HTML" + String(touchValue) + R"HTML(</div>
</body>
</html>
)HTML";
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);
  // 连接WiFi
  WiFi.begin(wifiName, wifiPwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.print("\nESP32 IP地址：");
  Serial.println(WiFi.localIP());
  // 只注册一条根路由，无独立数据接口，彻底避开404/连接超时
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web仪表盘启动完成");
}

void loop() {
  server.handleClient();
  // 串口实时打印触摸值，验证硬件读取正常
  Serial.print("触摸读数：");
  Serial.println(touchRead(touchPin));
  delay(200);
}
