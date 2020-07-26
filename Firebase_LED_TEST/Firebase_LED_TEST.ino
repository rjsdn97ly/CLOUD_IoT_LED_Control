#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "fir-led-control-21b25.firebaseio.com"
#define FIREBASE_AUTH "IT80XrfVOU79FzCzDRuTpDjkpbhzJUvEZFXjQfxU"

#define WIFI_SSID "test"
#define WIFI_PASSWORD "12345678"

int redLed = D4;
int blueLed = D3;

String red_fireStatus = "";
String blue_fireStatus = "";

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  WiFi.begin(WIFI_SSID);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // firebase에 연결
  Firebase.setString("RED_LED_STATUS", "OFF"); //초기 LED 상태를 OFF로 설정
  Firebase.setString("BLUE_LED_STATUS", "OFF");
}
void loop()
{
  
  delay(500);
  ledOn();
  delay(500);
  
}

void ledOn() {
  // Firebase 데이터베이스로 부터 LED 상태 값 읽음
  red_fireStatus = Firebase.getString("RED_LED_STATUS"); 
  // Firebase 데이터베이스로 부터 받은 LED 상태 값이 “ON”이면 LED 켜기
  if (red_fireStatus == "ON") { 
    // Serial Monitor에 “Led Turned ON” 문자열 출력
    Serial.println("RED Led Turned ON"); 
    digitalWrite(redLed, HIGH); // LED ON
    // Firebase 데이터베이스로 부터 LED 상태 값 읽음
  } else if (red_fireStatus == "OFF") { 
    // Serial Monitor에 “Led Turned OFF” 문자열 출력
    Serial.println("RED Led Turned OFF"); 
    digitalWrite(redLed, LOW); // LED OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }


  blue_fireStatus = Firebase.getString("BLUE_LED_STATUS"); // Firebase 데이터베이스로 부터 LED 상태 값 읽음
  if (blue_fireStatus == "ON") { // Firebase 데이터베이스로 부터 받은 LED 상태 값이 “ON”이면 LED 켜기
    Serial.println("BLUE Led Turned ON"); // Serial Monitor에 “Led Turned ON” 문자열 출력
    digitalWrite(blueLed, HIGH); // LED OFF
  } else if (blue_fireStatus == "OFF") { // Firebase 데이터베이스로 부토 LED 상태 값 읽음
    Serial.println("BLUE Led Turned OFF"); // Serial Monitor에 “Led Turned OFF” 문자열 출력
    digitalWrite(blueLed, LOW); // LED OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }
}
