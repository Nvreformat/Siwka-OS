#include <Siwka/svc.h>
#include <stdarg.h>

volatile SVCRequest SVCReq;

extern volatile uint32(*SVCHandler)(uint32, void*);

uint32 SystemCall(uint32 Code, void* Param)
{
	return SVCHandler(Code, Param);
}