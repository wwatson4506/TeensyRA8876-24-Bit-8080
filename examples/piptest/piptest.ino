// piptest.ino
// This example demonstrates some of the different capabilities
// of the RA8876. Formost, the two available PIP windows. PIP
// window 1 will always be on top of PIP window 2. It uses the
// setTMargins() function to create a window with a border that
// has adjustable thickness and cycle the colors of that border.
// It will repeatedly print the internal character set scrolling
// the window up as it prints. The window is basically a terminal
// window processing most ASCII control codes.
// There is a built in status line at the bottom of the screen that
// is 16 pixels in height with functions to support it.
#include "Arduino.h"
#include "RA8876_Config_8080.h"
#include <RA8876_t41_p.h>
#include <math.h>

RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

// Array of Simple RA8876 Basic Colors (24-Bit color)
PROGMEM uint32_t myColors[] = {
	0x000000, 0xffffff, 0xff0000, 0xED788D, 0xB41A1A, 0x00ff00, 0xA9EBA9,
	0x177817, 0x0000ff, 0x5757BF, 0x9393F1, 0x2727A7, 0xffff00, 0xF4F47E,
	0x96961A, 0x00CDF5, 0x9FE8F7, 0x138FA8, 0xFF00D7, 0xF075C5,0xA14380,
	0xA52A2A
};

uint8_t onOff = 1; // Enable PIP
uint8_t pipNo = 1; // PIP number 1
uint16_t xp = 0;   // x coord. (source), for PIP
uint16_t yp = 0;   // y coord. (source), for PIP
uint16_t xd = 0;   // x coord. of displayed PIP window
uint16_t yd = 40;  // y coord. of displayed PIP window
uint16_t xw = 320; // x width of displayed window
uint16_t yh = 240; // y height of displayed window
const PROGMEM char *title ="PIP+ DEMO\n";
const PROGMEM char *pip1 ="PIP WINDOW #1";
const PROGMEM char *pip2 ="PIP WINDOW #2";
uint8_t len = 0;
uint8_t c = 32;

int pipDelay = 0; // delayMicroseconds(pipDelay) Set to 0 for as fast as it gets
                  // or tone it down?
uint16_t thickness = 10; // drawRect() line thickness (Brush Size)
uint16_t x = 0;
uint16_t y = 0;
uint16_t w = 0;
uint16_t h = 0;
uint8_t fw = 0;
uint8_t fh = 0;

// Draw a border for the text window
void drawBorder(void) {
  uint64_t color = 0;
  fw = tft.getFontWidth();
  fh = tft.getFontHeight();
  x = (10*fw)-thickness;
  y = (2*fh)-thickness;
  w = tft.width()-(20*fw) + 2*thickness;
  h = tft.height()-(4*fh) + 2*thickness;
  color = random(0,65535) | 0x5555;
  for(int i = 1; i <= thickness; i++) {
    tft.drawRect(x, y, w, h, color);
    x+=1;
    y+=1;
    w-=2;
    h-=2;
  }
}

// Put it all together
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

  tft.setFontSize(2,false);
  tft.setCursor(0,0);
  tft.fillScreen(myColors[11]);
  len = strlen(title);
  tft.setTextColor(myColors[6],myColors[11]);
  tft.setCursor((tft.width()/2) - (len/2)*tft.getFontWidth(),0);
  tft.println(title);
  tft.setTextColor(myColors[1],myColors[11]);
  tft.setFontSize(1,true);
  tft.setTMargins(10, 2, 10, 2); //Setup a text window
	
  // Setup PIP window #1 on screen page #4
  tft.setTextColor(myColors[1],myColors[11]);
  tft.selectScreen(SCREEN_4); // Select screen page 4
  tft.fillScreen(myColors[13]);
  tft.setFontSize(1,true); // Set 12x24 font size
  tft.setCursor(0,0);
  tft.setTextColor(myColors[0],myColors[13]);
  tft.println(pip1);
  tft.fillCircle(xw / 2, yh / 2, 100, myColors[2]);
  // Setup PIP window #2 on screen page #5
  tft.setTextColor(myColors[1],myColors[11]);
  tft.selectScreen(SCREEN_5); // Select screen page 5
  tft.fillScreen(myColors[6]);
  tft.setFontSize(2,true); // Set 16x32 font size
  tft.setCursor(0,0);
  tft.setTextColor(myColors[0],myColors[6]);
  tft.println(pip2);
  tft.fillRect(xw - 300, yh - 200 , 100, 100, myColors[15]);
  // Set screen page #1 as the active screen page
  tft.selectScreen(SCREEN_1); // Select home page
}

void loop() {
  char STR1[256];
  uint32_t start = millis();
  uint32_t finished = 0;
  onOff = 1; // Enable PIP's
  pipNo = 1; // Select and enable PIP #1
  tft.PIP(onOff,pipNo,SCREEN_4,xp,yp,tft.width(),xd,yd,xw,yh);
  pipNo = 2; //Select and enable PIP #2
  tft.PIP(onOff,pipNo,SCREEN_5,xp,yp,tft.width(),xd+700,yd+215,xw,yh);
  pipNo = 1; // Select and move PIP #1
  drawBorder();
  for(int i=0; i <= 700; i++) {
    tft.PIP(onOff,pipNo,SCREEN_4,xp,yp,tft.width(),xd+i,yd,xw,yh);
    delayMicroseconds(pipDelay);
    tft.setTextColor(myColors[i % 22],myColors[11]);
    tft.write(c); // Print character set in text window
    c++;
    if(c == 255) c = 32;
  }
  drawBorder();
  pipNo = 2; // Select and move PIP #2
  for(int i=700; i >= 0; i--) {
    tft.PIP(onOff,pipNo,SCREEN_5,xp,yp,tft.width(),xd+i,yd+215,xw,yh);
    delayMicroseconds(pipDelay);
    tft.setTextColor(myColors[i % 22],myColors[11]);
    tft.print(c); // Print character set in text window
    c++;
    if(c == 255) c = 32;
  }
  finished = millis()-start;
  // Print some stats to the status line
  sprintf(STR1,"pipDelay: %lu uS, Loop Cycle Time: %lu ms, Use pipDelay=0 for fastest Loop time.",(unsigned long)pipDelay, (unsigned long)finished);
  tft.printStatusLine(0,myColors[13],myColors[11],STR1);
}
