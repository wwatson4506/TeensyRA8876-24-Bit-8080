#include <Adafruit_GFX.h>
#include <_font_ComicSansMS.h>
#include "Fonts/FreeSansOblique12pt7b.h"
#include "RA8876_Config_8080.h"
#include "Arduino.h"
#include <RA8876_t41_p.h>

RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

void setup() {
  //I'm guessing most copies of this display are using external PWM
  //backlight control instead of the internal RA8876 PWM.
  //Connect a Teensy pin to pin 14 on the display.
  //Can use analogWrite() but I suggest you increase the PWM frequency first so it doesn't sing.
#if defined(BACKLITE)
  pinMode(BACKLITE, OUTPUT);
  digitalWrite(BACKLITE, HIGH);
#endif

  Serial.begin(115200);
  while (!Serial && millis() < 1000) {} //wait for Serial Monitor

  // Set 8/16bit mode
  tft.setBusWidth(USE_8080_8_BIT_MODE);
  // DB5.0 WR pin, RD pin, D0 pin.
  tft.setFlexIOPins(RA8876_WR,RA8876_RD,RA8876_D0);
  tft.begin(BUS_SPEED); // 

  //tft.setRotation(1);
  tft.fillScreen(COLOR16M_BLACK);

  tft.setTextColor(COLOR16M_WHITE);
  tft.println("Test of the default font");
  tft.println();
//  wait_for_keyboard();

  tft.setTextColor(COLOR16M_WHITE, COLOR16M_BLUE);
  tft.setFont(ComicSansMS_18);
  tft.println("Opaque ILI font ComicSansMS_18");
  tft.println();

//  wait_for_keyboard();
  int cursor_x = tft.getCursorX();
  int cursor_y = tft.getCursorY();
  tft.fillRect(cursor_x, cursor_y, tft.width(), 20, COLOR16M_RED);
//  wait_for_keyboard();
  tft.setTextColor(COLOR16M_GREEN);
  tft.println("Transparent ILI ComicSansMS_18");
  tft.println();
//  wait_for_keyboard();

  tft.setTextColor(COLOR16M_WHITE, COLOR16M_RED);
  tft.setFont(&FreeSansOblique12pt7b);
  tft.println("Opaque GFX FreeSansOblique12pt");
//  wait_for_keyboard();

  cursor_x = tft.getCursorX();
  cursor_y = tft.getCursorY();
  tft.fillRect(cursor_x, cursor_y, tft.width(), 20, COLOR16M_YELLOW);
//  wait_for_keyboard();
  tft.setTextColor(COLOR16M_BLUE);
  tft.println("Transparent GFX");

//  wait_for_keyboard();
  tft.setFontDef();
  tft.setTextColor(COLOR16M_GREEN);
  tft.setFontSize(1, true);
  tft.println("This is default font:");
  //tft.setFontSpacing(1);//now give 5 pix extra spacing between chars
  tft.println("ABCDEF 1 2 3 4 5 6 7");

}

void wait_for_keyboard() {
  Serial.println("Wait for any key to continue");
  while (Serial.read() == -1);
  while (Serial.read() != -1);
}

void loop()
{  }
