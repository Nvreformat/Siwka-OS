#include <USPI/uspi.h>
#include <Kernel/input.h>
#include <Kernel/console.h>

void(*InputCallback)(Input* Event) = 0;

void MouseInputHandler(unsigned Button, int DisplacementX, int DisplacementY)
{
	if (InputCallback != 0 && DisplacementX == 0 && DisplacementY == 0)
	{
		MouseEvent Event;
		
		Event.DisplacementX = DisplacementX;
		Event.DisplacementY = DisplacementY;
		Event.Button = Button;
		Event.Event.Type = 0;
		
		InputCallback((Input*) &Event);
	}
}

void SetupInput()
{
	USPiMouseRegisterStatusHandler(MouseInputHandler);
}

void SetInputCallback(void(*Callback)(Input* Event))
{
	InputCallback = Callback;
}