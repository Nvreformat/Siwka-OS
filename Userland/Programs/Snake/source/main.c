#include <Stdlib/string.h>
#include <Siwka/svc.h>
#include <Siwka/program.h>
#include <Siwka/graphics.h>
#include <Siwka/input.h>

bool SelectingProgram = true;

void MouseEventHandler(MouseEvent* Event)
{
	Graphics::PutString("MOUSE", 0, 7, 0);
	
	if (Event->Button > 0 && Event->DisplacementX == 0 && Event->DisplacementY == 0 && SelectingProgram)
	{
		if (Event->Button == 4)
		{
			SelectingProgram = false;
		}
	}
}

void* Main() 
{
	Graphics::PutString("Para que no crachee", 0, 6, 0);
	
	SetMouseEventHandler(MouseEventHandler);
	
	while(SelectingProgram)
	{
		DispatchMessages();	
	};
	
	return 0;
}