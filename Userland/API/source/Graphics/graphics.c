#include <Siwka/graphics.h>

namespace Graphics
{
	Color Palette = {255, 255, 255};
	
	void __attribute__((optimize("O3"))) SetPixel(uint32 X, uint32 Y)
	{
		int ArrayLocation = (FramebufferData->Pitch * Y) + (X * 3);
	
		Framebuffer[ArrayLocation] = Palette.R;
		Framebuffer[ArrayLocation + 1] = Palette.G;
		Framebuffer[ArrayLocation + 2] = Palette.B;
	}
	
	Color* __attribute__((optimize("O3"))) GetPixel(uint32 X, uint32 Y)
	{
		int ArrayLocation = (FramebufferData->Pitch * Y) + (X * 3);
		
		return (Color*) ArrayLocation;
	}
	
	void SetColor(uint32 Color)
	{
		Palette.R = ((Color) & 0xFF);
		Palette.G = ((Color >> 8) & 0xFF);
		Palette.B = ((Color >> 16) & 0xFF);
	}
	
	void SetColor(int R, int G, int B)
	{
		Palette.R = R;
		Palette.G = G;
		Palette.B = B;
	}
	
	void __attribute__((optimize("O3"))) FillRect(uint32 X1, uint32 Y1, uint32 X2, uint32 Y2)
	{
		for (uint32 X = X1; X < X2; X++)
		{
			for (uint32 Y = Y1; Y < Y2; Y++)
			{
				SetPixel(X, Y);
			}
		}
	}
};