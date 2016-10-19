# Note: library under construction - not working

# Arduino LCD TFT Library for ILI9325 Liltek driver

This is the dedicated graphics hardware-specific library for ILI9325 TFT LCD display driver. It needs to be paired with the core graphics Adafruit GFX Library.

Adafruit GFX graphics core library derive from https://github.com/adafruit/Adafruit-GFX-Library

ILI9325 chip features:
- 240x320 RGB resolution
- 262,144 display color (Note: The library supports only 16-bit color - 65,536 colors.)

LCD TFT 2,4' shield features:
- shield compatible with Arduino UNO
- 8-bit Parallel Peripheral Interface (DB17-DB10 data pins are used to transfer)
- two DP74HC245 CMOS level drivers for 5/3V conversion

**LCD TFT 2,4' shield**
====================
![Picture1] | ![Picture2]
------------ | -------------
![Picture3] | ![Picture4]

![Picture5]

[Picture1]:https://raw.githubusercontent.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325/master/doc/2.4_TFT_LCD_ILI9325_3.jpg
[Picture2]:https://raw.githubusercontent.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325/master/doc/2.4_TFT_LCD_ILI9325_2.jpg
[Picture3]:https://raw.githubusercontent.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325/master/doc/2.4_TFT_LCD_ILI9325_4.jpg
[Picture4]:https://raw.githubusercontent.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325/master/doc/2.4_TFT_LCD_ILI9325_1.jpg
[Picture5]:https://raw.githubusercontent.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325/master/doc/2.4_TFT_LCD_ILI9325_5.jpg
