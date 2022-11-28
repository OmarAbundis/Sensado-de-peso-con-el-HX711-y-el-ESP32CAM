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

![A014](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A014.jpg)

En la tabla, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y el HX711.

| ESP32-CAM | HX711 |
|-----------|-------|
| Vcc = 5V  | Vcc   |
| GND       | GND   |
| GPIO 12   | SCK   |
| GPIO 13   | DT    |

## Instrucciones de operación

1.	Para poder operar el circuito electrónico es necesario que coloque la celda de carga entre la base de lo que será la báscula y el plato o base en donde se colocará el peso, dejando un espacio de unos 5mm, para haya espacio de la deformación de la galga y en base a esa deformación se pueda determinar el peso de la manera más fiel posible, en otras palabras, evitar roces o golpes de la base en que se coloca el objeto a determinar su peso.

![A015](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A015.JPG)

![A016](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A016.JPG)

![A017](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A017.JPG)

2. Abrir su IDE de Arduino, elegir el microcontrolador a utilizar, ESP32-CAM, y escribir el [código de control](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/PROGRAMA/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM.ino)

![A018](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A018.JPG)

3. Corroborar que no haya errores de sintaxis.

4. Conectar su ESP32-CAM mediante el cable USB a USB mini.

5. Poner en modo de programación tu ESP32-CAM.

6. Cargar el programa de control.

![A019](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A019.JPG)

## Instrucciones de operación

Ya habiendo comprobado que el programa fue cargado de manera exitosa, ya puedes proceder con la verificación de su funcionamiento, de la siguiente manera:

1. Ve a la terminal con que cuenta el IDE de Arduino.

2. Asegúrate de que este a la velocidad de 115200.

3. Oprime el botón de “reset” con que cuenta el ESP32-CAM.

![A020](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A020.JPG)

4. Y si todo ha salido bien, se observará el desplegado de los datos.

![A021](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A021.JPG)

## Resultados

Para corroborar que se está transmitiendo correctamente el dato correspondiente al peso del objeto, el procesado y transmisión por WI-FI por medio del ESP32-CAM:

1.	Se abre una terminal en Ubuntu 20.04

![A022](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A022.JPG)

2.	Se realiza la subscripción al Bróker que se estableció en el programa.

Parte del programa en donde se realizó la subscripción realizada en el programa.

![A023](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A023.JPG)

Recuerda que en la realización de tu programa, tú tienes que generar uno propio.

![A024](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A024.JPG)

3.	Subscripción en la terminal. Y si todo se ha realizado de manera correcta, se observarán los datos que se están transmitiendo y ya puedes someter el circuito electrónico para la adquisición del peso de un cuerpo, a pruebas de funcionamiento.

![A025](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM/blob/main/Imagenes/A025.JPG)

**Nota** *El valor que se observa de medida de peso esta expresada en gramos.*

## Preguntas frecuentes

**¿Por qué no se conecta el ESP32CAM a la red por WiFi?**
 - **R:** Verificar que en el programa de control hayas colocado correctamente el SSID y la contraseña de tu router.
 - **R:** Verificar que tú red tenga una conexión AES-WPA2.
 - **R:** El ESP32CAM debe de estar en un rango de no más de tres metros al router y no debe de haber piezas metálicas cercanas.

**¿Por qué no se pueden observar en la consola de Ubuntu 20.04 la información de los sensores?**

  - **R:** Verificar que se hayan escrito los mismos temas en los suscriptores y en los publicadores tanto en la consola como en el programa.
  - **R:** Asegurarse de tener una regla que permita conexiones con el puerto 1883 y tener correctamente configurado el archivo **mosquitto.conf**.
  - **R:** Asegurarse que se tenga la IP más reciente del broker público, ya que cambia con frecuencia.


## Créditos

Profesor Hugo Vargas, instructor del curso de Internet de las Cosas impartido por la plataforma CodigoIoT.
