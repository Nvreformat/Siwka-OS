#ifndef GRAPHICS_H
#define GRAPHICS_H

#define CHAR_COUNT_X (1920 / 16)
#define CHAR_COUNT_Y (1080 / 28)

typedef struct
{
	uint32 Width;
	uint32 Height;
	uint32 VirtualWidth;
	uint32 VirtualHeight;
	uint32 Pitch;
	uint32 BitDepth;
	uint32 X;
	uint32 Y;
	char* Pointer;
	uint32 Size;
} FramebufferDescription;

typedef struct
{
	uint8 R;
	uint8 G;
	uint8 B;
} Color;

namespace Graphics
{
	extern FramebufferDescription* FramebufferData;
	extern uint8* Framebuffer;
	extern Color TextBackground;
	extern Color TextForeground;
	extern Color Palette;
	extern uint32 CurrentFont;
	
	void Setup();
	void* GetFramebuffer();
	
	void SetColor(uint32 Color);
	void SetColor(int R, int G, int B);
	void SetPixel(uint32 X, uint32 Y);
	Color* GetPixel(uint32 X, uint32 Y);
	void FillRect(uint32 X1, uint32 Y1, uint32 X2, uint32 Y2);
	
	void SetTextBackgroundColor(uint32 Color);
	void SetTextForegroundColor(uint32 Color);
	void SetTextColors(int BR, int BG, int BB, int FR, int FG, int FB);
	void SetTextFont(uint32 NewFont);
	void PutChar(int Char, int PosX, int PosY);
	void PutString(char* Text, int X, int Y, int Alignment);
};

#endif