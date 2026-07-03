#include <WiFi.h>
#include <esp_now.h>

char mensajeRecibido[32] = "CENTRO";

#define S_IZQ 18
#define S_CEN 21
#define S_DER 4

#define PWMA 25
#define AIN1 32
#define AIN2 33

#define PWMB 13
#define BIN1 14
#define BIN2 12

#define STBY 26

int velocidadBase = 90;
int ultimaDireccion = 0;
// -1 = izquierda
//  0 = centro
//  1 = derecha

void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *incomingData,
                int len) {

  memcpy(mensajeRecibido, incomingData, len);

  Serial.print("Vision: ");
  Serial.println(mensajeRecibido);

  if (strcmp(mensajeRecibido, "CENTRO") == 0) {
    velocidadBase = 90;
  }
  else {
    velocidadBase = 60;
  }
}

void setup() {

  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  pinMode(S_IZQ, INPUT);
  pinMode(S_CEN, INPUT);
  pinMode(S_DER, INPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {

  int izq = digitalRead(S_IZQ);
  int cen = digitalRead(S_CEN);
  int der = digitalRead(S_DER);

  Serial.print(izq);
  Serial.print(" ");
  Serial.print(cen);
  Serial.print(" ");
  Serial.println(der);

  // Línea centrada
  if (izq == 0 && cen == 1 && der == 0) {

    ultimaDireccion = 0;
    avanzar();
  }

  // Línea hacia la izquierda
  else if (izq == 1) {

    ultimaDireccion = -1;
    girarIzquierda();
  }

  // Línea hacia la derecha
  else if (der == 1) {

    ultimaDireccion = 1;
    girarDerecha();
  }

  // Línea perdida
  else if (izq == 0 && cen == 0 && der == 0) {

    if (ultimaDireccion == -1) {
      girarIzquierda();
    }
    else if (ultimaDireccion == 1) {
      girarDerecha();
    }
    else {
      avanzar();
    }
  }
}

void avanzar() {

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, velocidadBase);
  analogWrite(PWMB, velocidadBase);
}

void girarIzquierda() {

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, velocidadBase + 20);
}

void girarDerecha() {

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, velocidadBase + 20);
  analogWrite(PWMB, 0);
}