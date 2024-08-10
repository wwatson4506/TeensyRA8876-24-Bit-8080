# TeensyRA8876-24-Bit-8080
## A RA8876 8080 parallel driver 24-Bit color library for Teensy boards and variants.

This library is designed to be used with the TeensyRa8876-24-Bit-GFX-Common library and can be found here:
- https://github.com/wwatson4506/TeensyRA8876-24-Bit-GFX-Common

This driver also uses a new FlexIO library found here:
- https://github.com/KurtE/FlexIO_t4/tree/master

Communication with the Teensy is accomplished using the 8080 parallel mode of FlexIO. To install unzip the zip file in the Arduino/libraries folder.

Example sketches can be found in the TeensyRA8876-24-Bit-8080 and TeensyRA8876-24-Bit-SPI examples folders.

# PINOUTS
*** CONNECTING THE TEENSY TO THE ER-TFTM101-1 in FlexIO 8080 mode***

40 pin dual inline connector pinouts can be found here.

https://www.buydisplay.com/download/interfacing/ER-TFTM101-1_RTP_Interfacing.pdf

## WIRED
### Dev Board 5 <_______> RA8876

      PIN                     PIN
*********************************
Use These 8 data lines for 8-bit data bus.
- D0  40 _______________> 15 
- D1  41 _______________> 16
- D2  42 _______________> 17 
- D3  43 _______________> 18 
- D4  44 _______________> 19
- D5  45 _______________> 20
- D6  06 _______________> 21
- D7  09 _______________> 22
*********************************
Use These 8 data lines for 16-bit data bus.
- D8  32 _______________> 23  
- D9  47 _______________> 24
- D10 48 _______________> 25 
- D11 49 _______________> 26 
- D12 08 _______________> 27
- D13 07 _______________> 28
- D14 50 _______________> 29
- D15 51 _______________> 30
*********************************
- RD  52 _______________> 05
- WR  53 _______________> 06
- CS  11 _______________> 07
- RS  13 _______________> 08
- RST 12 _______________> 11
- BL  3.3V (BACKLITE) ____> 14
- TFT 5V ________________> 3,4,37,38
- GND    ________________> 1,2,13,31,39,40

### Teensy 4.1 <________> RA8876

      PIN                     PIN
*********************************
Use These 8 data lines for 8-bit data bus.
- D0  40 _______________> 19 
- D1  41 _______________> 18
- D2  42 _______________> 14
- D3  43 _______________> 15
- D4  44 _______________> 40
- D5  45 _______________> 41
- D6  06 _______________> 17
- D7  09 _______________> 16
*********************************
Use These 8 data lines for 16-bit data bus.
- D8  32 _______________> 22  
- D9  47 _______________> 23
- D10 48 _______________> 20
- D11 49 _______________> 21
- D12 08 _______________> 38
- D13 07 _______________> 39
- D14 50 _______________> 26
- D15 51 _______________> 27
*********************************
- RD  37 _______________> 05
- WR  36 _______________> 06
- CS  11 _______________> 07
- RS  13 _______________> 08
- RST 12 _______________> 11
- BL  3.3V (BACKLITE) ____> 14
- TFT 5V ________________> 3,4,37,38
- GND    ________________> 1,2,13,31,39,40

# This is WIP. More to come.

