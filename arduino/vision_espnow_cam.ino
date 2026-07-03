#include "esp_camera.h"
#include <WiFi.h>
#include <esp_now.h>

// ===== AI THINKER =====
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5

#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

uint8_t receiverMac[] = {0x64, 0xB7, 0x08, 0xCE, 0x9E, 0x8C};
char ultimaDireccion[20] = "CENTRO";

void setup() {

  Serial.begin(115200);

  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;

  config.pixel_format = PIXFORMAT_GRAYSCALE;

  //config.frame_size = FRAMESIZE_240X240;

  config.frame_size = FRAMESIZE_QQVGA;

  config.fb_location = CAMERA_FB_IN_DRAM;

  config.fb_count = 1;

 esp_err_t err = esp_camera_init(&config);

if (err != ESP_OK) {

  Serial.print("Error camara: ");
  Serial.println(err);

  return;
}

Serial.print("PSRAM encontrada: ");
Serial.println(psramFound());

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr, receiverMac, 6);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  Serial.println("VISION LISTA");
}

void loop() {

  camera_fb_t *fb = esp_camera_fb_get();

  if (!fb) {
    Serial.println("Error capturando");
    delay(500);
    return;
  }

  Serial.print("Ancho=");
  Serial.print(fb->width);

  Serial.print(" Alto=");
  Serial.println(fb->height);

  int fila = 30;
  Serial.print("Fila=");
Serial.println(fila);

int izq = 255;
int cen = 255;
int der = 255;

for(int x=0; x<50; x++){
  if(fb->buf[fila * fb->width + x] < izq)
    izq = fb->buf[fila * fb->width + x];
}

for(int x=55; x<105; x++){
  if(fb->buf[fila * fb->width + x] < cen)
    cen = fb->buf[fila * fb->width + x];
}

for(int x=110; x<160; x++){
  if(fb->buf[fila * fb->width + x] < der)
    der = fb->buf[fila * fb->width + x];
}

  Serial.print("I=");
  Serial.print(izq);

  Serial.print(" C=");
  Serial.print(cen);

  Serial.print(" D=");
  Serial.println(der);

  char mensaje[20];

if (izq < 90) {

  strcpy(mensaje, "DERECHA");
  strcpy(ultimaDireccion, "DERECHA");

}
else if (cen < 90) {

  strcpy(mensaje, "CENTRO");
  strcpy(ultimaDireccion, "CENTRO");

}
else if (der < 90) {

  strcpy(mensaje, "IZQUIERDA");
  strcpy(ultimaDireccion, "IZQUIERDA");

}
else {

  strcpy(mensaje, ultimaDireccion);

}

  esp_now_send(receiverMac,
               (uint8_t *)mensaje,
               strlen(mensaje) + 1);

  Serial.println(mensaje);

  esp_camera_fb_return(fb);

  delay(200);
}