#include <Stdlib/string.h>
#include <Stdlib/memutil.h>
#include <Kernel/font.h>
#include <Kernel/text.h>
#include <Kernel/framebuffer.h>

uint32_t BackgroundColor = 0x000000;
uint32_t ForegroundColor = 0xFFFFFF;
ColorRGB BackgroundRGB = {0, 0, 0};
ColorRGB ForegroundRGB = {255, 255, 255};
int CurrentFont = 1;

void __attribute__((optimize("O3"))) ScreenPutChar(int Char, int PosX, int PosY)
{
	if (PosX >= 0 && PosX < CHAR_COUNT_X && PosY >= 0 && PosY < CHAR_COUNT_Y)
	{
		PosX *= 16;
		PosY *= 28;

		for (int Line = 0; Line < 28; Line++)
		{
		    for (int X = 0; X < 16; X = X + 1)
			{
				int ArrayLocation = (Framebuffer::Description.Pitch * (PosY + Line)) + ((PosX + X) * 3);
			
				if (FontData[CurrentFont][Char][Line] & (0x8000 >> (X)))
				{
					Framebuffer::Description.Pointer[ArrayLocation] = ForegroundRGB.B;
					Framebuffer::Description.Pointer[ArrayLocation + 1] = ForegroundRGB.G;
					Framebuffer::Description.Pointer[ArrayLocation + 2] = ForegroundRGB.B;
				}
				else
				{
					Framebuffer::Description.Pointer[ArrayLocation] = BackgroundRGB.R;
					Framebuffer::Description.Pointer[ArrayLocation + 1] = BackgroundRGB.G;
					Framebuffer::Description.Pointer[ArrayLocation + 2] = BackgroundRGB.B;
				}
			}	
		}
	}
}

void ScreenSetBackgroundColor(int Color)
{
	BackgroundColor = Color;	
	
	BackgroundRGB.R = (Color >> 16) & 0xFF;
	BackgroundRGB.G = (Color >> 8) & 0xFF;
	BackgroundRGB.B = (Color) & 0xFF;
}

void ScreenSetForegroundColor(int Color)
{
	ForegroundColor = Color;
	
	ForegroundRGB.R = (Color >> 16) & 0xFF;
	ForegroundRGB.G = (Color >> 8) & 0xFF;
	ForegroundRGB.B = (Color) & 0xFF;
}

void ScreenSetColors(int BColor, int FColor)
{
	ScreenSetBackgroundColor(BColor);
	ScreenSetForegroundColor(FColor);
}

void ScreenPutString(char* Text, int X, int Y, int Alignment)
{
	int i = 0;
	
	if (Alignment == 1)
	{
		X -= (StringGetLength(Text) - 1);
	}
	else if (Alignment == 2)
	{
		X -= (StringGetLength(Text) - 1) / 2;
	}
	
	while (1)
	{
		char Character = Text[i];
		
		if (Character == '\0')
		{
			break;
		}
		
		ScreenPutChar(Character, X + i, Y);
		
		i++;
	}
}

void ScreenSetFont(int Font)
{
	CurrentFont = Font;
}
