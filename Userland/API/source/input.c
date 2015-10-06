#include <Stdlib/string.h>
#include <Siwka/graphics.h>
#include <Siwka/input.h>

void(*MouseIHandler)(MouseEvent*) = 0;

void ProcessRawInput(Input* InputEvent)
{
	//Graphics::PutString("EEEEEEEEE", 50, 0, 0);
	
	if (InputEvent->Type == 0)
	{
		
		
		MouseEvent* Event = (MouseEvent*) InputEvent;
		
		if (MouseIHandler != 0)
		{
			MouseIHandler(Event);
		}
	}
}

void SetMouseEventHandler(void(*Handler)(MouseEvent*))
{
	MouseIHandler = Handler;
}