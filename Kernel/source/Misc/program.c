#include <Stdlib/memutil.h>
#include <Kernel/program.h>
#include <Kernel/console.h>
#include <Kernel/input.h>
#include <Kernel/timer.h>
#include <Stdlib/string.h>
#include <Kernel/sysutils.h>

extern uint32 __PROGRAM_START;
extern uint32 __PROGRAM_END;

volatile ProgramMessageHandler MessageHandler __attribute__((long_call)) = 0;

char a[50];


uint32 CurrentProgram = 0;
extern "C" uint32 SVCHandler(uint32 SVCCode, void* Param);

SiwkaHeader* Programs[MAX_PROGRAM_COUNT];
volatile ProgramMessage MessageQueue[MAX_MESSAGE_COUNT];
volatile int MessageCount = 0;

void InputEventHandler(Input* Event)
{
	ProgramSendMessage(0x0001, (void*) Event);
}

void LoadProgramList()
{
	MemorySet(Programs, 0, sizeof(Programs));
	
	char* Addr = (char*) __PROGRAM_START;
	uint32 Index = 0;
	
	SetInputCallback(InputEventHandler);
	
	while (true)
	{
		SiwkaHeader* Header = (SiwkaHeader*) Addr;
			
		if (Header->Signature == PROGRAM_MAGIC)
		{
			Programs[Index] = Header;
			
			ConsolePrintLine(StringFormat(a, "Found program called %s", Header->Name));
			
			++Index;
			Addr += Header->Size;
		}
		else
		{
			break;
		}
	}
}

SiwkaHeader** GetProgramList()
{
	return Programs;
}

SiwkaHeader* GetProgramByName(char* Name)
{
	for (int I = 0; I < MAX_PROGRAM_COUNT; I++)
	{
		if (StringEqual(Name, (char*) Programs[I]->Name))
		{
			return Programs[I];
		}
	}
			
	return 0;
}

uint32 GetProgramIndexByName(char* Name)
{
	for (int I = 0; I < MAX_PROGRAM_COUNT; I++)
	{
		if (StringEqual(Name, (char*) Programs[I]->Name))
		{
			return I;
		}
	}
			
	return 0;
}

void* ExecuteProgram(char* Name)
{
	SiwkaHeader* Header = GetProgramByName(Name);
	
	if (Header != 0)
	{
		
		
		CurrentProgram = GetProgramIndexByName(Name);
		
		MemorySet((void*) PROGRAM_ADDRESS, 0, 1024*1024);
		
		MemoryCopy((void*) Header + Header->Start, (void*) PROGRAM_ADDRESS, Header->Size);
		
		uint32 StartAddr = ((uint32) PROGRAM_ADDRESS);
		
		ProgramStart EntryPoint = (ProgramStart) PROGRAM_ADDRESS;
		//ConsolePrintLine(StringFormat(a, "Entry %u", *((uint32*)EntryPoint)));
		void* Return = EntryPoint((void*)SVCHandler);

		MessageCount = 0;

		
		return Return;
	}
	
	return (void*) 0;
}

void DispatchMessages()
{
	if (MessageCount > 0)
	{
		EnterCritical();

		for (int I = 0; I < MessageCount; I++)
		{
			ConsolePrintLine("Sending");
			ConsolePrintLine(StringFormat(a, "%u", MessageHandler));
			MessageHandler(MessageQueue[I].Message, (void*)MessageQueue[I].Data);
			ConsolePrintLine("Sent");
		}

		MessageCount = 0;
		LeaveCritical();
	}
}

void ProgramSendMessage(uint32 Message, void* Arguments)
{
	if (MessageHandler != 0)
	{
		if (MessageCount < MAX_MESSAGE_COUNT)
		{	
			MessageQueue[MessageCount].Message = Message;
			MemoryCopy(Arguments, (void*)MessageQueue[MessageCount].Data, sizeof(MessageQueue[MessageCount].Data));

			MessageCount++;
		}
	}
}

void ProgramSetMessageHandler(void* Handler)
{
	MessageHandler = (ProgramMessageHandler) Handler;
}