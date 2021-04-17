#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#define PIN 5
#define N_LEDS 12

Adafruit_NeoPixel ring 
  = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const int rs = 6, e = 7, dB4 = 8, 
dB5 = 9, dB6 = 10, dB7 = 11;

LiquidCrystal lcd(rs, e, dB4, dB5, dB6, dB7);

float gasData = 0;
int safe_Lamp = 3;
int danger_Lamp = 2;
int alarm = 4;
int sensor = 0;
int sensorData = 500;

void setup()
{
   ring.begin();
   pinMode(safe_Lamp,OUTPUT);
   pinMode(danger_Lamp, OUTPUT);
   pinMode(alarm,OUTPUT);
   pinMode(sensor,INPUT);
   Serial.begin(9600);
   lcd.begin(16,2);
}

void loop()
{
    gasData = analogRead(sensor);
 
    digitalWrite(safe_Lamp,HIGH);
    digitalWrite(danger_Lamp,LOW);
    noTone(alarm);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NO DANGER");
    lcd.setCursor(0,1);
    lcd.print("Gas: ");
    lcd.setCursor(6, 1);
    lcd.print(gasData);
    delay(1000);
    chase(ring.Color(0, 255, 0)); 
    chase(ring.Color(0, 255, 0)); 
    chase(ring.Color(0, 255, 0));
 
  while(gasData > sensorData)
  {
    gasData = analogRead(sensor);
    digitalWrite(safe_Lamp,LOW);
    digitalWrite(danger_Lamp,HIGH);
    tone(alarm,1000,1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("!!!EVACUATION!!!");
    delay(1000);
    chase(ring.Color(255, 0, 0));
    chase(ring.Color(255, 0, 0)); 
    chase(ring.Color(255, 0, 0)); 
  }  
}

static void chase(uint32_t c) 
{
  for(uint16_t i=0; i<ring.numPixels() + 4; i++) 
  {
      ring.setPixelColor(i, c); 
      ring.setPixelColor(i-4, 0);
      ring.show();
      delay(10);
  }  
}

