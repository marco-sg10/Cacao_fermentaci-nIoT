#ifndef CONFIG_H
#define CONFIG_H

// ===== Pines =====
const int pinBuzzer = 25;

// ===== Parámetros de fermentación =====
const float TEMP_IDEAL_MAX = 45.0;
const float TEMP_CRITICA_MAX = 52.0;
const float HUMEDAD_MIN = 60.0;  
const float HUMEDAD_MAX = 85.0; 

// ===== CONFIGURACIÓN DE MONITOREO OPTIMIZADO =====
const unsigned long INTERVALO_LECTURA = 30000;  // 30 segundos
const float UMBRAL_CAMBIO_TEMP = 0.2;
const float UMBRAL_CAMBIO_HUM = 1.0;

// ===== WiFi / WebServer =====
const char* PREFS_NAMESPACE = "wifi_conf";
const char* KEY_SSID = "ssid";
const char* KEY_PASS = "pass";

// ===== Access Point =====
const char* apSSID = "Fermentacion_Setup";
const char* apPass = "cacao2025";
const IPAddress local_IP(192, 168, 4, 1);
const IPAddress gateway(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);

#endif
