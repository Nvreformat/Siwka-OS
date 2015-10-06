#include <Siwka/svc.h>
#include <Siwka/program.h>

SiwkaHeader* GetProgramByName(char* Name)
{
	return (SiwkaHeader*) SystemCall(SYSCALL_GET_PROGRAM_BY_NAME, (void*) Name);
}

SiwkaHeader** GetProgramList()
{
	return (SiwkaHeader**) SystemCall(SYSCALL_GET_PROGRAM_LIST, (void*) 0);
}

uint32 DispatchMessages()
{
	return (uint32) SystemCall(SYSCALL_DISPATCH_MESSAGES, (void*) 0);
}