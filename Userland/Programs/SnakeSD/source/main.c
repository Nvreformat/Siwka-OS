#include <Siwka/graphics.h>
#include <Siwka/input.h>
#include <Siwka/program.h>
#include <Stdlib/string.h>
#include <screen.h>
#include <defs.h>
#include <snake.h>

volatile bool Running = true;

void MouseEventHandler(MouseEvent* Event)
{
	
	
	if (Event->Button > 0 && Event->DisplacementX == 0 && Event->DisplacementY == 0)
	{
		if (Event->Button == 4)
		{
			Running = false;
		}
	}
}

SnakeObject Snake;

void* Main() 
{
	char b[50];

	Snake = SnakeObject();
	
	SetMouseEventHandler(MouseEventHandler);
	
	for (uint32 X = 0; X < TileCountX; X++)
	{
		if (X % 2 == 0)
		{
			SetTileEnabled(X, 0, true);
		}
	}
	
	for (uint32 Y = 0; Y < TileCountY; Y++)
	{
		if (Y % 2 == 0)
		{
			SetTileEnabled(0, Y, true);
		}
	}
	
	int e = 0;
	while(Running)
	{
		Graphics::PutString(StringFormat(b, "%u", e), 0, 0, 0);
		DispatchMessages();
		
		e++;
	};
	
	return 0;
}