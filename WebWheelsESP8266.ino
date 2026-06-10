#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h> 

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81); 

// Motor A (Left side)
const int IN1 = 14; // NodeMCU D5
const int IN2 = 12; // NodeMCU D6

// Motor B (Right side)
const int IN3 = 13; // NodeMCU D7
const int IN4 = 15; // NodeMCU D8

// --- Webpage HTML (CSS + WebSocket JavaScript) ---
void handleRoot() {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0'>";
  html += "<title>Wi-Fi RC Car (WebSocket)</title>";
  html += "<style>body{font-family:Arial;text-align:center;background-color:#222;color:#fff;margin-top:20px; user-select: none; -webkit-user-select: none; touch-action: manipulation;}";
  html += ".btn{width:80px;height:80px;font-size:24px;margin:10px;border-radius:15px;border:none;background-color:#4CAF50;color:white;box-shadow:0 5px #2e6c31; cursor:pointer;}";
  html += ".btn:active{box-shadow:0 2px #2e6c31;transform:translateY(3px);}";
  html += ".stop{background-color:#f44336;box-shadow:0 5px #a62a22;}";
  html += ".stop:active{box-shadow:0 2px #a62a22;}";
  html += ".row{display:flex;justify-content:center;}</style>";
  
  // WebSocket JavaScript Setup
  html += "<script>";
  html += "var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);";
  html += "function cmd(dir) { connection.send(dir); }";
  // Prevent default context menus on long presses for mobile
  html += "window.oncontextmenu = function(event) { event.preventDefault(); event.stopPropagation(); return false; };";
  html += "</script></head>";
  
  html += "<body><h2>Zero-Lag RC Car</h2>";
  
  // Added onmouseup and ontouchend to automatically stop the car when the button is released!
  html += "<div class='row'><button class='btn' ontouchstart='cmd(\"F\")' onmousedown='cmd(\"F\")' ontouchend='cmd(\"S\")' onmouseup='cmd(\"S\")'>⬆️</button></div>";
  html += "<div class='row'>";
  html += "<button class='btn' ontouchstart='cmd(\"L\")' onmousedown='cmd(\"L\")' ontouchend='cmd(\"S\")' onmouseup='cmd(\"S\")'>⬅️</button>";
  html += "<button class='btn stop' ontouchstart='cmd(\"S\")' onmousedown='cmd(\"S\")'>STOP</button>";
  html += "<button class='btn' ontouchstart='cmd(\"R\")' onmousedown='cmd(\"R\")' ontouchend='cmd(\"S\")' onmouseup='cmd(\"S\")'>➡️</button>";
  html += "</div>";
  html += "<div class='row'><button class='btn' ontouchstart='cmd(\"B\")' onmousedown='cmd(\"B\")' ontouchend='cmd(\"S\")' onmouseup='cmd(\"S\")'>⬇️</button></div>";
  
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// --- Motor Control Functions ---
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
}
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);  
}
void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// --- WebSocket Event Handler ---
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    char dir = (char)payload[0]; 
    
    if (dir == 'F') moveForward();
    else if (dir == 'B') moveBackward();
    else if (dir == 'L') turnLeft();
    else if (dir == 'R') turnRight();
    else if (dir == 'S') stopCar();
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  stopCar(); 

  // --- THE MAGIC BULLET FOR LATENCY ---
  // Disable Wi-Fi sleep mode to ensure the ESP8266 never drops the connection
  WiFi.setSleepMode(WIFI_NONE_SLEEP); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start HTTP Server
  server.on("/", handleRoot);
  server.begin();

  // Start WebSocket Server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent); 
}

void loop() {
  server.handleClient(); 
  webSocket.loop();      
}