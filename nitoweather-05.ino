cpp
Copy code
/*
 * Proyecto: Monitor de Sensor con ESP32 y Pantalla OLED
 * Versión: 0.5
 * Autor: Nito
 * Fecha: 6 de Julio de 2024
 * 
 * Descripción:
 * Este proyecto utiliza un ESP32 para leer datos de un sensor HX710B, mostrar 
 * estos datos en una pantalla OLED de 128x64 y enviar los datos a un bot de Telegram.
 * 
 * Instrucciones de Uso:
 * 1. Conecta el ESP32 a una fuente de alimentación adecuada.
 * 2. Conecta la pantalla OLED y el sensor HX710B al ESP32 según los pines configurados:
 *    - DOUT del HX710B al pin 4 del ESP32
 *    - SCK del HX710B al pin 5 del ESP32
 *    - Pantalla OLED al bus I2C (SDA a pin 21, SCL a pin 22)
 * 3. Configura las credenciales de tu bot de Telegram:
 *    - Reemplaza `TU_BOT_TOKEN` con el token de tu bot de Telegram.
 *    - Reemplaza `TU_CHAT_ID` con el ID de chat de Telegram al que deseas enviar los mensajes.
 * 4. Sube el código al ESP32 utilizando el IDE de Arduino.
 * 5. Al iniciar, el ESP32 se conectará a una red WiFi utilizando WiFiManager.
 * 6. La pantalla OLED mostrará "GreenNito" junto con la fecha y hora actual al inicio.
 * 7. El ESP32 leerá el sensor periódicamente y actualizará la pantalla OLED con los datos del sensor.
 * 8. Los datos del sensor se enviarán a Telegram cada 10 segundos.
 * 
 * Historial de Versiones:
 * - Versión 0.1: Inicialización del proyecto.
 * - Versión 0.2: Integración del bot de Telegram.
 * - Versión 0.3: Optimización del código utilizando millis() en lugar de delay().
 * - Versión 0.4: Optimización del código utilizando X509List cert para la conexión TLS con Telegram.
 * - Versión 0.5: Adaptación y optimización del código para ESP32 WROOM.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "HX710B.h"

// Configuración del OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuración del HX710B
#define DOUT  4
#define SCK   5
HX710B hx710b(DOUT, SCK);

// Configuración del bot de Telegram
#define BOT_TOKEN "TU_BOT_TOKEN"
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// Configuración de NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

unsigned long lastSensorRead = 0;
unsigned long sensorInterval = 500;

unsigned long lastTelegramSend = 0;
unsigned long telegramInterval = 10000;

void setup() {
  Serial.begin(115200);

  // Inicialización del OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al inicializar el OLED"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Configuración de WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP32_AP");
  Serial.println("Conectado a WiFi");

  // Inicialización del cliente NTP
  timeClient.begin();
  timeClient.update();

  // Obtener la fecha y hora actual
  String formattedTime = timeClient.getFormattedTime();
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);
  String currentDate = String(timeInfo->tm_mday) + "/" + String(timeInfo->tm_mon + 1) + "/" + String(timeInfo->tm_year + 1900);

  // Mostrar "GreenNito" y la fecha y hora en el OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("GreenNito");
  display.setTextSize(1);
  display.print("Fecha: ");
  display.println(currentDate);
  display.print("Hora: ");
  display.println(formattedTime);
  display.display();
  delay(5000); // Mantener el mensaje por 5 segundos

  // Inicialización del HX710B
  hx710b.begin();

  // Configuración del cliente seguro con el certificado de Telegram
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Actualizar la hora
  timeClient.update();

  // Obtener la fecha y hora actual
  String formattedTime = timeClient.getFormattedTime();
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);
  String currentDate = String(timeInfo->tm_mday) + "/" + String(timeInfo->tm_mon + 1) + "/" + String(timeInfo->tm_year + 1900);

  // Leer y mostrar el sensor en el OLED
  if (currentMillis - lastSensorRead >= sensorInterval) {
    lastSensorRead = currentMillis;
    
    // Obtener datos del HX710B
    float sensorValue = hx710b.read();

    // Mostrar datos en el OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Valor del sensor: ");
    display.println(sensorValue);
    display.print("Fecha: ");
    display.println(currentDate);
    display.print("Hora: ");
    display.println(formattedTime);
    display.display();
  }

  // Enviar datos al bot de Telegram cada 10 segundos
  if (currentMillis - lastTelegramSend >= telegramInterval) {
    lastTelegramSend = currentMillis;
    
    float sensorValue = hx710b.read(); // Leer sensor de nuevo para asegurar precisión
    String message = "Valor del sensor: " + String(sensorValue) + "\nFecha: " + currentDate + "\nHora: " + formattedTime;
    bot.sendMessage("TU_CHAT_ID", message, "");
  }
}
