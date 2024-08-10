/*************************************************************** 
 * graphics.ino 
 * 
 * Basic graphics test for RA8876 based display
 ***************************************************************/
#include "Arduino.h"
#include "RA8876_Config_8080.h"
#include <RA8876_t41_p.h>
#include <math.h>
#include "font_Arial.h"

RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

// Array of Simple RA8876 Basic Colors (24-Bit color)
PROGMEM uint32_t myColors[] = {
	0x000000, 0xffffff, 0xff0000, 0xED788D, 0xB41A1A, 0x00ff00, 0xA9EBA9,
	0x177817, 0x0000ff, 0x5757BF, 0x9393F1, 0x2727A7, 0xffff00, 0xF4F47E,
	0x96961A, 0x00CDF5, 0x9FE8F7, 0x138FA8, 0xFF00D7, 0xF075C5,0xA14380,
	0xA52A2A
};

int interations = 0;
int w, h;
int i = 0;

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

  tft.graphicMode(true);
  tft.setTextCursor(0,0);
  tft.setFont(Arial_14);
  tft.setTextColor(BLACK);
  tft.setRotation(0);
  w = tft.width()-1; h = tft.height()-STATUS_LINE_HEIGHT-1;
  tft.fillScreen(myColors[11]);
  graphicsTest();
  tft.setRotation(1);
  w = tft.width()-1; h = tft.height()-STATUS_LINE_HEIGHT-1;
  tft.fillScreen(myColors[11]);
  graphicsTest();
  tft.setRotation(2);
  w = tft.width()-1; h = tft.height()-STATUS_LINE_HEIGHT-1;
  tft.fillScreen(myColors[11]);
  graphicsTest();
  tft.setRotation(3);
  w = tft.width()-1; h = tft.height()-STATUS_LINE_HEIGHT-1;
  tft.fillScreen(myColors[11]);
  graphicsTest();
  tft.printStatusLine(0,myColors[1],myColors[11],"FINISHED!");

}

void loop() {
}

void graphicsTest()
{
  tft.printStatusLine(0,myColors[1],myColors[11],"Rectangles");
  interations = 3000;
  rectangles(0);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Rectangles 10 pixel line thickness");
  interations = 4000;
  rectangles(10);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Filled Rectangles");
  interations = 4000;
  filledRectangles();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Round Rectangles");
  interations = 30000;
  rRectangles(0);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Round Rectangles 10 pixel line thickness");
  interations = 4000;
  rRectangles(10);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Filled Round Rectangles");
  interations = 4000;
  filledRRectangles();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Circles");
  interations = 3000;
  drawcircles(0);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Circles 10 pixel circle thickness");
  interations = 4000;
  drawcircles(10);
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Filled Circles");
  interations = 4000;
  fillcircles();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Triangles");
  interations = 3000;
  drawTriangles();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Filled Triangles");
  interations = 4000;
  fillTriangles();
  tft.fillScreen(myColors[11]);
  delay(10);
  interations = 3000;
  tft.printStatusLine(0,myColors[1],myColors[11],"Ellipses");
  drawEllipses();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Filled Ellipses");
  interations = 4000;
  fillEllipses();
  tft.fillScreen(myColors[11]);
  delay(10);
  tft.printStatusLine(0,myColors[1],myColors[11],"Lines");
  interations = 3000;
  drawlines();
  tft.fillScreen(myColors[11]);
  delay(10);
}

// Draw random unfilled rectangle boxes
void rectangles(uint16_t thickness) {
  uint16_t x0, y0, x1, y1, c;
  uint16_t j;

  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(1,512);
    y0 = (uint16_t)random(1,288);
    x1 = (uint16_t)random(512,w);
    y1 = (uint16_t)random(288,h);
    c = (uint16_t)random(21);
    if(x0 > tft.width()) x0 = tft.width();
    if(y0 > tft.height()) y0 = tft.height();
    if(x1 > tft.width()) x1 = tft.width();
    if(y1 > tft.height()) y1 = tft.height();
    if(thickness > 0) {
      for(j = 1; j <= thickness; j++) {
        tft.drawRect(x0,y0,x1-x0,y1-y0,myColors[c]);
        if(x0 <= tft.width()) x0++;
        if(y0 <= tft.height()) y0++;
        if(x1 > 0) x1--;
        if(y1 > 0) y1--;
      }
    } else {
      tft.drawRect(x0,y0,x1-y0,y1-y0,myColors[c]);
    }
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random filled rectangle boxes
void filledRectangles(void) {
  uint16_t x0, y0, x1, y1, c;
  for(int i=0; i< interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    x1 = (uint16_t)random(w);
    y1 = (uint16_t)random(h);
    c = (uint16_t)random(21);
    tft.fillRect(x0,y0,x1-x0,y1-y0,myColors[c+1]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random round rectangle boxes
void rRectangles(uint16_t thickness) {
  uint16_t x0, y0, x1, y1, xr, yr, c;
  uint16_t j;

  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(1,512);
    y0 = (uint16_t)random(1,288);
    x1 = (uint16_t)random(512,w);
    y1 = (uint16_t)random(288,h);
    xr = 20; // Major Radius - Line Thickness must be less than
    yr = 20; // Minor Radius - Major and Minor radiuses by at
//                           - least half of xr and yr.
    c = (uint16_t)random(21);
    if(x0 > tft.width()) x0 = tft.width();
    if(y0 > tft.height()) y0 = tft.height();
    if(x1 > tft.width()) x1 = tft.width();
    if(y1 > tft.height()) y1 = tft.height();
    // Make sure major radius (xr) is less than x1 - x0
    // Must be xr * 2 + 1 less than x1 - x0
    // RA8876.pdf section 12.6 page 62
    if((xr * 2 + 1) >= (x1 - x0)) xr = (x1 - x0) / 2 - 1;
    // Same for minor radius (yr)
    if((yr * 2 + 1) >= (y1 - y0)) yr = (y1 - y0) / 2 - 1;
    if(thickness > 0) {
      for(j = 1; j <= thickness; j++) {
        tft.drawRoundRect(x0,y0,x1-x0,y1-y0,xr,yr,myColors[c]);
        if(x0 <= tft.width()) x0++;
        if(y0 <= tft.height()) y0++;
        if(x1 > 0) x1--;
        if(y1 > 0 ) y1--;
        if(xr > 0) xr--;
        if(yr > 0) yr--;
      }
    } else {
      tft.drawRoundRect(x0,y0,x1-x0,y1-y0,xr,yr,myColors[c]);
    }
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random filled round rectangle boxes
void filledRRectangles(void) {
  uint16_t x0, y0, x1, y1, xr, yr, c;

  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(1,512);
    y0 = (uint16_t)random(1,288);
    x1 = (uint16_t)random(512,w);
    y1 = (uint16_t)random(288,h);
    xr = 20; // Major Radius
    yr = 20; // Minor Radius
    c = (uint16_t)random(21);
    // Keep x,y within 1024x576 boundries
    if(x0 > tft.width()) x0 = tft.width();
    if(y0 > tft.height()) y0 = tft.height();
    if(x1 > tft.width()) x1 = tft.width();
    if(y1 > tft.height()) y1 = tft.height();
    // Make sure major radius (xr) is less than x1 - x0
    // Must be xr * 2 + 1 less than x1 - x0
    // RA8876.pdf section 12.6 page 62
    if((xr * 2 + 1) >= (x1 - x0)) xr = (x1 - x0) / 2 - 1;
    // Same for minor radius (yr)
    if((yr * 2 + 1) >= (y1 - y0)) yr = (y1 - y0) / 2 - 1;
    tft.fillRoundRect(x0, y0, x1-x0, y1-y0, xr, yr, myColors[c]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random circles
void drawcircles(uint16_t thickness) {
  uint16_t x0, y0, r, c;
  int j;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    r = (uint16_t)random(239);
    c = (uint16_t)random(21);
    if(x0-r <= 0) x0 += (uint16_t)r;
    if(y0-r <= 0) y0 += (uint16_t)r;
    if(x0+r >=  tft.width()) x0 = (uint16_t)(w - r);
    if(y0+r >= h) y0 = (uint16_t)(h - r);
    if(thickness > 0) {
      for(j = 1; j <= thickness; j++) {
        tft.drawCircle(x0, y0, r, myColors[c]);
        if(r > 0) r--;
      }
    } else {
      tft.drawCircle(x0, y0, r, myColors[c]);
    }
    tft.drawCircle(x0, y0, r, myColors[c]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random filled circles
void fillcircles(void) {
  uint16_t x0, y0, r, c;
  for(int i=0; i< interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    r = (uint16_t)random(239);
    c = (uint16_t)random(21);
    if(x0-r <= 0) x0 += (uint16_t)r;
    if(y0-r <= 0) y0 += (uint16_t)r;
    if(x0+r >=  w) x0 = (uint16_t)(w - r);
    if(y0+r >= h) y0 = (uint16_t)(h - r);
    tft.fillCircle(x0, y0, r, myColors[c]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random unfilled tritangles
void drawTriangles(void) {
  uint16_t x0, y0, x1, y1, x2, y2, c;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    x1 = (uint16_t)random(w);
    y1 = (uint16_t)random(h);
    x2 = (uint16_t)random(w);
    y2 = (uint16_t)random(h);
    c = (uint16_t)random(21);
    tft.drawTriangle(x0,y0,x1,y1,x2,y2,myColors[c+1]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random filled triangles
void fillTriangles(void) {
  uint16_t x0, y0, x1, y1, x2, y2, c;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    x1 = (uint16_t)random(w);
    y1 = (uint16_t)random(h);
    x2 = (uint16_t)random(w);
    y2 = (uint16_t)random(h);
    c = (uint16_t)random(21);
    tft.fillTriangle(x0,y0,x1,y1,x2,y2,myColors[c+1]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random unfilled ellipses
void drawEllipses(void) {
  int16_t  x0, y0, xr, yr;
  uint16_t color;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    xr = (uint16_t)random(239);
    yr = (uint16_t)random(239);
    color = (uint16_t)random(21);
    if(x0-xr <= 0) x0 += (uint16_t)xr;
    if(y0-yr <= 0) y0 += (uint16_t)yr;
    if(x0+xr >= w) x0 = (uint16_t)(w - xr);
    if(y0+yr >= h) y0 = (uint16_t)(h - yr);
    tft.drawEllipse(x0, y0, xr, yr, myColors[color]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random filled ellipses
void fillEllipses(void) {
  int16_t  x0, y0, xr, yr;
  uint16_t color;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(w);
    y0 = (uint16_t)random(h);
    xr = (uint16_t)random(239);
    yr = (uint16_t)random(239);
    color = (uint16_t)random(21);
    if(x0-xr <= 0) x0 += (uint16_t)xr;
    if(y0-yr <= 0) y0 += (uint16_t)yr;
    if(x0+xr >= w) x0 = (uint16_t)(w - xr);
    if(y0+yr >= h) y0 = (uint16_t)(h- yr);
    tft.fillEllipse(x0, y0, xr, yr, myColors[color]);
  }
  tft.fillStatusLine(myColors[11]);
}

// Draw random Lines
void drawlines(void) {
  uint16_t x0, y0, x1, y1, c;
  for(int i=0; i < interations; i++) {
    x0 = (uint16_t)random(1,w);
    y0 = (uint16_t)random(1,h);
    x1 = (uint16_t)random(1,w);
    y1 = (uint16_t)random(1,h);
     c = (uint16_t)random(21);
    if(x0 > tft.width()) x0 = tft.width();
    if(y0 > tft.height()) y0 = tft.height();
    if(x1 > tft.width()) x1 = tft.width();
    if(y1 > tft.height()) y1 = tft.height();
    tft.drawLine(x0,y0,x1,y1,myColors[c]);
  }
  tft.fillStatusLine(myColors[11]);
}
