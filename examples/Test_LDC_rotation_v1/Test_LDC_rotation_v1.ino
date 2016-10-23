/* 
  Copyright (c) 2016 Piotr Czerczak
  All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <TTFLCD_ILI9325.h>

TFTLCD_ILI9325 MyLCD;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Test program for TFT LCD 240x320 with ILI9325"));

  MyLCD.HWReset();

  uint16_t myChipID = MyLCD.ReadRegisters16(ILI9325_DRIVER_CODE_REG);
  Serial.print(F("Chipset verification for ILI9325. Received value: "));
  Serial.println(myChipID, HEX);

  MyLCD.LcdRegistersInit();
}

void loop() {
  Serial.println(F("*** Main loop starts ***"));

  MyLCD.setRotation(0);
  MyLCD.fillScreen(BLACK_16b);
  MyLCD.drawRect(0, 0, 239, 319, WHITE_16b);
  //write tekst
  MyLCD.setTextColor(WHITE_16b);
  MyLCD.setTextSize(2);
  MyLCD.setCursor(5, 8);
  MyLCD.println("(0,0)");
  MyLCD.setCursor(152,8);
  MyLCD.println("(239,0)");
  MyLCD.setCursor(5,298);
  MyLCD.println("(0,319)");
  MyLCD.setCursor(50, 155);
  MyLCD.println("Rotation = 0");
  delay(3000);

  MyLCD.setRotation(1);
  MyLCD.fillScreen(BLACK_16b);
  MyLCD.drawRect(0, 0, 319, 239, YELLOW_16b);
  //write tekst
  MyLCD.setTextColor(YELLOW_16b);
  MyLCD.setTextSize(2);
  MyLCD.setCursor(5, 8);
  MyLCD.println("(0,0)");
  MyLCD.setCursor(232,8);
  MyLCD.println("(319,0)");
  MyLCD.setCursor(5,218);
  MyLCD.println("(0,239)");
  MyLCD.setCursor(90, 115);
  MyLCD.println("Rotation = 1");
  delay(3000);

  MyLCD.setRotation(2);
  MyLCD.fillScreen(BLACK_16b);
  MyLCD.drawRect(0, 0, 239, 319, GREEN_16b);
  //write tekst
  MyLCD.setTextColor(GREEN_16b);
  MyLCD.setTextSize(2);
  MyLCD.setCursor(5, 8);
  MyLCD.println("(0,0)");
  MyLCD.setCursor(152,8);
  MyLCD.println("(239,0)");
  MyLCD.setCursor(5,298);
  MyLCD.println("(0,319)");
  MyLCD.setCursor(50, 155);
  MyLCD.println("Rotation = 2");
  delay(3000);

  MyLCD.setRotation(3);
  MyLCD.fillScreen(BLACK_16b);
  MyLCD.drawRect(0, 0, 319, 239, MAGENTA_16b);
  //write tekst
  MyLCD.setTextColor(MAGENTA_16b);
  MyLCD.setTextSize(2);
  MyLCD.setCursor(5, 8);
  MyLCD.println("(0,0)");
  MyLCD.setCursor(232,8);
  MyLCD.println("(319,0)");
  MyLCD.setCursor(5,218);
  MyLCD.println("(0,239)");
  MyLCD.setCursor(90, 115);
  MyLCD.println("Rotation = 3");
  delay(3000);
}
