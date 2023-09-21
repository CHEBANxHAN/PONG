#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
#include <Arduino.h> 

#define TFT_CS 11
#define TFT_DC 7 
#define TFT_RST 8 

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int sum = 0;
int idx = 1;
// Массивы радиостанций
float mas[] = {88.3, 88.7, 89.5, 90.3, 92.4, 96.8, 100.9, 102.5, 103.0, 104.2, 104.7, 105.0, 105.7, 106.2, 107.4};
char* name_station[] = {"Retro FM", "Umor FM", "Megapolis FM", "Avtoradio", "Radio    Dacha", "Deti FM", "Radio    VERA", "Camedi   Radio", "Radio    Shanson", "Radio    ENERGY", "7 na semi holmah", "Radio    Kniga", "Russkoe  Radio", "Evropa   Plus", "Hit FM"};
// массив для отправки I2C
byte arr[5]={0,0,0xB0,0x10,0x00};

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
  pinMode(9, INPUT_PULLUP); //Кнопка
  pinMode(10, INPUT_PULLUP); //Кнопка
  tft.init(240, 240, SPI_MODE2);//  ST7789 дисплей 240x240 px   
  tft.setRotation(2);                           // Поворот экрана  
  tft.fillScreen(ST77XX_BLACK);

}

void loop() {
  boolean button5 = !digitalRead(9);
  boolean button6 = !digitalRead(10);
  tft.setTextSize(4);
  tft.setCursor(0, 90);                            
  tft.print("Radio And Pong");
  if(button5 == 1) {
    tft.fillScreen(ST77XX_BLACK);
    while (true) {
      boolean button1 = !digitalRead(3);
      boolean button2 = !digitalRead(4);
      if (button1 == 1) {
        sum++;
        idx++;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
        delay(1000);
      }
      if (button2 == 1) {
        sum--;
        idx--;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
        delay(1000);
      }
      if (sum > 14) {
        sum = 0;
        idx = 1;
      }
      if (sum < 0) {
        sum = 14;
        idx = 15;
      }
      Wire.begin();
      // запуск радио
      unsigned int freqB = 4 * (mas[sum] * 1000000 + 225000) / 32768;
      byte freqH = freqB >> 8;
      byte freqL = freqB & 0XFF;
      arr[0]= freqH;
      arr[1]= freqL;
      Wire.beginTransmission(0x60);
      for(int i=0;i<5;i++) {
        Wire.write(arr[i]);
      }
      Wire.endTransmission();
    
      //Вывод информации на дисплей
      tft.setTextSize(4);
      tft.setCursor(0, 5);                            
      tft.print(mas[sum]);
      tft.setCursor(155, 5);
      tft.setTextSize(4);                             
      tft.print("MHz");
    
      tft.setTextSize(4);
      tft.setCursor(3, 100);                            
      tft.print(name_station[sum]);
    
      tft.setTextSize(4);
      tft.setCursor(5, 210);                            
      tft.print("Chanal- ");
      tft.setTextSize(4);
      tft.setCursor(180, 210);
      tft.print(idx);
      
      Serial.println(mas[sum]);
    }
  }
  if(button6 == 1){
    tft.init(240, 240, SPI_MODE2);//  ST7789 дисплей 240x240 px   
    tft.setRotation(2);                           // Поворот экрана  
    tft.fillScreen(ST77XX_BLACK);
    while (true) {
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
  }
}
