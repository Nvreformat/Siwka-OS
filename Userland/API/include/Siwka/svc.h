#ifndef SVC_H
#define SVC_H
	
#define SYSCALL_SET_MESSAGE_HANDLER 0x0001
#define SYSCALL_GET_FRAMEBUFFER_DATA 0x0002
#define SYSCALL_GET_PROGRAM_LIST 0x0003
#define SYSCALL_GET_PROGRAM_BY_NAME 0x0004
#define SYSCALL_DISPATCH_MESSAGES 0x0005

typedef struct
{
	uint32 Code;
	void* Param;
} SVCRequest;

uint32 SystemCall(uint32 Code, void* Param);
	
#endif