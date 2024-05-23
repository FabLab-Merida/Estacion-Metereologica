
#include <DHT.h> //https://github.com/adafruit/DHT-sensor-library (1.4.6)
#include <Adafruit_Sensor.h> //https://github.com/adafruit/Adafruit_Sensor (1.1.14)
#include <Adafruit_BMP085.h> //https://github.com/adafruit/Adafruit-BMP085-Library (1.2.4)
#include "BluetoothSerial.h"
#include <SPI.h>

/*
* Definicion de los pines a usar
*/

#define pin_dht22 4 // Sensor humedad y temperatura

/*
* Como el sensor de presion BMP085 es i2c
* 3.3 ==> 3.3 Voltios (NUNCA A 5V, para ello usar VCC)
* SDA ==> D21 (ESP32)
* SLC ==> D22 (ESP32)
* GND ==> GND
* VCC ==> 5V (SOLO SI NO USAS 3v3, no usar las dos a la vez)
*/
#define pin_sensor_lluvia 34
#define nombre_bluetooth "meteo_ESP" //Se puede moner el nombre a preferencia

/*
* Inicializacion de los objetos y variables
*/

DHT sensor_humedad(pin_dht22, DHT22);  // Si usamos un DHT21 en ver de un DHT22 cambiamos el 2º parametro "DHT22"
Adafruit_BMP085 sensor_presion;
float temperatura, humedad;
BluetoothSerial Serial_BT;

/*
* Funciones del programa
*/

void setup() {
  /*
  * Inicializacion de sensores y dispositivos
  */
  setCpuFrequencyMhz(240);
  Serial.begin(115200);
  Serial_BT.begin(nombre_bluetooth);
  sensor_humedad.begin();
  while (!sensor_presion.begin()) {
    Serial.println("Error al inicializar el sensor de presion atmosferica."); //Si el sensor de presion esta mal conectado saltara error
    delay(1000);
    }

  delay(2000); // Dejamos 2 sengudos a que se estabilicen los sensores
  }

void loop() {
  /* Obtencion de los datos de temepratura y humedad */
  humedad = sensor_humedad.readHumidity();
  temperatura = sensor_humedad.readTemperature();

  /* Salida datos por BT */


  Serial_BT.print("Humedad ");
  Serial_BT.print(humedad);
  Serial_BT.println("%");
  Serial_BT.print("Temperatura ");
  Serial_BT.print(temperatura);
  Serial_BT.println(" grados Celsius");
  Serial_BT.print("Humedad ");
  Serial_BT.print(humedad);
  Serial_BT.println("%");
  Serial_BT.print("Presion atmosferica  ");
  Serial_BT.print(sensor_presion.readPressure() / 100); // Leemos presion atm. y aplica conversion de pascales a hectopascales 
  Serial_BT.println(" Hpa");


  /* Salida datos por serial */

  Serial.print("Humedad ");
  Serial.print(humedad);
  Serial.println("%");
  Serial.print("Temperatura ");
  Serial.print(temperatura);
  Serial.println(" grados Celsius");
  Serial.print("Presion atmosferica ");
  Serial.print(sensor_presion.readPressure() / 100);
  Serial.println("HPa");
  Serial.println(" ");


  delay(5000);

  }