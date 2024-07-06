
#NitoWeather
# Proyecto: Monitor de Sensor con ESP32 y Pantalla OLED

## Descripción
Este proyecto utiliza un ESP32 para leer datos de un sensor HX710B, mostrar estos datos en una pantalla OLED de 128x64 y enviar los datos a un bot de Telegram. 

## Autor
Nito

## Versión
0.5 (6 de Julio de 2024)

## Instrucciones de Uso

### Conexión del Hardware

1. **ESP32:**
    - Conecta el ESP32 a una fuente de alimentación adecuada.

2. **Pantalla OLED (128x64):**
    - Conecta SDA al pin 21 del ESP32.
    - Conecta SCL al pin 22 del ESP32.
    - Conecta VCC a 3.3V.
    - Conecta GND a GND.

3. **Sensor HX710B:**
    - Conecta DOUT al pin 4 del ESP32.
    - Conecta SCK al pin 5 del ESP32.
    - Conecta VCC a 3.3V.
    - Conecta GND a GND.

### Configuración del Software

1. **IDE de Arduino:**
    - Instala el IDE de Arduino desde [aquí](https://www.arduino.cc/en/software).

2. **Instalación de Librerías:**
    - Instala las siguientes librerías desde el Administrador de Librerías del IDE de Arduino:
      - **Adafruit GFX Library:** [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
      - **Adafruit SSD1306:** [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
      - **WiFiManager:** [WiFiManager](https://github.com/tzapu/WiFiManager)
      - **UniversalTelegramBot:** [UniversalTelegramBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
      - **NTPClient:** [NTPClient](https://github.com/arduino-libraries/NTPClient)
      - **HX710B Library:** Puedes encontrar el archivo `HX710B.h` en el repositorio de este proyecto.

3. **Configuración de Credenciales:**
    - Reemplaza `TU_BOT_TOKEN` con el token de tu bot de Telegram.
    - Reemplaza `TU_CHAT_ID` con el ID de chat de Telegram al que deseas enviar los mensajes.

4. **Subir el Código al ESP32:**
    - Conecta tu ESP32 al ordenador.
    - Selecciona la placa ESP32 y el puerto adecuado en el IDE de Arduino.
    - Sube el código proporcionado.

### Ejecución del Proyecto

1. **Conexión a WiFi:**
    - Al iniciar, el ESP32 se conectará a una red WiFi utilizando WiFiManager.
    - Busca una red WiFi llamada `ESP32_AP` y conéctate a ella.
    - Abre un navegador y ve a `192.168.4.1` para configurar tu red WiFi.

2. **Pantalla OLED:**
    - La pantalla OLED mostrará "GreenNito" junto con la fecha y hora actual al inicio.
    - Luego mostrará los datos del sensor periódicamente.

3. **Bot de Telegram:**
    - Los datos del sensor se enviarán a Telegram cada 10 segundos.

## Historial de Versiones

- **Versión 0.1:** Inicialización del proyecto.
- **Versión 0.2:** Integración del bot de Telegram.
- **Versión 0.3:** Optimización del código utilizando millis() en lugar de delay().
- **Versión 0.4:** Optimización del código utilizando X509List cert para la conexión TLS con Telegram.
- **Versión 0.5:** Adaptación y optimización del código para ESP32 WROOM.

## Enlaces a las Librerías

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [WiFiManager](https://github.com/tzapu/WiFiManager)
- [UniversalTelegramBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- [NTPClient](https://github.com/arduino-libraries/NTPClient)
