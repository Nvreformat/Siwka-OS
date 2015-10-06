#include <Stdlib/string.h>
#include <Kernel/console.h>
#include <Kernel/svc.h>
#include <Kernel/program.h>
#include <Kernel/framebuffer.h>

char Test[50];

extern "C" uint32 SVCHandler(uint32 SVCCode, void* Param)
{
	ConsolePrintLine(StringFormat(Test, "SVC %u", SVCCode));
	
	if (SVCCode == SYSCALL_SET_MESSAGE_HANDLER)
	{
		ProgramSetMessageHandler(Param);
		
		return 1;
	}
	else if (SVCCode == SYSCALL_GET_FRAMEBUFFER_DATA)
	{
		return (uint32) Framebuffer::GetDescription();
	}
	else if (SVCCode == SYSCALL_GET_PROGRAM_LIST)
	{
		return (uint32) GetProgramList();
	}
	else if (SVCCode == SYSCALL_GET_PROGRAM_BY_NAME)
	{
		return (uint32) GetProgramByName((char*) Param);
	}
	else if (SVCCode == SYSCALL_DISPATCH_MESSAGES)
	{
		DispatchMessages();
		
		return 1;
	}
	
	return 0;
}