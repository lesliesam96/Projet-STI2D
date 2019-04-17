#include "DHT.h"
#include <SPI.h>
#include <SD.h>
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

 Serial.println("DHTxx test!");
 dht.begin();
}
void loop()
{

 // La lecture du capteur prend 250ms
 // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t))
 
 {
   Serial.println("Failed to read from DHT sensor!");
 }
 
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, true);


   myFile = SD.open("test.txt", FILE_WRITE);
   if (myFile) {
    Serial.println("Writing to test.txt...");
     myFile.print("Humidite: ");
     myFile.print(h);
     myFile.println(" %\t");
     myFile.print("Temperature: ");
     myFile.print(t);
     myFile.println(
      " *C ");
     myFile.close();
    Serial.println("done.");
      } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
     
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
     Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  delay(60000);
}
