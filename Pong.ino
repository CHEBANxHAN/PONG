#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
//#include <Arduino_ST7789_Fast.h>
#include <Arduino.h>

#define TFT_CS 11
#define TFT_DC 7 
#define TFT_RST 8

#define SCR_WD   240
#define SCR_HT   240

//#define SCREEN_WIDTH 240
//#define SCREEN_HEIGHT 240

//Arduino_ST7789 tft = Arduino_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int score1 = 0;
int score2 = 0;

int x1 = 230;
int y1 = 90;
int x2 = 0;
int y2 = 90;

int xb = 115;
int yb = 115;

int speed_1 = 10;
int velX = 1;
int velY = 1;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP); //Кнопка
  pinMode(4, INPUT_PULLUP); //Кнопка
  pinMode(5, INPUT_PULLUP); //Кнопка
  pinMode(6, INPUT_PULLUP); //Кнопка
  tft.init(240, 240, SPI_MODE2);//  ST7789 дисплей 240x240 px   
  tft.setRotation(2);                           // Поворот экрана  
  tft.fillScreen(ST77XX_BLACK);
 }

void loop() {
  boolean button1 = !digitalRead(3);
  boolean button2 = !digitalRead(4);
  boolean button3 = !digitalRead(5);
  boolean button4 = !digitalRead(6);
  int scorep1 = score1 - 1;
  int scorep2 = score2 - 1;
  if (button1 == 1) {
    y1 += speed_1; 
    tft.fillRect(x1, y1 - 120, 20, 120, ST77XX_BLACK);
  }
  if (button2 == 1) {
    y1 -= speed_1;                        
    tft.fillRect(x1, y1 + 120, 20, 120, ST77XX_BLACK);           
  }

  if (button3 == 1) {
    y2 += speed_1; 
    tft.fillRect(x2, y2 - 120, 20, 120, ST77XX_BLACK);            
  }
  if (button4 == 1) {
    y2 -= speed_1;                       
    tft.fillRect(x2, y2 + 120, 20, 120, ST77XX_BLACK);                 
  }
 

  if (y1 < 0) {
    y1 = 0;
  }

  if (y1 + 120 > 240) {
    y1 = 120;
  }

  if (y2 < 0) {
    y2 = 0;
  }

  if (y2 + 120 > 240) {
    y2 = 120;
  }

  xb += velX;
  yb += velY;

  if (xb < 0 or xb > 240 - 10) {
    velX = 0;
    velY = 0;
    speed_1 = 0;
  }

  if (yb < 0 or yb > 240 - 10) {
    velY = -velY;
  }

  if (xb + 10 > x1 and yb > y1 and yb + 10 < y1 + 120) {
    velX = -velX;
    scorep2++;
  }

  if (xb < x2 + 10 and yb > y2 and yb + 10 < y2 + 120) {
    velX = -velX;
    scorep1++;
  }

  if (velX > 0 or velY > 0) {
    tft.fillRect(xb - 1, yb - 1, 20, 20, ST77XX_BLACK);
  }
  if (velX < 0 or velY < 0) {
    tft.fillRect(xb + 1, yb + 1, 20, 20, ST77XX_BLACK);
  }

  if (scorep1 == score1) {
    score1++;
    tft.fillRect(30, 0, 30, 34, ST77XX_BLACK);
  }

  if (scorep2 == score2) {
    score2++;
    tft.fillRect(200, 0, 30, 34, ST77XX_BLACK);
  }

  
   
  tft.fillRect(x1, y1, 10, 120, ST77XX_WHITE);
  tft.fillRect(x2, y2, 10, 120, ST77XX_WHITE);
  tft.fillRect(xb, yb, 10, 10, ST77XX_WHITE);

  tft.setTextSize(4);
  tft.setCursor(30, 0);                            
  tft.print(score1);

  tft.setTextSize(4);
  tft.setCursor(200, 0);                            
  tft.print(score2);
  
 
}
