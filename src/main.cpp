#define HTTP_METHOD_ENUM_FIX 1

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ===== Módulos =====
#include "config/config.h"
#include "sensors/sensors.h"
#include "wifi/wifi_manager.h"
#include "monitoring/monitoring.h"
#include "html/pages.h"

// ===== Sensores =====
Adafruit_SHT31 sht31 = Adafruit_SHT31();
OneWire oneWire(4);
DallasTemperature dsSensor(&oneWire);

// ===== WiFi / WebServer =====
WebServer server(80);
Preferences prefs;
bool wifiConnected = false;

// ===== Variables de control de monitoreo =====
float ultimaTempAmbiente = -999;
float ultimaTempGrano = -999;
float ultimaHumedad = -999;
unsigned long ultimaLectura = 0;
bool primeraLectura = true;

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1500);

  // Configurar buzzer APAGADO desde el inicio
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, HIGH); // Buzzer apagado (activo en LOW)

  // Inicializar sensores
  initSensors();

  // ===== MODO PORTÁTIL =====
  Serial.println("═══════════════════════════════════════");
  Serial.println("   SISTEMA DE MONITOREO - FERMENTACIÓN");
  Serial.println("   Cooperativa de Cacao - Tocache");
  Serial.println("   MODO PORTÁTIL ACTIVADO");
  Serial.println("═══════════════════════════════════════");
  Serial.println("Cada encendido requiere configuración WiFi");
  Serial.println("Las credenciales se borran al apagar");
  Serial.println("═══════════════════════════════════════");

  startAP();
  
  // Configurar rutas del servidor
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/save", HTTP_GET, []() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });
  
  server.on("/info", HTTP_GET, []() {
    server.send(200, "text/html", pageInfo());
  });
  
  server.on("/status", HTTP_GET, []() {
    server.send(200, "text/html", pageStatus());
  });

  server.onNotFound([]() {
    Serial.println("Ruta no encontrada, redirigiendo: " + server.uri());
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("═══════════════════════════════════════");
  Serial.println("PORTAL DE CONFIGURACIÓN INICIADO");
  Serial.println("═══════════════════════════════════════");
  Serial.println("Red WiFi: Fermentacion_Setup");
  Serial.println("Contraseña: cacao2025");
  Serial.println("Abrir en navegador: http://192.168.4.1");
  Serial.println("═══════════════════════════════════════");

  // Pitidos para indicar que el AP está activo
  playAPActive();

  // Mantener el AP activo hasta que se conecte
  while (!wifiConnected) {
    server.handleClient();
    delay(10);
  }

  // Asegurar que buzzer esté apagado antes de iniciar Arduino Cloud
  digitalWrite(pinBuzzer, HIGH);
  delay(500);

  // Arduino Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  Serial.println("═══════════════════════════════════════");
  Serial.println("CONECTADO A ARDUINO IOT CLOUD");
  Serial.println("═══════════════════════════════════════");
  Serial.println("Parámetros de fermentación configurados:");
  Serial.printf("  Temp. ideal máxima: %.1f°C\n", TEMP_IDEAL_MAX);
  Serial.printf("  Temp. crítica: %.1f°C (NO SUPERAR)\n", TEMP_CRITICA_MAX);
  Serial.printf("  Humedad ambiente: %.0f%% - %.0f%%\n", HUMEDAD_MIN, HUMEDAD_MAX);
  Serial.println("═══════════════════════════════════════");
  Serial.println("Intervalo de lectura: 40 segundos");
  Serial.println("Envío inteligente: solo cambios significativos");
  Serial.println("═══════════════════════════════════════\n");
  
  // Esperar 5 segundos antes de primera lectura
  Serial.println("Esperando 5 segundos antes de iniciar monitoreo...");
  delay(5000);
  Serial.println("Iniciando monitoreo de sensores\n");
  
  // Inicializar monitoreo
  initMonitoring();
}

// ===== LOOP OPTIMIZADO =====
void loop() {
  ArduinoCloud.update();

  unsigned long tiempoActual = millis();
  
  if (tiempoActual - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = tiempoActual;
    
    // Leer sensores
    SensorReadings readings = readSensors();
    
    // Procesar si hay lecturas válidas
    if (readings.valid) {
      processMonitoring(readings.temperaturaAmbiente, readings.temperaturaGrano, readings.humedad);
    } else {
      Serial.println("Esperando lecturas válidas de sensores...");
      digitalWrite(pinBuzzer, HIGH); // Mantener buzzer apagado
    }
  }
  
  delay(100);
}
