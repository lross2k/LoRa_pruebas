# Pruebas y ejemplos de LoRa 32
Este repositorio fue creado para documentar en distintas plataformas el proceso de configuración 
y uso de microcontroladores con capacidades LoRa, así como alamacenar ejemplos de uso y código
reutilizable para los mismos.

## Información de dispositivos
### HELTEC LoRa 32
- [Datasheet ESP32](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf).
- [Documentación](https://heltec.org/project/wifi-lora-32/).  
- [Esquemática](https://resource.heltec.cn/download/WiFi_LoRa_32/V2/WIFI_LoRa_32_V2(868-915).PDF).
- [Pinout](https://resource.heltec.cn/download/WiFi_LoRa_32/WIFI_LoRa_32_V2.pdf).

## IDEs para trabajar con ESP32
### Arduino IDE
1. Instalar la IDE de Arduino ya sea del [sitio oficial](https://www.arduino.cc/en/software) o un
   repositorio adicional, como en el caso de Linux basado en Debian usando `sudo apt-get install arduino`
2. Instalar la librería `Heltec ESP32` en el manager de librerías de Arduino, dentro de la IDE, pasos: 
   `Sketch -> Include Library -> Manage Libraries` y buscar `"Heltec ESP32"` e instalarlo
3. En Linux se debe dar permisos al usuario para manejar puertos USB con `sudo usermod -a -G dialout
   $USER` 
4. Abrir en la IDE `File` -> `Preferences` y en *Additional Boards Manager URLs* se coloca la
   siguiente dirección https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.6/package_heltec_esp32_index.json
5. En la IDE ir a `Tools -> Board -> Boards Manager...` y acá buscar "Heltec ESP32" e
   instalarlo
6. Una vez instalado se puede seleccionar la placa correspondiente, en este caso se estaba usando la 
   "WiFi LoRa 32 (V2)"
### STM32CubeIDE
1. Descargar STM32CubeProg del [sitio oficial](https://www.st.com/en/development-tools/stm32cubeprog.html)
   e instalarlo
2. Descargar STM32CubeIDE del [sitio oficial](https://www.st.com/en/development-tools/stm32cubeide.html)
   e instalarlo
3. En Linux se debe dar permisos al usuario para manejar puertos USB con `sudo usermod -a -G dialout
   $USER` 

## Reglas para contribuciones
- Para proponer cambios, correciones o mejoras, hacer un fork de este repositorio y luego de realizar
  los cambios crear un pull request con la información detallada de lo realizado.
- Para hacer cambios locales, simplemente clonar el repositorio.

# Ejemplos
Inicialmente se corrió un ejemplo base para el LoRa 32, este se encuentra en el directorio `WiFi
LoRa 32FactoryTest`, el mismo puede ser usado luego de completar el proceso de configuración de
Arduino IDE

# Contactos
- [Luis Ross Lépiz](mailto:luisross87@estudiantec.cr)
- [Byron Bolaños Zamora](mailto:bbolanos@estudiantec.cr)

