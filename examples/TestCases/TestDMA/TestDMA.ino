#include "Teensy41_Cardlike.h"
#include "flexio_teensy_mm.c"
#include "teensy41.c"
#include "RA8876_Config_8080.h"
#include <RA8876_t41_p.h>

RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

uint32_t start = 0;
uint32_t end =  0;
uint8_t busSpeed = 12;

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
  tft.begin(busSpeed); // 12 MHz

  Serial.printf("%c MicroMod Board and RA8876 parallel 8080 mode testing (8Bit/DMA)\n\n",12);
//  Serial.print(CrashReport);

  Serial.print("Bus speed: ");
  Serial.print(busSpeed,DEC);
  Serial.println(" MHZ");
  Serial.print("Bus Width: ");
  Serial.print(tft.getBusWidth(),DEC);
  Serial.println("-bits");

  tft.graphicMode(true);
  tft.setRotation(0);
}

void loop() {
//  tft.pushPixels16bitAsync(teensy41_Cardlike,10,10,575,424);
//  tft.pushPixels16bitAsync(flexio_teensy_mm,0,0,480,320); // 480x320
//  tft.pushPixels16bitAsync(teensy41,0,0,480,320); // 480x320
//  tft.writeRect(10,10,575,424,teensy41_Cardlike);
//  tft.writeRect(10,280,480,320,teensy41);
//  tft.writeRect(530,0,480,320,flexio_teensy_mm);

  tft.fillScreen(0x0010);
  start = micros();
  tft.pushPixels16bitDMA(teensy41_Cardlike,1,1,575,424);    // FLASHMEM buffer
  end = micros() - start;
  Serial.printf("Wrote %d bytes in %dss\n\n",575*424, end);
  waitforInput();
  tft.fillScreen(0x0010);
  start = micros();
  tft.pushPixels16bitDMA(teensy41,1,1,480,320);    // FLASHMEM buffer
  end = micros() - start;
  Serial.printf("Wrote %d bytes in %dus\n\n",480*320, end);
  waitforInput();
  tft.fillScreen(0x0010);
  start = micros();
  tft.pushPixels16bitDMA(flexio_teensy_mm,530,260,480,320); // FLASHMEM buffer
  end = micros() - start;
  Serial.printf("Wrote %d bytes in %dus\n\n",480*320, end);
  waitforInput();
}

void waitforInput()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
