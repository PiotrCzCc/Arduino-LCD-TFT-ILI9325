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
#ifndef __TFTLCD_SHIELD_DEFINITION_H_
#define __TFTLCD_SHIELD_DEFINITION_H_

#define TFTWIDTH   240
#define TFTHEIGHT  320

//
// TFTLCD shield control lines definition
// 
#define nRD_PORT PORTC				// A0 pin
#define nRD_MASK B00000001			// nRS - Read Strobe signal (active - L)

#define nWR_PORT PORTC				// A1 pin
#define nWR_MASK B00000010			// nWR - Write Strobe signal (active - L)

#define RS_PORT PORTC				// A2 pin
#define RS_MASK B00000100			// RS - Register Select signal (index-status - L, control - H)

#define nCS_PORT PORTC				// A3 pin
#define nCS_MASK B00001000			// nCS - Chip Select signal (active - L)

#define nRESET_PORT PORTC			// A4 pin
#define nRESET_MASK B00010000		// nRESET - Chip Reset signal (active - L)


// Control signals are ACTIVE LOW (idle is HIGH)
// Command/Data: LOW = command, HIGH = data
// These are single-instruction operations and always inline
#define RD_ACTIVE		nRD_PORT &= ~nRD_MASK
#define RD_IDLE			nRD_PORT |=  nRD_MASK
#define nWR_LOW			nWR_PORT &= ~nWR_MASK				// Active state of nWR
#define nWR_HIGH		nWR_PORT |=  nWR_MASK				// Idle state of nWR
#define RS_COMMAND		RS_PORT &= ~RS_MASK
#define RS_DATA			RS_PORT |=  RS_MASK
#define nCS_LOW			nCS_PORT &= ~nCS_MASK				// Active state of nCS
#define nCS_HIGH		nCS_PORT |=  nCS_MASK				// Idle state of nCS
#define nRESET_LOW		nRESET_PORT &= ~nRESET_MASK			// Active state of nRESET
#define nRESET_HIGH		nRESET_PORT |=  nRESET_MASK			// Idle state of nRESET

// 
#define LCD_WRITE_8_bit(d) {                          \
    PORTD = (PORTD & B00000011) | ((d) & B11111100);  \
    PORTB = (PORTB & B11111100) | ((d) & B00000011);  \
	LCD_WR_STROBE; }

// Set value of TFT register: 8-bit address, 16-bit value
// hi & lo are temp vars
// write command 0x00, a
// write data d (hi, lo)
#define LCD_WRITE_16_bit(a, d) {                      \
  uint8_t hi, lo;                                     \
  RS_COMMAND;                                         \
  LCD_WRITE_8_bit(0x00);                              \
  LCD_WRITE_8_bit(a);                                 \
  RS_DATA;                                            \
  hi = (d) >> 8; lo = (d);                            \
  LCD_WRITE_8_bit(hi);                                \
  LCD_WRITE_8_bit(lo); }

//
#define LCD_READ_8_bit(result) {                      \
    RD_ACTIVE;                                        \
    DELAY7;                                           \
    result = (PIND & B11111100) | (PINB & B00000011); \
	RD_IDLE; }

// Data write strobe
// Action: idle H -> change active L -> change idle H
#define LCD_WR_STROBE { nWR_LOW; nWR_HIGH; }

#define setWriteDirInline() { DDRD |=  B11111100; DDRB |=  B00000011; }
#define setReadDirInline()  { DDRD &= ~B11111100; DDRB &= ~B00000011; }


// NOTE: direct from https://github.com/samuraijap/TFTLCD-Library
// Pixel read operations require a minimum 400 nS delay from RD_ACTIVE
// to polling the input pins.  At 16 MHz, one machine cycle is 62.5 nS.
// This code burns 7 cycles (437.5 nS) doing nothing; the RJMPs are
// equivalent to two NOPs each, final NOP burns the 7th cycle, and the
// last line is a radioactive mutant emoticon.
#define DELAY7        \
  asm volatile(       \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "nop"      "\n"   \
::);


#endif    // __TFTLCD_SHIELD_DEFINITION_H_