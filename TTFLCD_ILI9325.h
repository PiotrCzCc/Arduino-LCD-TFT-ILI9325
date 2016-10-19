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

Driver characteristics:
- 16bit colors support 32×64×32 = 65,536 colors (HighColor)
- colors order in init16_t (rrrrr gggggg bbbbb) GUICC_M556
*/
#ifndef __TFTLCD_ILI9325_H_
#define __TFTLCD_ILI9325_H_

#include <Adafruit_GFX.h>
#include <stdint.h>

#include "TTFLCD_ILI9325_registers.h"
#include "TTFLCD_shield_definition.h"

// Color name definition
#define BLACK_16b		0x0000
#define WHITE_16b		0xFFFF
#define RED_16b			0xF800
#define GREEN_16b		0x07E0
#define BLUE_16b		0x001F
#define CYAN_16b		0x07FF
#define MAGENTA_16b		0xF81F
#define YELLOW_16b		0xFFE0
#define GRAY_16b		0x7BEF
#define LIGHT_GRAY_16b	0xC618
#define BROWN_16b		0x8200
#define ORANGE_16b		0xFCA0
#define VIOLET_16b		0x9199
#define PURPLE_16b		0x780F

class TFTLCD_ILI9325 : public Adafruit_GFX {
  public:
  	TFTLCD_ILI9325();    // Constructor
  
	void 		drawPixel(int16_t x, int16_t y, uint16_t color);
	uint16_t	ReadRegisters16(uint8_t r);
	void		HWReset(void);
	void 		LcdRegistersInit(void);
	// This method replaces the original method from the library Adafruit_GFX
	void		fillScreen(uint16_t color);
	
  private:
//	void 		LcdRegistersInit(void);

};		//End TFTLCD_ILI9325 class declaration


#endif    // __TFTLCD_ILI9325_H_
