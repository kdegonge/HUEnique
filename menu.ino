#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int LED_COUNT = 3;
CRGB leds[LED_COUNT+1];
int HUE = 0;
int SAT = 255;
int BRT = 150;


void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 6>(leds, LED_COUNT);
  FastLED.clear();
  lcd.print("DeskLEDs V0.01c");
  lcd.setCursor(0, 1);
  lcd.print("(C)2018 DeGonge");
  delay(5000);
}

void loop()
{
  //knob positions
  int pot1 = analogRead(2);
  int pot2 = analogRead(3);
  int pot3 = analogRead(4);

  //print data to console
  /*Serial.print("pot1: ");
  Serial.print(pot1);
  Serial.print('\n');
  Serial.print("pot2: ");
  Serial.print(pot2);
  Serial.print('\n');
  Serial.print("pot3: ");
  Serial.print(pot3);
  Serial.print('\n');*/

  //update values
  HUE = pot1>>2;
  SAT = pot2>>2;
  BRT = pot3>>2;
  FastLED.showColor(CHSV(HUE, SAT, BRT));

  //update lcd with knob values
  lcd.clear();
  lcd.print("HUE   SAT   BRT");
  lcd.setCursor(0, 1);
  lcd.print(HUE);
  lcd.setCursor(6, 1);
  lcd.print(SAT);
  lcd.setCursor(12, 1);
  lcd.print(BRT);
  
  delay(25);
}
