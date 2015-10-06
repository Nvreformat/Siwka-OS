#include <Siwka/graphics.h>
#include <screen.h>
#include <defs.h>

void SetTileEnabled(uint32 X, uint32 Y, bool Enabled)
{
	if (X < TileCountX && Y < TileCountY)
	{
		uint32 PosX = X * TileSize;
		uint32 PosY = Y * TileSize;
		
		Graphics::SetColor(Enabled ? 0xFFFFFF : 0x000000);
		Graphics::FillRect(PosX, PosY + 28, PosX + TileSize, PosY + TileSize + 28);
	}
}