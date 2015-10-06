#include <Stdlib/string.h>
#include <Siwka/graphics.h>
#include <Siwka/font.h>

namespace Graphics
{
	Color TextBackground = {0, 0, 0};
	Color TextForeground = {255, 255, 255};
	uint32 CurrentFont = 1;
	
	void SetTextBackgroundColor(uint32 Color)
	{
		TextBackground.R = ((Color) & 0xFF);
		TextBackground.G = ((Color >> 8) & 0xFF);
		TextBackground.B = ((Color >> 16) & 0xFF);
	}
	
	void SetTextForegroundColor(uint32 Color)
	{
		TextForeground.R = ((Color) & 0xFF);
		TextForeground.G = ((Color >> 8) & 0xFF);
		TextForeground.B = ((Color >> 16) & 0xFF);
	}
	
	void SetTextFont(uint32 NewFont)
	{
		CurrentFont = NewFont;
	}
	
	void __attribute__((optimize("O3"))) PutChar(int Char, int PosX, int PosY)
	{
		if (PosX >= 0 && PosX < CHAR_COUNT_X && PosY >= 0 && PosY < CHAR_COUNT_Y)
		{
			PosX *= 16;
			PosY *= 28;

			for (int Line = 0; Line < 28; Line++)
			{
				for (int X = 0; X < 16; X = X + 1)
				{
					int ArrayLocation = (FramebufferData->Pitch * (PosY + Line)) + ((PosX + X) * 3);

					if (FontData[CurrentFont][Char][Line] & (0x8000 >> (X)))
					{
						Framebuffer[ArrayLocation] = TextForeground.B;
						Framebuffer[ArrayLocation + 1] = TextForeground.G;
						Framebuffer[ArrayLocation + 2] = TextForeground.B;
					}
					else
					{
						Framebuffer[ArrayLocation] = TextBackground.R;
						Framebuffer[ArrayLocation + 1] = TextBackground.G;
						Framebuffer[ArrayLocation + 2] = TextBackground.B;
					}
				}	
			}
		}
	}
	
	void PutString(char* Text, int X, int Y, int Alignment)
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

			PutChar(Character, X + i, Y);

			i++;
		}
	}
	
	void SetTextColors(int BR, int BG, int BB, int FR, int FG, int FB)
	{
		TextBackground.R = BR;
		TextBackground.G = BG;
		TextBackground.B = BB;
		TextForeground.R = FR;
		TextForeground.G = FG;
		TextForeground.B = FB;
	}
}