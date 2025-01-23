#include "BluetoothSerial.h"
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
#define nombre_bluetooth "meteo_ESP" //Se puede moner el nombre a preferencia

/*
* Inicializacion de los objetos y variables
*/
BluetoothSerial Serial_BT;

/*
* Funciones del programa
*/

void setup() {
  Serial.begin(115200);
  Serial_BT.begin(nombre_bluetooth);
}

void loop() {
  /* Salida datos por BT */
  Serial_BT.println("Hola mundo ");
  delay(5000);

}
