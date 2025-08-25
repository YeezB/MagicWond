#include <esp_now.h>
#include <WiFi.h>
#include "unihiker_k10.h"

//对黑帽子和橘帽子K10上传时候需要打开相应宏定义，注释掉另一个宏定义
#define blackHAT
//#define orangeHAT

// 创建对象
UNIHIKER_K10 k10;
uint8_t      screen_dir=2;
static int status = 0;
float startTime = 0;
float endTime = 0;

//MAC
uint8_t MAC1[] = {0x7C, 0xDF, 0xA1, 0xFE, 0xEF, 0xC4};//魔法棒
//uint8_t MAC0[] = {0x7C, 0xDF, 0xA1, 0xFD, 0x67, 0xB8};//黑帽子（英国BETT）
uint8_t MAC2[] = {0x68, 0xB6, 0xB3, 0x22, 0x06, 0x34};//橙帽子
uint8_t MAC0[] = {0x34, 0xCD, 0xB0, 0x0D, 0xB8, 0x80};//黑帽子

typedef struct struct_message {
  uint8_t ID;
  char data[50];
} struct_message;
struct_message sendData;
struct_message recvData;
esp_now_peer_info_t peerInfo;

int recv_action;

// Callback when data is sent   发送回调函数
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", 
           mac_addr[0], mac_addr[1], mac_addr[2], 
           mac_addr[3], mac_addr[4], mac_addr[5]);
  if(status == ESP_NOW_SEND_SUCCESS){
    Serial.print("Send Success to ");
    Serial.println(macStr);
  }else{
    Serial.print("Send Fail to ");
    Serial.println(macStr);
  }
}

/* 
Callback when data is received   接收回调函数
ACTION 1 表示画圆，让两个帽子停下
ACTION 2 表示左右摇晃，让黑色帽子动 
ACTION 3 表示上下晃动，让橘色帽子动
两个HAT的/需要上传不同的程序，程序切换由该程序开头的#define宏定义实现
*/
void OnDataRecv(const uint8_t * mac, const uint8_t *Data, int len) {
  memcpy(&recvData, Data, sizeof(recvData));
  Serial.println("=========");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println(recvData.ID);
  Serial.println(recvData.data);
  if (String(recvData.data) == "Action_2") {
      recv_action = 1;
      //k10.canvas->canvasText("Action_2", 0, 0, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
      #ifdef blackHAT
      if(status = 0)
      {
        digitalWrite(P0, HIGH);
        status = 1;
      }
      else if(status = 1)
      {
        digitalWrite(P0, LOW);
        delay(800);
        digitalWrite(P0, HIGH);
        status = 1;
      }
      #endif
  } else if (String(recvData.data) == "Action_1") {
      recv_action = 2;
      //k10.canvas->canvasText("Action_1", 0, 0, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
      digitalWrite(P0, LOW);
      status = 0;
  } else if (String(recvData.data) == "Action_3") {
      recv_action = 3;
      //k10.canvas->canvasText("Action_3", 0, 0, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
      #ifdef orangeHAT
      if(status = 0)
      {
        digitalWrite(P0, HIGH);
        status = 1;
      }
      else if(status = 1)
      {
        digitalWrite(P0, LOW);
        delay(800);
        digitalWrite(P0, HIGH);
      }
      status = 0;
      #endif
  }
  Serial.println(recv_action);
  //k10.canvas->updateCanvas();
  Serial.println("---------");
}

void setup() {
  Serial.begin(9600);
  k10.begin();
  pinMode(P0, OUTPUT);
  //k10.initScreen(screen_dir);
  //k10.creatCanvas();
  //k10.setScreenBackground(0xFFFFFF);
  //k10.rgb->write(-1, 0x0000FF);
  WiFi.mode(WIFI_STA);
  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing");
    return;
  }

  //注册发送回调函数
  esp_now_register_send_cb(OnDataSent);

  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //注册MAC1设备
  memcpy(peerInfo.peer_addr, MAC1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer0");
    return;
  }

  //注册接收回调函数
  esp_now_register_recv_cb(OnDataRecv);
  //k10.rgb->write(-1, 0x000000);

  delay(3000);
  digitalWrite(P0, HIGH);
  delay(1000);
  digitalWrite(P0, LOW);
}

void loop() {
  if(digitalRead(P0) == HIGH)
  {
    endTime = millis();
    if(endTime - startTime >= 15000)
    {
      startTime = endTime;
      delay(500);
      digitalWrite(P0, LOW);
      delay(800);
      digitalWrite(P0, HIGH);
    }
  }
  else if(digitalRead(P0) == LOW)
  {
    startTime = millis();
  }
  Serial.print("Start Time: ");
  Serial.println(startTime);
  Serial.print("End Time: ");
  Serial.println(endTime);
}