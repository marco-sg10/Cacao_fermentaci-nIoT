#ifndef HTML_PAGES_H
#define HTML_PAGES_H

#include <Arduino.h>

String pageForm() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Configuración WiFi - Modo Portátil</title>
<style>
body{
  margin:0;
  font-family:'Poppins',sans-serif;
  background:linear-gradient(135deg,#8B4513,#D2691E);
  color:#333;
  display:flex;
  justify-content:center;
  align-items:center;
  min-height:100vh;
  padding:20px;
}
.card{
  background:white;
  padding:30px;
  border-radius:15px;
  box-shadow:0 8px 20px rgba(0,0,0,0.3);
  text-align:center;
  max-width:420px;
  width:100%;
}
h2{color:#8B4513;margin-bottom:10px;}
.subtitle{color:#666;font-size:14px;margin-bottom:20px;}
input[type=text],input[type=password]{
  width:90%;
  padding:12px;
  margin:8px 0;
  border:2px solid #D2691E;
  border-radius:8px;
  font-size:16px;
}
input[type=text]:focus,input[type=password]:focus{
  outline:none;
  border-color:#8B4513;
}
button,input[type=submit]{
  background:#8B4513;
  color:white;
  border:none;
  border-radius:8px;
  padding:12px 24px;
  cursor:pointer;
  margin-top:10px;
  font-size:16px;
  transition:0.3s;
  width:95%;
}
button:hover,input[type=submit]:hover{
  background:#6B3410;
}
small{color:#777;}
.showpass{margin-top:8px;text-align:left;padding-left:5%;}
footer{
  margin-top:20px;
  color:#666;
  font-size:12px;
  border-top:1px solid #ddd;
  padding-top:15px;
}
.info-box{
  background:#FFF3E0;
  border-left:4px solid #FF6F00;
  padding:10px;
  margin:15px 0;
  border-radius:5px;
  text-align:left;
  font-size:13px;
}
.warning-box{
  background:#FFE5E5;
  border-left:4px solid #FF3333;
  padding:10px;
  margin:15px 0;
  border-radius:5px;
  text-align:left;
  font-size:12px;
}
.icon{font-size:24px;margin-bottom:10px;}
</style>
</head>
<body>
  <div class="card">
    <div class="icon">🍫</div>
    <h2>Sistema de Fermentación</h2>
    <div class="subtitle">Cooperativa de Cacao - Tocache</div>
    
    <div class="warning-box">
      <strong>🔄 Modo Portátil Activo</strong><br>
      Las credenciales NO se guardan. Al apagar el dispositivo deberás volver a configurar la red WiFi.
    </div>
    
    <div class="info-box">
      <strong>📡 Conectar a WiFi</strong><br>
      Ingresa los datos de tu red para iniciar el monitoreo
    </div>
    
    <form method="POST" action="/save">
      <input name="ssid" type="text" placeholder="Nombre de la red (SSID)" required><br>
      <input id="pass" name="pass" type="password" placeholder="Contraseña WiFi" required><br>
      <div class="showpass">
        <input type="checkbox" onclick="togglePass()"> <small>Mostrar contraseña</small>
      </div>
      <input type="submit" value="✅ Conectar (Temporal)">
    </form>

    <footer>
      <strong>Sistema de Monitoreo IoT</strong><br>
      Control de temperatura y humedad en tiempo real<br>
      <small>v1.1 - Modo Portátil Corregido - 2025</small>
    </footer>
  </div>
<script>
function togglePass(){
  var p=document.getElementById('pass');
  p.type=(p.type==='password')?'text':'password';
}
</script>
</body>
</html>
)rawliteral";
  return page;
}

String pageConnecting() {
  String page = R"rawliteral(
  <!DOCTYPE html><html><head><meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <meta http-equiv="refresh" content="3;url=/status">
  <style>
  body{
    font-family:'Poppins',sans-serif;
    text-align:center;
    padding-top:40px;
    background:linear-gradient(135deg,#8B4513,#D2691E);
    color:white;
    min-height:100vh;
  }
  .success-box{
    background:white;
    color:#333;
    padding:30px;
    border-radius:15px;
    max-width:400px;
    margin:0 auto;
    box-shadow:0 8px 20px rgba(0,0,0,0.3);
  }
  h2{color:#27ae60;animation:fade 1s ease-in;}
  @keyframes fade{from{opacity:0;}to{opacity:1;}}
  .loading{
    margin:20px auto;
    width:40px;
    height:40px;
    border:4px solid #f3f3f3;
    border-top:4px solid #8B4513;
    border-radius:50%;
    animation:spin 1s linear infinite;
  }
  @keyframes spin{0%{transform:rotate(0deg);}100%{transform:rotate(360deg);}}
  .info{background:#FFF3E0;padding:10px;border-radius:5px;margin-top:15px;font-size:13px;}
  </style></head>
  <body>
    <div class="success-box">
      <h2>✅ Credenciales Recibidas</h2>
      <div class="loading"></div>
      <p><strong>Intentando conectar a la red WiFi...</strong></p>
      <p>Esto puede tomar hasta 30 segundos</p>
      <div class="info">
        🔄 <strong>Modo Portátil</strong><br>
        Conectándose al WiFi. Por favor espera...
      </div>
      <hr style="margin:20px 0;">
      <small>Serás redirigido automáticamente al estado...</small>
    </div>
  </body></html>
  )rawliteral";
  return page;
}

String pageInfo() {
  String page = R"rawliteral(
    <!DOCTYPE html><html><head><meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <style>
    body{font-family:Arial;text-align:center;padding:20px;background:#f0f0f0;}
    .box{background:white;padding:20px;border-radius:10px;max-width:400px;margin:0 auto;}
    </style></head>
    <body>
      <div class="box">
        <h2>ℹ️ Información del Sistema</h2>
        <p><strong>Red WiFi:</strong> Fermentacion_Setup</p>
        <p><strong>IP:</strong> 192.168.4.1</p>
        <p><strong>Estado:</strong> Esperando configuración</p>
        <hr>
        <button onclick="window.location.href='/'">Configurar WiFi</button>
      </div>
    </body></html>
    )rawliteral";
  return page;
}

String pageStatus() {
  String page = "<!DOCTYPE html><html><head><meta charset='utf-8'>";
  page += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  page += "<meta http-equiv='refresh' content='5'>";
  page += "<style>body{font-family:Arial;text-align:center;padding:20px;background:#f0f0f0;}";
  page += ".box{background:white;padding:20px;border-radius:10px;max-width:400px;margin:0 auto;}</style></head>";
  page += "<body><div class='box'><h2>📊 Estado de Conexión</h2>";
  
  if (WiFi.status() == WL_CONNECTED) {
    page += "<p style='color:green;font-size:20px;'>✅ Conectado</p>";
    page += "<p><strong>Red:</strong> " + WiFi.SSID() + "</p>";
    page += "<p><strong>IP:</strong> " + WiFi.localIP().toString() + "</p>";
    page += "<p><strong>Señal:</strong> " + String(WiFi.RSSI()) + " dBm</p>";
    page += "<hr><p>El portal se cerrará en breve...</p>";
  } else {
    page += "<p style='color:orange;font-size:20px;'>🔄 Conectando...</p>";
    page += "<p>Por favor espera...</p>";
    page += "<p><small>Esta página se actualiza automáticamente</small></p>";
    page += "<hr><button onclick=\"window.location.href='/'\">Volver a configurar</button>";
  }
  
  page += "</div></body></html>";
  return page;
}

String pageError(const char* message) {
  String page = "<!DOCTYPE html><html><body style='font-family:Arial;text-align:center;padding:40px;'>";
  page += "<h2>❌ Error</h2><p>";
  page += message;
  page += " <a href='/'>Volver</a></p></body></html>";
  return page;
}

#endif
