#include <Stdlib/string.h>
#include <Siwka/svc.h>
#include <Siwka/program.h>
#include <Siwka/graphics.h>
#include <Siwka/input.h>
#include <gridlist.h>

SiwkaHeader** ProgramList;
GridList List;

volatile bool SelectingProgram = true;

void MouseEventHandler(MouseEvent* Event)
{
	if (Event->Button > 0 && Event->DisplacementX == 0 && Event->DisplacementY == 0 && SelectingProgram)
	{
		if (Event->Button == 1)
		{
			List.MoveUp();
		}
		else if (Event->Button == 2)
		{
			List.MoveDown();
		}
		else if (Event->Button == 4)
		{
			SelectingProgram = false;
		}
	}
}

void* Main() 
{
	ProgramList = GetProgramList();
	
	Graphics::PutString("---------------------------------------", 0, 0, 0);
	Graphics::PutString("| Welcome to Siwka OS!                |", 0, 1, 0);
	Graphics::PutString("| A hobby Operating System created by |", 0, 2, 0);
	Graphics::PutString("| Agustin \"Nvreformat\" Harasiwka      |", 0, 3, 0);
	Graphics::PutString("---------------------------------------", 0, 4, 0);
	Graphics::PutString("Please select a program below:", 0, 6, 0);
	
	List = GridList();
	
	int I = 1;
	while(true)
	{
		if (ProgramList[I]->Signature != 0x13371337)
		{
			break;	
		}
		
		List.AddItem((char*) ProgramList[I]->Name, "Que se yo, soy una descripcion random", ProgramList[I]->Size);
		
		I++;
	}
	
	List.SetSelectedItem(0);
	SetMouseEventHandler(MouseEventHandler);
	
	while(SelectingProgram)
	{
		DispatchMessages();	
	};
	
	return (void*) ProgramList[List.GetSelectedItem() + 1]->Name;
}