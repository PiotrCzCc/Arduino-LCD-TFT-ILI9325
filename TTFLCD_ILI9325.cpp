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

#include "TTFLCD_ILI9325.h"

#include <stdint.h>

TFTLCD_ILI9325::TFTLCD_ILI9325() :
	Adafruit_GFX(TFTWIDTH, TFTHEIGHT) {
	
	nRESET_HIGH;
	RD_IDLE;
	nWR_HIGH;
	RS_DATA;
	nCS_HIGH;
	
	// to trzeba zmodyfikować 
	pinMode(A3, OUTPUT);   // Enable outputs
	pinMode(A2, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A0, OUTPUT);
	pinMode(A4, OUTPUT);
	
	setWriteDirInline();
	
	rotation  = 0;
	cursor_y  = cursor_x = 0;
	textsize  = 1;
	textcolor = 0xFFFF;
	_width    = TFTWIDTH;
	_height   = TFTHEIGHT;

} // END TFTLCD_ILI9325::TFTLCD_ILI9325

uint16_t TFTLCD_ILI9325::ReadRegisters16(uint8_t r) {
	uint16_t result;
	uint8_t hi, lo;

	nCS_LOW;
	RS_COMMAND;
	LCD_WRITE_8_bit(0x00);
	LCD_WRITE_8_bit(r);
	
	setReadDirInline();
	LCD_READ_8_bit(hi);
	LCD_READ_8_bit(lo);
	
	setWriteDirInline();
	nCS_HIGH;
	
	result = hi; result <<= 8; result |= lo;
	return result;
} // END TFTLCD_ILI9325::ReadRegisters16

// The basic methods that must be defined for Adafruit_GFX.
void TFTLCD_ILI9325::drawPixel(int16_t x, int16_t y, uint16_t color) {

	// Verification - Are the coordinates x,y in the screen?
	if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

	int16_t t;
	nCS_LOW;			// Active state of nCS
	
	switch(rotation) {
		case 1:
			t = x;
			x = TFTWIDTH  - 1 - y;
			y = t;
		break;
		case 2:
			x = TFTWIDTH  - 1 - x;
			y = TFTHEIGHT - 1 - y;
		break;
		case 3:
			t = x;
			x = y;
			y = TFTHEIGHT - 1 - t;
		break;
	}
	
	LCD_WRITE_16_bit(ILI9325_Horizontal_GRAM_Address_Set, x);			// Set GRAM horizontal Address
	LCD_WRITE_16_bit(ILI9325_Vertical_GRAM_Address_Set, y);				// Set GRAM Vertical Address
	LCD_WRITE_16_bit(ILI9325_Write_Data_to_GRAM, color);				// 
	
	nCS_HIGH;			// Idle state of nCS
	
} //END TFTLCD_ILI9325::drawPixel

void TFTLCD_ILI9325::LcdRegistersInit(void) {
	
	nCS_LOW;			// Active state of nCS
	
	// This are not documented - only in Application Notes for ILI9325 V0.22
	LCD_WRITE_16_bit(ILI9325_Internal_Timing_1, 0x3008);				// Set internal timing
	LCD_WRITE_16_bit(ILI9325_Internal_Timing_2, 0x0012);				// Set internal timing
	LCD_WRITE_16_bit(ILI9325_Internal_Timing_3, 0x1231);				// Set internal timing

	//************* Start Initial Sequence **********//
	LCD_WRITE_16_bit(ILI9325_Driver_Output_Control_1, 0x0100);			// Set SS=1 and SM=0 bit
	LCD_WRITE_16_bit(ILI9325_LCD_Driving_Wave_Control, 0x0700);			// Set 1 line inversion
	LCD_WRITE_16_bit(ILI9325_Entry_Mode, 0x1030);						// Set GRAM write direction and BGR=1
	LCD_WRITE_16_bit(ILI9325_Resizing_Control_Register, 0x0000);		// Set Resize register
	LCD_WRITE_16_bit(ILI9325_Display_Control_2, 0x0207);				// Set the back porch and front porch from AN(orginal in driver 0x0202)
	LCD_WRITE_16_bit(ILI9325_Display_Control_3, 0x0000);				// Set non-display area refresh cycle ISC[3:0]
	LCD_WRITE_16_bit(ILI9325_Display_Control_4, 0x0000);				// FMARK function
	LCD_WRITE_16_bit(ILI9325_RGB_Display_Interface_Control_1, 0x0000);	// RGB interface setting
	LCD_WRITE_16_bit(ILI9325_Frame_Maker_Position, 0x0000);				// Frame marker Position
	LCD_WRITE_16_bit(ILI9325_RGB_Display_Interface_Control_2, 0x0000);	// RGB interface polarity
	
	//*************Power On sequence ****************//
	LCD_WRITE_16_bit(ILI9325_Power_Control_1, 0x0000);					// SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WRITE_16_bit(ILI9325_Power_Control_2, 0x0007);					// DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WRITE_16_bit(ILI9325_Power_Control_3, 0x0000);					// VREG1OUT voltage
	LCD_WRITE_16_bit(ILI9325_Power_Control_4, 0x0000);					// VDV[4:0] for VCOM amplitude
	delay(200);															// Dis-charge capacitor power voltage 200ms
	
	LCD_WRITE_16_bit(ILI9325_Power_Control_1, 0x1190);					// SAP, BT[3:0], AP, DSTB, SLP, STB (other value: 0x1190 0x1290 0x1490 0x1690)
	LCD_WRITE_16_bit(ILI9325_Power_Control_2, 0x0221);					// DC1[2:0], DC0[2:0], VC[2:0] (other value: 0x0221 0x0227)
	delay(50);															// Dis-charge capacitor power voltage 50ms
	
	LCD_WRITE_16_bit(ILI9325_Power_Control_3, 0x001A);					// VREG1OUT voltage (other value: 0x0018 0x001A 0x001B 0x001C)
	delay(50);															// Dis-charge capacitor power voltage 50ms
	
	LCD_WRITE_16_bit(ILI9325_Power_Control_4, 0x1800);					// VDV[4:0] for VCOM amplitude (other: 0x1A00)
	LCD_WRITE_16_bit(ILI9325_Power_Control_7, 0x002A);					// Set VCM[5:0] for VCOMH (other: 0x0025)
	LCD_WRITE_16_bit(ILI9325_Frame_Rate_and_Color_Control, 0x000C);		// Set Frame Rate
	delay(50);															// Dis-charge capacitor power voltage 50ms
	
	LCD_WRITE_16_bit(ILI9325_Horizontal_GRAM_Address_Set, 0x0000);		// Set GRAM horizontal Address
	LCD_WRITE_16_bit(ILI9325_Vertical_GRAM_Address_Set, 0x0000);		// Set GRAM Vertical Address
	
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_1, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_2, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_3, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_4, 0x0206);					// Gradient adjustment registers
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_5, 0x0808);					// Amplitude adjustment registers
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_6, 0x0007);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_7, 0x0201);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_8, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_9, 0x0000);					// Gradient adjustment registers
	LCD_WRITE_16_bit(ILI9325_Gamma_Control_10, 0x0000);					// Amplitude adjustment registers
	
	//------------------ Set GRAM area ---------------//
	LCD_WRITE_16_bit(ILI9325_Horizontal_Address_Start_Position, 0x0000);	// Horizontal GRAM Start Address = 0
	LCD_WRITE_16_bit(ILI9325_Horizontal_Address_End_Position, 0x00EF);		// Horizontal GRAM End Address = 239
	LCD_WRITE_16_bit(ILI9325_Vertical_Address_Start_Position, 0x0000);		// Vertical GRAM Start Address = 0
	LCD_WRITE_16_bit(ILI9325_Vertical_Address_End_Position, 0x013F);		// Vertical GRAM End Address = 319
	
	LCD_WRITE_16_bit(ILI9325_Driver_Output_Control_2, 0xA700);				// Gate Scan Line
	LCD_WRITE_16_bit(ILI9325_Base_Image_Display_Control, 0x0003);			// NDL,VLE, REV (other: 0x0001)
	LCD_WRITE_16_bit(ILI9325_Vertical_Scroll_Control, 0x0000);				// Set scrolling line
	
	//-------------- Partial Display Control ---------//
	LCD_WRITE_16_bit(ILI9325_Partial_Image_1_Display_Position, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Partial_Image_1_Area_Start_Line, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Partial_Image_1_Area_End_Line, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Partial_Image_2_Display_Position, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Partial_Image_2_Area_Start_Line, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Partial_Image_2_Area_End_Line, 0x0000);
	
	//-------------- Panel Control -------------------//
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_1, 0x0010);
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_2, 0x0000);			// (other: 0x0600)
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_3, 0x0003);
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_4, 0x1100);
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_5, 0x0000);
	LCD_WRITE_16_bit(ILI9325_Panel_Interface_Control_6, 0x0000);
	
	LCD_WRITE_16_bit(ILI9325_Display_Control_1, 0x0133);					// 262K color and display ON
	
	nCS_HIGH;			// Idle state of nCS
	
} // END TFTLCD_ILI9325::LcdRegistersInit

// Hardware RESET method on TFTLCD_ILI9325
void TFTLCD_ILI9325::HWReset(void) {
	
	//All control singnals in idle state (High level)
	nCS_HIGH;
	RD_IDLE;
	nWR_HIGH;
	RS_DATA;
	
	// Reset sequence on Reset PIN
	nRESET_HIGH;			// Reset pin in idle state
	delay(10);				// Delay 10ms
	nRESET_LOW;				// Reset pin in active state
	delay(10);				// Delay 10ms - This delay time is necessary
	nRESET_HIGH;			// Reset pin in idle state
	delay(50);				// Delay 50ms
	
} // END TFTLCD_ILI9325::HWReset

// Fill Screen method optimized for ILI9325, command Write_Data_to_GRAM [0x22].
// This method replaces the original method from the Adafruit_GFX library.
void TFTLCD_ILI9325::fillScreen(uint16_t color) {
	uint8_t		hi = color >> 8,
				lo = color;
	uint32_t	i;
	const uint32_t	ram = (uint32_t)TFTWIDTH*(uint32_t)TFTHEIGHT;
	
	nCS_LOW;								// Active state of nCS
	
	// This is needed to fill the screen nicely. The screen is filled from one side to the other.
	LCD_WRITE_16_bit(ILI9325_Horizontal_GRAM_Address_Set, 0);			// Set GRAM horizontal Address =0
	LCD_WRITE_16_bit(ILI9325_Vertical_GRAM_Address_Set, 0);				// Set GRAM Vertical Address =0
	
	// used command: Write_Data_to_GRAM
	RS_COMMAND;
	LCD_WRITE_8_bit(0x00);
	LCD_WRITE_8_bit(ILI9325_Write_Data_to_GRAM);
	
	RS_DATA;
	if(hi == lo) {
		LCD_WRITE_8_bit(hi);
		LCD_WRITE_8_bit(lo);
		
		for(i=1; i<ram; i++) {
			// valid data is on the data port D[7:0], only WR strobe is needed
			LCD_WR_STROBE;
			LCD_WR_STROBE;
		}
	} else {
		for(i=0; i<ram; i++) {
			LCD_WRITE_8_bit(hi);
			LCD_WRITE_8_bit(lo);
		}
	}
	
	nCS_HIGH;								// Idle state of nCS
	
} // END TFTLCD_ILI9325::fillScreen