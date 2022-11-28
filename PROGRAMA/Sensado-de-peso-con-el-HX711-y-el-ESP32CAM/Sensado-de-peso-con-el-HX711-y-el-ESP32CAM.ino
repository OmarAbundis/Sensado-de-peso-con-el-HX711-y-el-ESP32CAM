/*                    Proyecto: HABEETAT, Colmena saludable
 *                     
 *    Programa de control con las siguientes características:
 *      
 *      ->  Detecta el peso de la colmena, usando una galaga extensiométrica de 20Kg. y un acondicionador de señal HX711
 *      ->  Las señal del sensor ya procesada por el ESP32CAM, es transformada a tipo JSON y comunicada a través del protocolo MQTT a un Flow que sirve de punto de monitoreo.
 *      
 *    Integrantes del equipo:
 *    
 *          Abundis Noyola Omar
 *          García León Lizbeth
 *          Soto Soto Raymundo
 *          
 *    Profesor e instructor del curso de Código IoT      
 *    
 *          Hugo Vargas
 *          
 *    Fecha:  27 de noviembre del 2022
 * 
 *
      Notas del profesor para el correcto funcionamiento de MQTT
  
            Este programa envía datos a por Internet a través del protocolo MQTT. Para poder comprobar el funcionamiento de este programa, es necesario conectarse a un broker
            y usar NodeRed para visualzar que la información se está recibiendo correctamente.
            
            Este programa está basado en "Conexión básica por MQTT del NodeMCU" y explica como enviar strings que contengan JSON para enviar mas de una variable a la vez.
 
      Referencias:
   
            Example testing sketch for various DHT humidity/temperature sensors written by ladyada
  
            REQUIRES the following Arduino libraries:
  
            DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
            Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
            Biblioteca "HX711 Arduino Library"  by ** Bogdan Necula ** 

 *    Componentes   Pines del ESP32-CAM     estados lógicos
 *           
 *        -> ledStatus------GPIO 33---------On=>LOW,  Off=>HIGH
 *        -> ledFlash-------GPIO 4----------On=>HIGH, Off=>LOW
 * 
 *                
 *                
 *          Pines del ESP32-CAM      Pines del HX711
 *      
                     VCC = 5V ----------- VCC
                     GND      ----------- GND
                     GPIO 12  ----------- SCK
                     GPIO 13  ----------- DT
 *                            
 *             
 *     Referencia de terminales DHT 11                       
 *     https://www.omniblug.com/sensor-temperatura-humedad-DHT11-DHT22.html
 */

// BIBLIOTECAS

#include <WiFi.h>           // Biblioteca para el control de WiFi
#include <PubSubClient.h>   //Biblioteca para conexion MQTT
#include <HX711.h>          //Biblioteca para el control del HX711

// Datos de WiFi

const char* ssid = "INFINITUMB46E_2.4";   // Aquí debes poner el nombre de tu red
const char* password = "4520297937";      // Aquí debes poner la contraseña de tu red

//Datos del broker MQTT

const char* mqtt_server = "192.168.1.66"; // Si estas en una red local, coloca la IP asignada, en caso contrario, coloca la IP publica
IPAddress server(192,168,1,66);

// Datos para el control de la balanza

const int LOADCELL_DOUT_PIN = 13;         // Conexión con <HX711,DT> y <ESP32,GPIO13>
const int LOADCELL_SCK_PIN = 12;          // Conexión con <HX711,12> y <ESP32, GPIO12>
const float ajuste = 2827.82;             // valor inicial sin peso y sin la función balanza.tare(30) en void setup()

// Objetos

WiFiClient espClient;                     // Este objeto maneja los datos de conexion WiFi
PubSubClient client(espClient);           // Este objeto maneja los datos de conexion al broker
HX711 balanza;                            // Objeto balanza


// Variables

int flashLedPin = 4;                      // Para mostrar mensajes recibidos
int statusLedPin = 33;                    // Para indicar el estatus de conexión
long timeNow, timeLast;                   // Variables de control de tiempo no bloqueante
int wait = 5000;                          // Indica la espera cada 5 segundos para envío de mensajes MQTT

// Inicialización del programa

void setup() 
{
  // Iniciar comunicación serial
  
  Serial.begin (115200);
  Serial.println ("programa iniciado");
 
  pinMode (flashLedPin, OUTPUT);
  pinMode (statusLedPin, OUTPUT);
  digitalWrite (flashLedPin, LOW);
  digitalWrite (statusLedPin, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);                                                       // Esta es la función que realiz la conexión a WiFi
 
  while (WiFi.status() != WL_CONNECTED) 
  {                                                                                 // Este bucle espera a que se realice la conexión
    
    digitalWrite (statusLedPin, HIGH);
    delay(500);                                                                     // Dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (statusLedPin, LOW);
    Serial.print(".");                                                              // Indicador de progreso
    delay (5);
  }
  
  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Si se logro la conexión, encender led
  
  if (WiFi.status () > 0)
  {
    digitalWrite (statusLedPin, LOW);
  }
  
  delay (1000);                                                                   // Está espera es solo una formalidad antes de iniciar la comunicación con el broker

  // Conexión con el broker MQTT
  
  client.setServer(server,1883);                                                 // Conectarse a la IP del broker en el puerto indicado
  client.setCallback(callback);                                                  // Activar función de CallBack, permite recibir mensajes MQTT y ejecutar funciones a partir de ellos
  delay(1500);                                                                   // Esta espera es preventiva, espera a la conexión para no perder información

  timeLast = millis ();                                                         // Inicia el control de tiempo

  // Inicialización de la configuración de la balanza electrónica

  balanza.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);                           // Inicialización, señales de DT y SCK del HX711
  delay(250);                                                                   // Espera bloqueante de 250ms, para estabilizar.
  
  Serial.print("Lectura del valor del ADC:   ");                                // Lectura inicial del ADC del HX711, para la tara.
  Serial.println(balanza.read());                                               // Proceso de de lectura inicial
  Serial.println("No ponga ningún objeto sobre la balanza");
  Serial.println("Destarando...");
  balanza.set_scale(105.853);
  //balanza.tare(30);                                                             // Hacer 30 lecturas, el promedio es la tara
  Serial.println("Listo para pesar");

}                                                                               // fin del void setup ()


// Cuerpo del programa, bucle principal

void loop() 
{
                                                                                // Verificar siempre que haya conexión al broker
  
  if (!client.connected()) 
  {
    reconnect();                                                                // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
  }                                                                             // fin del if (!client.connected())
  
  client.loop();                                                                // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker
  
  timeNow = millis();                                                           // Control de tiempo para esperas no bloqueantes
  if (timeNow - timeLast > wait) 
  {                                                                             // Manda un mensaje por MQTT cada cinco segundos
    
    timeLast = timeNow;                                                         // Actualización de seguimiento de tiempo


//  Obtención del peso de la balanza

    float reading = balanza.get_units(30);                                      // Se toma un valor proveniente del HX711
    float p = reading - ajuste;                                                 // Se hace un ajuste para no tomar en cuenta que se tare con un nuevo valor en una falla de energía.
    
           
                                                                                //Se construye el string correspondiente al JSON que contiene 3 variables
    
    //String json = "{\"id\":\"Habeetat_SensoresExt\",\"temp\":"+String(t)+",\"hum\":"+String(h)+",\"peso\":"+String(p)+"}";
    String json = "{\"id\":\"Habeetat_SensoresExt\",\"peso\":"+String(p)+"}";
    
    Serial.println(json);                                                       // Se imprime en monitor solo para poder visualizar que el string esta correctamente creado
    
    int str_len = json.length() + 1;                                            //Se calcula la longitud del string
    char char_array[str_len];                                                   //Se crea un arreglo de caracteres de dicha longitud
    json.toCharArray(char_array, str_len);                                      //Se convierte el string a char array    
    client.publish("codigoIoT/G7/Habeetat", char_array);                       // Esta es la función que envía los datos por MQTT, especifica el tema y el valor
    
  }                                                                             // fin del if (timeNow - timeLast > wait)
}                                                                               // fin del void loop ()

// Funciones de usuario

                                                                // Esta función permite tomar acciones en caso de que se reciba un mensaje correspondiente a un tema al cual se hará una suscripción

void callback(char* topic, byte* message, unsigned int length) 
{
  
                                                                                 // Indicar por serial que llegó un mensaje
  
  Serial.print("Llegó un mensaje en el tema: ");
  Serial.print(topic);

                                                                                 // Concatenar los mensajes recibidos para conformarlos como una varialbe String
  
  String messageTemp;                                                           // Se declara la variable en la cual se generará el mensaje completo  
  
  for (int i = 0; i < length; i++) 
  {                                                                             // Se imprime y concatena el mensaje
    
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

                                                                                // Se comprueba que el mensaje se haya concatenado correctamente
  
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);

                                                                               // En esta parte puedes agregar las funciones que requieras para actuar segun lo necesites al recibir un mensaje MQTT

                                                                               // Ejemplo, en caso de recibir el mensaje true - false, se cambiará el estado del led soldado en la placa.
                                                                               // El ESP323CAM está suscrito al tema codigoIoT/ejemplo/mqttin se cambia a codigoIoT/G7/Habeetat_in
  
  if (String(topic) == "codigoIoT/G7/Habeetat_in") 
    {                                                                         // En caso de recibirse mensaje en el tema codigoIoT/G7/Habeetat
      if(messageTemp == "true")
      {
        Serial.println("Led encendido");
        digitalWrite(flashLedPin, HIGH);
        
              
      }                                                                       // fin del if (String(topic) == "")
      
      else if(messageTemp == "false")
      {
        Serial.println("Led apagado");
        digitalWrite(flashLedPin, LOW);
        
      }                                                                     // fin del else if(messageTemp == "false")
      
    }                                                                                         // fin del if (String(topic) == "esp32/output")
    
}                                                                                             // fin del void callback

// Función para reconectarse

void reconnect() 
{
                                                                                              // Bucle hasta lograr conexión
  while (!client.connected()) 
  {                                                                                           // Pregunta si hay conexión
  Serial.print("Tratando de contectarse...");
                                                                                              // Intentar reconexión
    
  if (client.connect("ESP32CAMClient")) 
  {                                                                                           // Pregunta por el resultado del intento de conexión
    
    Serial.println("Conectado");
    client.subscribe("codigoIoT/G7/Habeetat_in");                                             // Esta función realiza la suscripción al tema
    
    }                                                                                         // fin del  if (client.connect("codigoIoT/G7/Habeetat_in"))
    
   else 
   {                                                                                          //en caso de que la conexión no se logre
    
     Serial.print("Conexion fallida, Error rc=");
     Serial.print(client.state());                                                            // Muestra el codigo de error
     Serial.println(" Volviendo a intentar en 5 segundos");
    
     delay(5000);                                                                             // Espera de 5 segundos bloqueante
     
     Serial.println (client.connected ());                                                    // Muestra estatus de conexión
    }                                                                                         // fin del else
  }                                                                                           // fin del bucle while (!client.connected())
}                                                                                             // fin de void reconnect(
