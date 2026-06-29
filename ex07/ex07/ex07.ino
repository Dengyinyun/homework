#include <WiFi.h>
#include <WebServer.h>

// 修改成你自己的WiFi名称和密码
const char* wifiName = "Deng1314";
const char* wifiPwd = "12332145";

WebServer server(80);
const int ledPin = 2;   // LED接GPIO2
int brightness = 0;     // 亮度范围0~255

// 网页界面代码（滑动条+实时数值）
String webHtml = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>网页无级调光</title>
</head>
<body style="text-align:center;margin-top:120px;font-size:22px;">
<h2>ESP32 滑动条调光器</h2>
<input type="range" min="0" max="255" value="0" id="lightSlider" style="width:85%;height:35px;">
<p>当前亮度值：<span id="num">0</span></p >
<script>
let slider = document.getElementById("lightSlider");
let showNum = document.getElementById("num");
// 拖动滑动条实时发送数值给ESP32
slider.oninput = function(){
  let val = this.value;
  showNum.innerText = val;
  fetch("/setBright?val="+val);
}
</script>
</body>
</html>
)HTML";

// 首页路由，返回网页
void handleIndex(){
  server.send(200, "text/html", webHtml);
}

// 接收滑动条亮度参数
void handleBright(){
  if(server.hasArg("val")){
    brightness = server.arg("val").toInt();
    analogWrite(ledPin, brightness);
  }
  server.send(200, "text/plain", "success");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
  Serial.begin(115200);

  // 连接WiFi
  WiFi.begin(wifiName, wifiPwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功，设备IP：");
  Serial.println(WiFi.localIP());

  // 绑定网页接口
  server.on("/", handleIndex);
  server.on("/setBright", handleBright);
  server.begin();
}

void loop() {
  server.handleClient();
}
