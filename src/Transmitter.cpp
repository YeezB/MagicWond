#include <esp_now.h>
#include <WiFi.h>
#include "unihiker_k10.h"
#include <DFRobot_NeoPixel.h>
#include <magic-xhl_inferencing.h> //Need to change to your own library

UNIHIKER_K10 k10;
DFRobot_NeoPixel neoPixel_P1;
uint8_t      screen_dir=2;

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
int x,y,z,v;
int mind_n_test = 0;
int i = 0;
int max_probability_class = 0; 


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

// Callback when data is received 
void OnDataRecv(const uint8_t * mac, const uint8_t *Data, int len) {
  memcpy(&recvData, Data, sizeof(recvData));
  Serial.println("=========");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println(recvData.ID);
  Serial.println(recvData.data);
  Serial.println("---------");
}

static float features[100];

int featureIndex = 0;

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void print_inference_result(ei_impulse_result_t result);

void setup()
{
    Serial.begin(9600);
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0xFFFFFF);
    k10.rgb->write(-1, 0xFF0000);
    k10.initSDFile();
    k10.canvas->canvasDrawImage(0, 0, "S:/Fail.png");
    k10.canvas->updateCanvas();
    neoPixel_P1.begin(2, 7);
    pinMode(1, INPUT);
    WiFi.mode(WIFI_STA);
    //Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing");
        return;
    }

    //Register the send callback function
    esp_now_register_send_cb(OnDataSent);

    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    //Register MAC0 devices
    memcpy(peerInfo.peer_addr, MAC0, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer0");
        return;
    }
    //Register MAC2 devices
    memcpy(peerInfo.peer_addr, MAC2, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer0");
        return;
    }

    //Register the receive callback function
    esp_now_register_recv_cb(OnDataRecv);
    sendData.ID = 1;
    k10.rgb->write(-1, 0x000000);
}

void loop()
{
    if (digitalRead(1)) {
        Serial.println("====================");
        k10.canvas->canvasDrawImage(0, 0, "S:/Effective.png");
        k10.canvas->updateCanvas();
        featureIndex = 0;
        neoPixel_P1.setRangeColor(0, 13, 0xFF0000);
        delay(100);
        
    while (featureIndex < 100) {
      if ((k10.isGesture(TiltForward))) {
        mind_n_test = 1;
      }
      else {
        if ((k10.isGesture(TiltBack))) {
          mind_n_test = 2;
          }
          else {
            if ((k10.isGesture(TiltLeft))) {
              mind_n_test = 3;
              }
              else {
                if ((k10.isGesture(TiltRight))) {
                  mind_n_test = 4;
                  }
                  else {
                    if ((k10.isGesture(ScreenUp))) {
                      mind_n_test = 5;
                      }
                      else {
                        if ((k10.isGesture(ScreenDown))) {
                          mind_n_test = 6;
                          }
                          else {
                            mind_n_test = 0;
                            }
                          }
                        }
                      }
                    }
                  }
    // Store data in the features array
    //Serial.print(features[featureIndex]);Serial.print(","); 
    features[featureIndex++] = mind_n_test;
    //Serial.print(features[featureIndex]);Serial.print(","); 
    features[featureIndex++] = k10.getAccelerometerX();
    //Serial.print(features[featureIndex]);Serial.print(","); 
    features[featureIndex++] = k10.getAccelerometerY();
    //Serial.print(features[featureIndex]);Serial.print(","); 
    features[featureIndex++] = k10.getAccelerometerZ();
    //Serial.print(features[featureIndex]);Serial.print(","); 
    features[featureIndex++] = k10.getStrength();
    delay(100);
    }

        ei_printf("Edge Impulse standalone inferencing (Arduino)\n");

        if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
            ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
            delay(1000);
            return;
        }

        ei_impulse_result_t result = { 0 }; 

        signal_t features_signal;
        features_signal.total_length = sizeof(features) / sizeof(features[0]);
        features_signal.get_data = &raw_feature_get_data;

        EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
        if (res != EI_IMPULSE_OK) {
            ei_printf("ERR: Failed to run classifier (%d)\n", res);
            return;
        }

        ei_printf("run_classifier returned: %d\r\n", res);
        print_inference_result(result);
        //neoPixel_P1.setRangeColor(0, 6, 0x00FF00);
        // for (int index = 0; index < 7; index++) {
        //     neoPixel_P1.shift(1);
        //     delay(20);
        // }
        if(max_probability_class == 1){
            strcpy(sendData.data, "Action_1");
            for (int i = 0; i < 7; i++) {
              neoPixel_P1.setRangeColor(i, i, 0x00FF00);
              neoPixel_P1.setRangeColor(13-i, 13-i, 0x00FF00);
              delay(20);
            }
            esp_now_send(0, (uint8_t *)&sendData, sizeof(sendData));  
            k10.canvas->canvasDrawImage(0, 0, "S:/Action_1.png");    
            Serial.println("esp_now_send");
            
        }else if(max_probability_class == 2){
            strcpy(sendData.data, "Action_2");
            for (int i = 0; i < 7; i++) {
              neoPixel_P1.setRangeColor(i, i, 0x00FF00);
              neoPixel_P1.setRangeColor(13-i, 13-i, 0x00FF00);
              delay(20);
            }
            esp_now_send(0, (uint8_t *)&sendData, sizeof(sendData));
            k10.canvas->canvasDrawImage(0, 0, "S:/Action_2.png"); 
            Serial.println("esp_now_send");
        }else if(max_probability_class == 3){
            strcpy(sendData.data, "Action_3");
            for (int i = 0; i < 7; i++) {
              neoPixel_P1.setRangeColor(i, i, 0x00FF00);
              neoPixel_P1.setRangeColor(13-i, 13-i, 0x00FF00);
              delay(20);
            }
            esp_now_send(0, (uint8_t *)&sendData, sizeof(sendData));
            k10.canvas->canvasDrawImage(0, 0, "S:/Action_3.png");
            Serial.println("esp_now_send");
        }  
        k10.canvas->updateCanvas();
        delay(2000);
        k10.canvas->canvasDrawImage(0, 0, "S:/Fail.png");
        k10.canvas->updateCanvas();
        neoPixel_P1.clear();
    }
}


void print_inference_result(ei_impulse_result_t result) {
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }
#else
    ei_printf("Predictions:\r\n");
    float max_value = 0.0;
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
        if (result.classification[i].value > max_value) {
            max_value = result.classification[i].value;
            max_probability_class = i + 1; // 更新为当前类别（从1开始）
        }
    }

    ei_printf("Max Probability Class: %d\n", max_probability_class);
#endif

#if EI_CLASSIFIER_HAS_ANOMALY
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif
}
