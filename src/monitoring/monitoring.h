#ifndef MONITORING_H
#define MONITORING_H

#include <Arduino.h>
#include "../config/config.h"

// ===== Variables de control de monitoreo =====
extern float ultimaTempAmbiente;
extern float ultimaTempGrano;
extern float ultimaHumedad;
extern unsigned long ultimaLectura;
extern bool primeraLectura;

// ===== Variables de Arduino Cloud (declaradas extern) =====
extern float temperaturaSHT31;
extern float temperaturaDS18B20;
extern float humedadSHT31;
extern bool alertaFermentacion;

// ===== Funciones de monitoreo =====
void initMonitoring();
void processMonitoring(float tempAmbiente, float tempGrano, float humedad);
void controlBuzzer(bool alerta);
void printMonitoringStatus(float tempAmbiente, float tempGrano, float humedad, const String& nivelAlerta);

// ===== Implementación =====
void initMonitoring() {
  ultimaTempAmbiente = -999;
  ultimaTempGrano = -999;
  ultimaHumedad = -999;
  ultimaLectura = 0;
  primeraLectura = true;
}

void controlBuzzer(bool alerta) {
  if (alerta) {
    digitalWrite(pinBuzzer, LOW);  // Activar buzzer
  } else {
    digitalWrite(pinBuzzer, HIGH); // Apagar buzzer
  }
}

void printMonitoringStatus(float tempAmbiente, float tempGrano, float humedad, const String& nivelAlerta) {
  Serial.println("╔═══════════════════════════════════════╗");
  Serial.println("║   MONITOREO DE FERMENTACIÓN           ║");
  Serial.println("╚═══════════════════════════════════════╝");
  
  unsigned long tiempoTotal = millis() / 1000;
  int horas = tiempoTotal / 3600;
  int minutos = (tiempoTotal % 3600) / 60;
  Serial.printf("⏱️  Tiempo activo: %d:%02d (h:mm)\n", horas, minutos);
  
  Serial.printf("🌡️  Temp. Ambiente: %.2f °C\n", tempAmbiente);
  Serial.printf("🌡️  Temp. Grano:    %.2f °C ", tempGrano);
  
  if (tempGrano > TEMP_CRITICA_MAX) {
    Serial.println("🔥 ¡CRÍTICO! Supera los 52°C");
  } else if (tempGrano > TEMP_IDEAL_MAX) {
    Serial.println("⚠️  Supera temp. ideal (45°C)");
  } else if (tempGrano >= 40.0) {
    Serial.println("✅ Rango óptimo");
  } else {
    Serial.println("📊 Monitoreando");
  }
  
  Serial.printf("💧 Humedad Ambiente: %.2f %% ", humedad);
  
  if (humedad < HUMEDAD_MIN) {
    Serial.println("⚠️  Baja (< 70%)");
  } else if (humedad > HUMEDAD_MAX) {
    Serial.println("⚠️  Alta (> 80%)");
  } else {
    Serial.println("✅ Óptima");
  }
  
  Serial.println("───────────────────────────────────────");
  Serial.printf("Estado: %s\n", nivelAlerta.c_str());
  Serial.println("📤 Datos enviados a la nube");
  Serial.println("═══════════════════════════════════════\n");
}

void processMonitoring(float tempAmbiente, float tempGrano, float humedad) {
  bool cambioSignificativo = false;
  
  // Primera lectura: inicializar valores
  if (primeraLectura) {
    temperaturaSHT31 = tempAmbiente;
    temperaturaDS18B20 = tempGrano;
    humedadSHT31 = humedad;
    ultimaTempAmbiente = tempAmbiente;
    ultimaTempGrano = tempGrano;
    ultimaHumedad = humedad;
    cambioSignificativo = true;
    primeraLectura = false;
    
    Serial.println("╔═══════════════════════════════════════╗");
    Serial.println("║   PRIMERA LECTURA COMPLETADA         ║");
    Serial.println("╚═══════════════════════════════════════╝");
    Serial.printf("🌡️  Temp. Ambiente inicial: %.2f °C\n", tempAmbiente);
    Serial.printf("🌡️  Temp. Grano inicial:    %.2f °C\n", tempGrano);
    Serial.printf("💧 Humedad inicial:        %.2f %%\n", humedad);
    Serial.println("═══════════════════════════════════════\n");
  } else {
    // Verificar cambios significativos
    if (abs(tempAmbiente - ultimaTempAmbiente) >= UMBRAL_CAMBIO_TEMP) {
      temperaturaSHT31 = tempAmbiente;
      ultimaTempAmbiente = tempAmbiente;
      cambioSignificativo = true;
    }
    
    if (abs(tempGrano - ultimaTempGrano) >= UMBRAL_CAMBIO_TEMP) {
      temperaturaDS18B20 = tempGrano;
      ultimaTempGrano = tempGrano;
      cambioSignificativo = true;
    }
    
    if (abs(humedad - ultimaHumedad) >= UMBRAL_CAMBIO_HUM) {
      humedadSHT31 = humedad;
      ultimaHumedad = humedad;
      cambioSignificativo = true;
    }
  }
  
  // ===== EVALUACIÓN DE CONDICIONES =====
  bool alertaTempIdeal = false;
  bool alertaTempCritica = false;
  bool alertaHumBaja = false;
  bool alertaHumAlta = false;
  
  if (!primeraLectura) {
    alertaTempIdeal = temperaturaDS18B20 > TEMP_IDEAL_MAX;
    alertaTempCritica = temperaturaDS18B20 > TEMP_CRITICA_MAX;
    alertaHumBaja = humedadSHT31 < HUMEDAD_MIN;
    alertaHumAlta = humedadSHT31 > HUMEDAD_MAX;
  }

  // Determinar nivel de alerta
  String nivelAlerta = "✅ ÓPTIMO";
  bool alertaPrevia = alertaFermentacion;
  alertaFermentacion = false;

  if (alertaTempCritica) {
    nivelAlerta = "🚨 CRÍTICO - TEMPERATURA PELIGROSA";
    alertaFermentacion = true;
  } else if (alertaTempIdeal || alertaHumBaja || alertaHumAlta) {
    nivelAlerta = "⚠️  ADVERTENCIA";
    alertaFermentacion = true;
  }

  // Control del buzzer
  controlBuzzer(alertaFermentacion);
  
  // Si cambió el estado de alerta, forzar envío
  if (alertaPrevia != alertaFermentacion) {
    cambioSignificativo = true;
  }

  // ===== REPORTE EN CONSOLA =====
  if (cambioSignificativo) {
    printMonitoringStatus(tempAmbiente, tempGrano, humedad, nivelAlerta);
  } else {
    Serial.println("📊 Lectura sin cambios significativos (ahorro de energía)");
  }
}

#endif
