/*
Cayenne Photoresistor Example

This sketch shows how to send Photoresistor Sensor data to the Cayenne Dashboard.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Attach a photoresistor to an analog pin on your Arduino.
   Make sure to use an analog pin, not a digital pin.
   Schematic:
   [Ground] -- [10k-resistor] -- | -- [Photoresistor] -- [5V]
                                 |
                            Analog Pin
2. Set the SENSOR_PIN value below to the pin number you used when connecting the sensor.
3. Set the VIRTUAL_CHANNEL value below to a free virtual channel (or the virtual channel of a Photoresistor Sensor widget you have added) in the Dashboard.
4. Set the Cayenne authentication info to match the authentication info from the Dashboard.
5. Compile and upload this sketch.
6. Once the Arduino connects to the Dashboard it should automatically create a temporary display widget (or update the Photoresistor Sensor widget you have added) with data.
   To make a temporary widget permanent click the plus sign on the widget.
*/

 
#include <CayenneMQTTSerial.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "23ee6a40-fa6d-11ed-8485-5b7d3ef089d0";
char password[] = "03663e8adbfc39653382aa7b3ba2912cfd44d42b";
char clientID[] = "07847a20-fa9f-11ed-8485-5b7d3ef089d0";

#define ACTUATOR_PIN 2 
#define SENSOR_PIN 0
#define SENSOR_PIN2 1
#define VIRTUAL_CHANNELFOTO 1
#define VIRTUAL_CHANNELPOTE 2
#define VIRTUAL_CHANNELBOTON3 3
void setup()
{
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
  pinMode(ACTUATOR_PIN, INPUT);
}

void loop()
{
  Cayenne.loop();
}
  CAYENNE_IN(VIRTUAL_CHANNELBOTON3)
  {
    int value = getValue.asInt();
    CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNELBOTON3, ACTUATOR_PIN, value);
    digitalWrite(ACTUATOR_PIN, value);


    if (value == 1 ){
      digitalWrite(4, HIGH);
    }
    else {
      digitalWrite(4, LOW);
    }
  }

  CAYENNE_OUT_DEFAULT()
  {
    Cayenne.virtualWrite(0, millis());
  }
// Lectura Analogica
CAYENNE_OUT(VIRTUAL_CHANNELFOTO)
{
  Cayenne.virtualWrite(VIRTUAL_CHANNELFOTO, analogRead(SENSOR_PIN), "analog_sensor", "null");
}
CAYENNE_OUT(VIRTUAL_CHANNELPOTE)
{
  Cayenne.virtualWrite(VIRTUAL_CHANNELPOTE, analogRead(SENSOR_PIN2), "analog_sensor", "null");
}
