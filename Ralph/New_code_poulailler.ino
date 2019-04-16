#include <GSM.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#define PINNUMBER "264843"

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;
char txtMsg[200] = "Le taux de luminosité du poulailler est inférieur à 40 lux.";
char remoteNum[20] = "0769621300";

float sensorVoltage;
float sensorValue;
float UVIndex;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(0x29);


void setup()

{
  Serial.begin(9600);

  boolean notConnected = true;

  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);


    }
  }
}


void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  tsl.getEvent(&event);

  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    Serial.print("sensor.reading = ");
    Serial.print(event.light); Serial.println(" lux");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
    if (sensorValue <= 40) {
      // send the message
      Serial.println("Le message va etre envoyé");
      sms.beginSMS("0769621300");
      sms.print("Alerte, Problème de luminosité dans le poulailler");
      sms.endSMS();
      Serial.println("\nCOMPLETE!\n");


    }
  }

  delay(250);


}

/*
  Read input serial
*/
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
