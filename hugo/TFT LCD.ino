#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include "..\Adafruit_ImageReader_Library-1.0.7\Adafruit_ImageReader.h"
#include <Adafruit_ILI9341.h>


#define TFT_DC 9
#define TFT_CS 10
#define SD_CS   4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);



// 240 / 320
// taille des cercles: 320/2 = 170

// reste pour le texte: 240-170=70
// marge des cercles: 5
// Rayon du cercle = (170-5*2)/2 = 80

// Main programme
void setup() {
  if (!SD.begin(SD_CS)) {
    Serial.println("Error SD");
  }
  Serial.begin(9600);
  tft.begin();
  Adafruit_ImageReader reader();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.println(x, HEX);
  tft.setRotation(-1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(2);
  tft.setCursor(20,10);
  tft.print("Humidite:");
  tft.setCursor(170,10);
  tft.print("Temperature:");
  ImageReturnCode stat;
  Adafruit_Image img;
  stat = reader.loadBMP("/cercle.bmp", img)
}

void loop() {
  // utilise une image pour affiche les informations;
  delay(60000);
}


