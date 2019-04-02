#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ImageReader.h>
#include <Adafruit_ILI9341.h>


#define TFT_DC 9
#define TFT_CS 10
#define SD_CS   4

#define TEMPX 5
#define TEMPY 80

#define HUMIX 170
#define HUMIY 80

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ImageReader reader;

// 240 / 320
// taille des cercles: 320/2 = 170

// reste pour le texte: 240-170=70
// marge des cercles: 5
// Rayon du cercle = (170-5*2)/2 = 80

int mesure(float& temp, float& humi);
void affPrint(const float& temp, const float& humi);
void affTier(const float& temp, const float& humi);
void drawTemp(const short& nb);
void drawHumi(const short& nb);

float CO_d = 0;
float humi = 0;
float temp = 0;

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
  tft.setTextColor(ILI9341_WHITE); 

}

void loop() {
  CO_d = mesure(temp, humi);
  
  tft.setTextSize(2);
  tft.setCursor(20,10);
  tft.print("Humidite:");
  tft.setCursor(170,10);  
  tft.print("Temperature:");
  Adafruit_ImageReader reader;
  ImageReturnCode stat;
  stat = reader.drawBMP("/cercle.bmp", tft, TEMPX, TEMPY, false);
  stat = reader.drawBMP("/cercle.bmp", tft, HUMIX, HUMIY, false);

  affPrint(temp, humi);
  affTier(temp, humi);
  // utilise une image pour affiche les informations;
  delay(60000);
}

int mesure(float& temp, float& humi) {
  // recuper le code de jerem
  // pour les variables:
  // temp = #Température
  // humi = #Humidité

  // Mesurer le taux de CO2 (ppm)
  // dans le int de return
  return 0;
}

void affPrint(const float& temp, const float& humi) {
  Serial.print("Température: ");
  Serial.print(temp);
  Serial.print("°C,     Humidité: ");
  Serial.print(humi);
  Serial.println("%");
  Serial.println("--------------------");
  Serial.println("Wait: 1min");
  Serial.println("--------------------");
}

void affTier(const float& temp, const float& humi) {
  tft.setCursor(44,80);
  tft.print(temp);
  tft.setCursor(209,80);
  tft.print(humi);
  if (temp >= 20.0) {
    drawTemp(3); 
  } else if (temp >= 15) {
    drawTemp(2);
  } else if (temp >= 10) {
    drawTemp(1);
  }
  if (humi >= 65.0) {
    drawHumi(3);
  } else if (humi >= 50.0) {
    drawHumi(2);
  } else if (humi >= 35.0) {
    drawHumi(1); 
  }
  
}

void drawTemp(const short& nb) {
  Adafruit_ImageReader reader;
  ImageReturnCode stat;
  if (nb == 1) {
    stat = reader.drawBMP("/vert.bmp", tft, TEMPX, TEMPY, false);
    Serial.println("Draw: green temperatur");
  }
  if (nb == 2) {
    stat = reader.drawBMP("/jaune.bmp", tft, TEMPX, TEMPY, false);
    Serial.println("Draw: yellow temperatur");
  } 
  if (nb == 3) {
    stat = reader.drawBMP("/rouge.bmp", tft, TEMPX, TEMPY, false);
    Serial.println("Draw: red temperatur");
  }
}

void drawHumi(const short& nb) {
  Adafruit_ImageReader reader;
  ImageReturnCode stat;
  if (nb == 1) {
    stat = reader.drawBMP("/vert.bmp", tft, HUMIX, HUMIY, false);
    Serial.println("Draw: green humidity");
  }
  if (nb == 2) {
    stat = reader.drawBMP("/jaune.bmp", tft, HUMIX, HUMIY, false);
    Serial.println("Draw: yellow humidity");
  } 
  if (nb == 3) {
    stat = reader.drawBMP("/rouge.bmp", tft, HUMIX, HUMIY, false);
    Serial.println("Draw: red humidity");
  }
}




