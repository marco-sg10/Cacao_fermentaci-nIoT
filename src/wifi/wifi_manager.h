#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "../config/config.h"
#include "../html/pages.h"

// ===== Variables globales =====
extern WebServer server;
extern Preferences prefs;
extern bool wifiConnected;

// ===== Funciones del portal =====
void startAP();
void handleRoot();
void handleSave();
void playConnectionSuccess();
void playConnectionError();
void playAPActive();

// ===== Implementación =====
void startAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(apSSID, apPass);

  Serial.print("📶 Punto de acceso creado: ");
  Serial.println(apSSID);
  Serial.print("➡️  IP: ");
  Serial.println(WiFi.softAPIP());
}

void handleRoot() {
  server.send(200, "text/html", pageForm());
}

void handleSave() {
  if (!server.hasArg("ssid") || !server.hasArg("pass")) {
    server.send(400, "text/html", pageError("Faltan parámetros."));
    return;
  }

  String ssid = server.arg("ssid");
  String pass = server.arg("pass");

  if (ssid.length() == 0) {
    server.send(400, "text/html", pageError("El SSID no puede estar vacío."));
    return;
  }

  Serial.println("\n═══════════════════════════════════════");
  Serial.println("📝 CREDENCIALES RECIBIDAS");
  Serial.println("═══════════════════════════════════════");
  Serial.println("SSID: " + ssid);
  Serial.println("Password: " + String(pass.length()) + " caracteres");
  Serial.println("═══════════════════════════════════════");
  
  server.send(200, "text/html", pageConnecting());
  delay(1000);
  
  Serial.println("🔄 Cambiando a modo Station (manteniendo AP activo)...");
  WiFi.mode(WIFI_AP_STA);
  Serial.print("🔄 Intentando conectar a: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid.c_str(), pass.c_str());
  
  unsigned long start = millis();
  int dots = 0;
  
  while (millis() - start < 30000) {
    delay(500);
    server.handleClient();
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n");
      break;
    }
    
    Serial.print(".");
    dots++;
    if (dots % 10 == 0) Serial.println();
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    Serial.println("═══════════════════════════════════════");
    Serial.println("✅ ¡CONEXIÓN EXITOSA!");
    Serial.println("═══════════════════════════════════════");
    Serial.print("📶 Red WiFi: ");
    Serial.println(ssid);
    Serial.print("📍 IP asignada: ");
    Serial.println(WiFi.localIP());
    Serial.print("💪 Señal WiFi: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("⚠️  Credenciales NO guardadas (modo portátil)");
    Serial.println("═══════════════════════════════════════\n");
    
    Serial.println("🔒 Cerrando Access Point...");
    delay(2000);
    server.stop();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);
    
    playConnectionSuccess();
    
  } else {
    wifiConnected = false;
    Serial.println("\n═══════════════════════════════════════");
    Serial.println("❌ ERROR DE CONEXIÓN");
    Serial.println("═══════════════════════════════════════");
    Serial.println("No se pudo conectar a: " + ssid);
    Serial.println("\n Posibles causas:");
    Serial.println("  • Contraseña incorrecta");
    Serial.println("  • Red WiFi 5GHz (solo 2.4GHz soportado)");
    Serial.println("  • Señal WiFi muy débil");
    Serial.println("  • SSID con caracteres especiales");
    Serial.println(" El portal WiFi permanece activo.");
    Serial.println("   Vuelve a intentarlo desde el navegador.");
    Serial.println("═══════════════════════════════════════\n");
    
    playConnectionError();
  }
}

void playConnectionSuccess() {
  Serial.println(" Confirmación sonora...");
  for (int i = 0; i < 2; i++) {
    digitalWrite(pinBuzzer, LOW);
    delay(100);
    digitalWrite(pinBuzzer, HIGH);
    delay(100);
  }
}

void playConnectionError() {
  // Pitido de error (largo)
  digitalWrite(pinBuzzer, LOW);
  delay(1000);
  digitalWrite(pinBuzzer, HIGH);
}

void playAPActive() {
  // Pitidos para indicar que el AP está activo
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinBuzzer, LOW);
    delay(200);
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
  }
}

#endif
