#include <Siwka/svc.h>
#include <Siwka/graphics.h>
#include <Siwka/input.h>
#include <Stdlib/string.h>

extern void* Main();
void ProgramSetMessageHandler(void* Handler);
void MessageHandler(uint32 Code, void* Address);

volatile uint32(*SVCHandler)(uint32, void*) __attribute__((long_call)) = (volatile uint32(*)(uint32, void*))10;

Init void* InternalMain(volatile uint32(*SVC)(uint32, void*))
{
	
	
	SVCHandler = SVC;
	
	Graphics::Setup();
	
	
	ProgramSetMessageHandler((void*) MessageHandler);
	
	//return (void*) SystemCall(SYSCALL_SET_MESSAGE_HANDLER, (void*) MessageHandler);
	return Main();
}

void ProgramSetMessageHandler(void* Handler)
{
	SystemCall(SYSCALL_SET_MESSAGE_HANDLER, Handler);
}

int a = 0;
// TODO: Thread safety; nested SVCs fuck up really bad. This may be fixed by now
void MessageHandler(uint32 Code, void* Param)
{
	a++;
	
	char r[50];
	
	Graphics::PutString(StringFormat(r, "%u", a), 50, 0, 0);
	
	// Input event
	if (Code == 0x0001)
	{
		ProcessRawInput((Input*) Param);
	}
}

