#include "flexio_teensy_mm.c"
#include "teensy41.c"
#include "RA8876_Config_8080.h"
#include <RA8876_t41_p.h>

RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

uint32_t start = 0;
uint32_t end =  0;
uint8_t busSpeed = 12; // 12MHz max in 16-bit mode. 20 or greater in 8-bit mode.

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
  tft.setBusWidth(USE_8080_16_BIT_MODE);
  // DB5.0 WR pin, RD pin, D0 pin.
  tft.setFlexIOPins(RA8876_WR,RA8876_RD,RA8876_D0);
  tft.begin(busSpeed); // 

  Serial.printf("%c DB5 board and RA8876 parallel 8080 mode testing (8-Bit/16-bit,DMA/ASYNC)\n\n",12);
//  Serial.print(CrashReport);

  Serial.print("Bus speed: ");
  Serial.print(busSpeed,DEC);
  Serial.println(" MHZ");
  Serial.print("Bus Width: ");
  Serial.print(tft.getBusWidth(),DEC);
  Serial.println("-bits");

  tft.graphicMode(true);
  tft.fillScreen(0x0000);
  tft.setRotation(0);
}

void loop() {
  start = micros();

  tft.pushPixels16bitAsync(flexio_teensy_mm,530,260,480,320); // 480x320
  tft.pushPixels16bitDMA(teensy41,1,1,480,320);    // FLASHMEM buffer

  end = micros() - start;
  Serial.printf("Wrote %d bytes in %dus\n\n",(575*424), end);
  waitforInput();
}

void waitforInput()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
