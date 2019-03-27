#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ImageReader.h>
#include <Adafruit_ILI9341.h>


#define TFT_DC 9
#define TFT_CS 10
#define SD_CS   4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ImageReader reader;

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
  stat = reader.drawBMP("/purple.bmp", tft, 0, 0);
}

void loop() {
  /*
  Adafruit_ImageReader reader;
  ImageReturnCode stat;
  Adafruit_Image img;
  int16_t pos = 10;
  stat = reader.drawBMP("ez.bmp", NULL, pos, pos, false);
  */
  // utilise une image pour affiche les informations;
  delay(60000);
}



