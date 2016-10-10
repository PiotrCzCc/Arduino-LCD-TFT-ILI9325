#include <TTFLCD_ILI9325.h>
#include <TTFLCD_ILI9325_registers.h>

TFTLCD_ILI9325 MyLCD;

void setup() {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test - START"));

  uint16_t myChipID = MyLCD.ReadRegisters16(ILI9325_DRIVER_CODE_REG);
  Serial.println(myChipID, HEX);
}

void loop() {
  // put your main code here, to run repeatedly:

}
