// TeensyRA8876_24-Bit_testing.ino

#include "RA8876_Config_8080.h"
#include <RA8876_t41_p.h>

//#define BACKLITE 5 //External backlight control connected to this Arduino pin
RA8876_t41_p tft = RA8876_t41_p(RA8876_8080_DC,RA8876_8080_CS,RA8876_8080_RESET);

uint8_t busSpeed = 12;

//*****************************************************************************
// Un-comment one the three  sections here and the corresponding section below.
//*****************************************************************************
/*
#include "parrots.h"
char *pixel1, *data1 = header_data1;
int i1 = width1 * height1;
char *processed_data1 = pixel1 = (char *)malloc(i1 * 4 + 1);
*/
/*
#include "images_1.h"
char *pixel2, *data2 = header_data2;
int i2 = width2 * height2;
char *processed_data2 = pixel2 = (char *)malloc(i2 * 4 + 1);
*/

#include "Original-image-24bit-RGB.h"
char *pixel3, *data3 = header_data3;
int i3 = width3 * height3;
char *processed_data3 = pixel3 = (char *)malloc(i3 * 4 + 1);

//****************************************************************************

// Trigraph to 24-bit RGB decoder
void trigraphDecode(int i, char *pixel, char *data) {
  while(i-- > 0) {
    pixel[0] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33)));
    pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2));
    pixel[2] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4));
    pixel[3] = 0;
    data += 4;
    pixel += 4;
  }
}

void setup() {
  while (!Serial && millis() < 3000) {} //wait for Serial Monitor
  Serial.printf("%c MicroMod Board and RA8876 parallel 8080 mode testing (8-Bit/16-BitDMA)\n\n",12);
//  Serial.print(CrashReport);
//  pinMode(WINT, INPUT); // For XnWAIT signal if connected and used.
 
  // Set 16bit mode
  tft.setBusWidth(16);
  // DB5.0 WR pin, RD pin, D0 pin.
  tft.setFlexIOPins(RA8876_WR,RA8876_RD,RA8876_D0);
  tft.begin(busSpeed);// 20 is working in 8bit and 16bit mode on T41
  delay(100);

  Serial.print("Bus speed: ");
  Serial.print(busSpeed,DEC);
  Serial.println(" MHZ");
  Serial.print("Bus Width: ");
  Serial.print(tft.getBusWidth(),DEC);
  Serial.println("-bits");

//  tft.Select_Main_Window_24bpp();

  tft.fillScreen(COLOR16M_BLACK);

}

void loop() {
//*******************************************************************************
// Un-comment one of the three sections here and the corresponding section above.
//*******************************************************************************
/*
  trigraphDecode(i1, pixel1, data1);
  tft.writeRect(500,50,width1,height1,(uint32_t *)processed_data1);
//  tft.pushPixels16bitAsync((uint32_t *)processed_data1,10,10,width1,height1); //16-Bit only at this time
//  tft.pushPixels16bitDMA((uint32_t *)processed_data1,0,0,width1,height1);  //16-Bit only at this time
*/
/*
  trigraphDecode(i2, pixel2, data2);
  tft.writeRect(500,50,width2,height2,(uint32_t *)processed_data2);
//  tft.pushPixels16bitAsync((uint32_t *)processed_data2,10,10,width2,height2); //16-Bit only at this time
//  tft.pushPixels16bitDMA((uint32_t *)processed_data2,0,0,width2,height2);  //16-Bit only at this time
*/


  trigraphDecode(i3, pixel3, data3);
  tft.writeRect(500,50,width3,height3,(uint32_t *)processed_data3);
//  tft.pushPixels16bitAsync((uint32_t *)processed_data3,10,10,width3,height3); //16-Bit only at this time
//  tft.pushPixels16bitDMA((uint32_t *)processed_data3,0,0,width3,height3);  //16-Bit only at this time

//*******************************************************************************

  waitforInput();
  tft.setFontSize(2);
  tft.drawSquareFill(10,10,100,100,0xFF0000);
  tft.setTextColor(COLOR16M_RED,COLOR16M_BLACK);
  tft.textxy(0,4);
  tft.print("24-BIT RED");

  tft.drawSquareFill(210,210,300,300,0x00FF00);
  tft.setTextColor(COLOR16M_GREEN);
  tft.textxy(10,10);
  tft.print("24-BIT GREEN");

  tft.drawSquareFill(410,410,500,500,0x0000FF);
  tft.setTextColor(COLOR16M_BLUE);
  tft.textxy(23,16);
  tft.print("24-BIT BLUE");
  waitforInput();
}

void waitforInput()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
