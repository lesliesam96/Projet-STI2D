#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// 240 / 320
// taille des cercles: 320/2 = 170
// reste pour le texte: 240-170=70
// marge des cercles: 5
// Rayon du cercle = (170-5*2)/2 = 80

cercleAff test(100, 100, 50, 300);

// Main programme
void setup() {
  Serial.begin(9600);
  tft.begin();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.println(x, HEX);
  tft.setRotation(-1);
  tft.fillScreen(0x5AA6);
  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(2);
  tft.setCursor(20,10);
  tft.print("Humidite:");
  tft.setCursor(170,10);
  tft.print("Temperature:");
}

void loop() {
  // utilise une image pour affiche les informations;
  delay(60000);
}



