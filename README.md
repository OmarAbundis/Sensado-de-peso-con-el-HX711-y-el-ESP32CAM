# Sensado-de-peso-con-el-HX711-y-el-ESP32CAM

## Introducción

En el presente trabajo se describe de qué manera se puede implementar una báscula utilizando una galga extensiométrica de 20Kg., de capacidad, un circuito acondicionador de señal que integra un convertidor de señal analógica a digital de 24 bits de resolución, el HX711 y como elemento para el procesado de los datos adquiridos y acondicionamiento para su envío a través del Bróker Mosquitto, el microcontrolador ESP32-CAM.

## Material necesario

- 1 [ESP32CAM](https://docs.ai-thinker.com/en/esp32-cam). Tarjeta de desarrollo
- 1 [FTDI](https://ftdichip.com/wp-content/uploads/2020/08/DS_FT232R.pdf). Tarjeta controladora USB
- 1 [HX711](https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf). ADC-24 bits para escalas de peso.
- 1 [Celda de carga para 20Kg.](https://naylampmechatronics.com/sensores/157-celda-de-carga-20kg.html). También conocida como galga extensiométrica.
- 1 cable USB a USB mini.
- Jumpers MM.

## Software necesario

En la experimentación de está práctica se debe de contar con el siguiente software libre:

- Ubuntu 20.04
- Arduino IDE
- Mosquitto MQTT Broker, Listener en puerto 1883 para 0.0.0.0 y conexiones autentificadas activadas.

## Material de referencia

Previamente a la realización de está práctica, ha sido necesario el estudio de distitos temas, que se encuentran en la plataforma [edu.codigoiot.com](https://www.codigoiot.com/), en donde se explican conceptos y configuraciones necesarias, tales como:

- Instalación de virtual Box y Ubuntu 20.04
- Configuración de Arduino IDE para ESP32CAM
- Instalación de Mosquitto MQTT

También se recomienda el estudio de las siguientes páginas, donde se explican algunas implementaciones de una báscula electrónica usando la tarjeta de desarrollo Arduino UNO.

- [bogde/HX711](https://github.com/bogde/HX711)
- [Tutorial trasmisor de celda de carga HX711, Balanza Digital](https://naylampmechatronics.com/blog/25_tutorial-trasmisor-de-celda-de-carga-hx711-balanza-digital.html)
- [Balanza Electronica con HX711 y Arduino](https://controlautomaticoeducacion.com/arduino/balanza-electronica-hx711-arduino/)
- [Balanza WIFI con ESP32](https://www.prometec.net/balanza-wifi-esp32/)
- [Celda de carga 50 kg arduino programacion](https://arduinoque.com/arduino/celda-de-carga-50-kg-arduino-programacion/)
- [ESP32 Troubleshooting Guide](https://randomnerdtutorials.com/esp32-troubleshooting-guide/)

## Servicios

Adicional a lo ya indicado en líneas superiores, también es necesario contar con los siguientes servicios:

[HiveMQ](https://www.hivemq.com/public-mqtt-broker/). Es un broker público y que no demanda de contar con una cuenta.

## Instrucciones para realizar el circuito de control para el sensado del peso

**Nota:** Se recomienda revisar la información previamente citada, antes de comenzar con el armado del circuito electrónico, para reducir la probabilidad de realizar malas conexiones entre los dispositivos, fallas en la polarización y en consecuencia el daño permanente de los dispositivos o daño parcial o total de su equipo de cómputo.

1.  Se debe de armar el circuito electrónico mostrado en la figura, teniendo cuidado de conectar a las terminales indicadas del ESP32-CAM, y cuidar la polaridad de los dispositivos.

![]()

En la tabla, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y el HX711.

| ESP32-CAM | HX711 |
|-----------|-------|
| Vcc = 5V  | Vcc   |
| GND       | GND   |
| GPIO 12   | SCK   |
| GPIO 13   | DT    |

## Instrucciones de operación

## Resultados

## Evidencias

## Preguntas frecuentes

## Compatibilidad

## Créditos
