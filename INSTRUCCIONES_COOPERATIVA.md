# INSTRUCCIONES DE CONFIGURACIÓN - SISTEMA DE FERMENTACIÓN DE CACAO

## Para el equipo de la cooperativa

Este dispositivo está listo para usar. Solo necesitan conectarlo a energia electrica es un minicomputadora mientras sea alimentado por energia electrica va funcionar, para nuestro prototipo estamos usando un powerbank de 10000 mAh(miliamperios) capacidad para estar activo entre 4 a 6 horas.Luego se puede cargar la powerbank viene incluido con un cable de tipo C para ser cargado.

---

## 📋 PASOS PARA LA PRIMERA CONFIGURACIÓN

### 1️⃣ Conectar a la electricidad
- Conecten el ESP32 a un puerto USB o adaptador de corriente
- El LED azul del ESP32 debería encenderse

### 2️⃣ Configurar el WiFi (SOLO LA PRIMERA VEZ)

#### Desde un celular o laptop:

1. **Buscar la red WiFi de la esp32:**
   - Nombre de red: `Fermentacion_Setup`
   - Contraseña: `cacao2025`

2. **Conectarse a esa red WiFi**
   - En su celular o laptop, vayan a Configuración → WiFi
   - Seleccionen "Fermentacion_Setup"
   - Ingresen la contraseña:'cacao2025'
   - Una vez que se conecten la red wifi les saldra 'sin internet'
   
3. **Configurar la red WiFi local**
   - Inmediatamente despues de conectarse a la red wifi 'Fermentación_Setup' dirigirse a su navegador de preferencia y vayan a: `http://192.168.4.1`
   - Ya dentro de la pagina web tendran la opción de colocar su red wifi importante tiene que tener conexión a internet para poder enviar los datos a la nube y app de arduino iot cloud.
   - Ingresen el nombre de la red y la contraseña de su WiFi
   - Presionen "Save" (Guardar)
   - Luego de guardar en la misma pagina les va aparecer el mensaje de 'configuración exitosa'
   - Redireccionate a la app si estas en celular o a la pagina si estas en laptop de arduino iot cloud para ver los dashboard.
   
4. ** Visualizar los dashboard en tiempo real**
   - Si estas en laptop ingresa este link: https://login.arduino.cc/login?state=hKFo2SBoYUI5VUVLX25iM2dGMHE2ZEIxYjhCUkExcjNsLWZlS6FupWxvZ2luo3RpZNkgcXpabS1lQnc2YWE4b0RQZXk4WTBTYUlpZ2hXRHlIOTijY2lk2SBlOXFpcEEyTjBrOVA4dnZyZTlmZEdjNnU5S2w5ZUhTUA&client=e9qipA2N0k9P8vvre9fdGc6u9Kl9eHSP&protocol=oauth2&scope=openid+profile+email&redirect_uri=https%3A%2F%2Fapp.arduino.cc&response_type=code&response_mode=query&nonce=d2VFR1pzUTlGfm12N3ZFdUxIXzdkX1Z%2BOUxkcVY0ZjZtcldJamxMRFZvVQ%3D%3D&code_challenge=VBCXJ_ShzQx630psdROiK__d_iAee4wtGmNuIsT-q8Y&code_challenge_method=S256&auth0Client=eyJuYW1lIjoiYXV0aDAtc3BhLWpzIiwidmVyc2lvbiI6IjIuMS4zIn0%3D#/sso/login
   - Una vez en la pagina web ingresa a la cuenta educativa creada para acceder a los dashboard:
   - Para los que estan en celular, dirigirse a play store y buscar la app Arduino IoT cloud remote, descargarlo y lo mismo colocar las credenciales.
   - Credenciales:
      - Username or Email: monitoreocacaocecat@gmail.com
      - Password: @cecat_123AZ
   
---

## ✅ VERIFICAR QUE FUNCIONA

### Señales de que todo está bien:
- Para empezar el led de color rojo del ESP32 está encendido,
- En el monitor serial (si lo conectan a una computadora) verán:
  ```
  ✅ Conectado a WiFi exitosamente!
  ✅ SISTEMA INICIADO CORRECTAMENTE
  ```
- Se conectan exitosamente en a la red wifi local 'Fermentación_setup'
- Los datos aparecen en el dashboard de Arduino Cloud

---

## SI NECESITAN CAMBIAR LA RED WiFi

Si cambian de router o necesitan conectar a otra red WiFi:

1. **Mantener presionado el botón BOOT** del ESP32 mientras lo encienden
2. El dispositivo borrará la configuración WiFi guardada
3. Repetir los pasos de configuración desde el inicio

---

##  SOLUCIÓN DE PROBLEMAS

### ❌ No aparece la red "Fermentacion_Setup"
- **Solución:** Desconecten y vuelvan a conectar el ESP32 a la corriente
- Esperen 30 segundos y busquen nuevamente la red wifi.
### ❌ No se abre la página de configuración automáticamente
- **Solución:** Abran el navegador manualmente y vayan a: `http://192.168.4.1`

### ❌ No se conecta a mi WiFi
- **Verificar:** ¿La contraseña del WiFi está correcta?
- **Verificar:** ¿El WiFi es de 2.4 GHz? (El ESP32 NO funciona con WiFi de 5 GHz)
- **Solución:** Reinicien el proceso presionando el botón BOOT al encender

### ❌ Los datos no aparecen en Arduino Cloud
- **Verificar:** ¿El ESP32 está conectado al WiFi? (ver LED azul encendido)
- **Verificar:** ¿Tienen acceso al dashboard de Arduino Cloud?
- **Solución:** Esperen 1-2 minutos, a veces tarda en sincronizar

### ❌ La app arduino cloud IOT remote no lee los datos
-Vuelven a cargar la app, con la acción de deslizamiento hacia abajo en la pantalla, si estas en laptop en la pagina misma realizas la acción de cargar y esperar unos 2 a 3 segundos para visualizar los parámetros en funcionamiento.

### ❌ 
---

---

## 🔧 INFORMACIÓN TÉCNICA (Opcional)

- **Dispositivo:** ESP32 DevKit C V4
- **Sensores:**
  - SHT31 (Temperatura y Humedad)
  - DS18B20 (Temperatura)
- **Conectividad:** WiFi 2.4 GHz + Arduino IoT Cloud
- **Alimentación:** 5V USB (mínimo 500mA)

---

**✅ ¡El sistema está listo para monitorear la fermentación del cacao!**
