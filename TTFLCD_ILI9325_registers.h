// Register names definition for ILI9325
// Code provided by PiotrCzCc
// https://github.com/PiotrCzCc/Arduino-LCD-TFT-ILI9325

#define ILI9325_DRIVER_CODE_REG						0x00
#define ILI9325_Driver_Output_Control_1				0x01
#define ILI9325_LCD_Driving_Wave_Control			0x02
#define ILI9325_Entry_Mode							0x03
#define ILI9325_Resizing_Control_Register			0x04

#define ILI9325_Display_Control_1					0x07
#define ILI9325_Display_Control_2					0x08
#define ILI9325_Display_Control_3					0x09
#define ILI9325_Display_Control_4					0x0A
#define ILI9325_RGB_Display_Interface_Control_1		0x0C
#define ILI9325_Frame_Maker_Position				0x0D
#define ILI9325_RGB_Display_Interface_Control_2		0x0F

#define ILI9325_Power_Control_1						0x10
#define ILI9325_Power_Control_2						0x11
#define ILI9325_Power_Control_3						0x12
#define ILI9325_Power_Control_4						0x13

#define ILI9325_Horizontal_GRAM_Address_Set			0x20
#define ILI9325_Vertical_GRAM_Address_Set			0x21
#define ILI9325_Write_Data_to_GRAM					0x22

#define ILI9325_Power_Control_7						0x29
#define ILI9325_Frame_Rate_and_Color_Control		0x2B

// ----------- Gamma Curve correction registers ----------//
#define ILI9325_Gamma_Control_1						0x30
#define ILI9325_Gamma_Control_2						0x31
#define ILI9325_Gamma_Control_3						0x32
#define ILI9325_Gamma_Control_4						0x35
#define ILI9325_Gamma_Control_5						0x36
#define ILI9325_Gamma_Control_6						0x37
#define ILI9325_Gamma_Control_7						0x38
#define ILI9325_Gamma_Control_8						0x39
#define ILI9325_Gamma_Control_9						0x3C
#define ILI9325_Gamma_Control_10					0x3D

//------------------ GRAM area registers ----------------//
#define ILI9325_Horizontal_Address_Start_Position	0x50
#define ILI9325_Horizontal_Address_End_Position		0x51
#define ILI9325_Vertical_Address_Start_Position		0x52
#define ILI9325_Vertical_Address_End_Position		0x53

#define ILI9325_Driver_Output_Control_2				0x60
#define ILI9325_Base_Image_Display_Control			0x61
#define ILI9325_Vertical_Scroll_Control				0x6A

//-------------- Partial Display Control register -------//
#define ILI9325_Partial_Image_1_Display_Position	0x80
#define ILI9325_Partial_Image_1_Area_Start_Line		0x81
#define ILI9325_Partial_Image_1_Area_End_Line		0x82
#define ILI9325_Partial_Image_2_Display_Position	0x83
#define ILI9325_Partial_Image_2_Area_Start_Line		0x84
#define ILI9325_Partial_Image_2_Area_End_Line		0x85

#define ILI9325_Panel_Interface_Control_1			0x90
#define ILI9325_Panel_Interface_Control_2			0x92
#define ILI9325_Panel_Interface_Control_3			0x93	// This are not documented in Datasheet V0.43
#define ILI9325_Panel_Interface_Control_4			0x95
#define ILI9325_Panel_Interface_Control_5			0x97	// This are not documented in Datasheet V0.43
#define ILI9325_Panel_Interface_Control_6			0x98	// This are not documented in Datasheet V0.43

// This are not documented in Datasheet V0.43- only in Application Notes for ILI9325 V0.22
#define ILI9325_Internal_Timing_1					0xE3
#define ILI9325_Internal_Timing_2					0xE7
#define ILI9325_Internal_Timing_3					0xEF