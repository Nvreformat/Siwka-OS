#include <Stdlib/memutil.h>
#include <Siwka/svc.h>
#include <Siwka/graphics.h>

namespace Graphics
{
	FramebufferDescription* FramebufferData;
	uint8* Framebuffer;  
	
	void Setup()
	{
		uint32 Response = SystemCall(SYSCALL_GET_FRAMEBUFFER_DATA, (void*) 0);		
		
		//FramebufferData = (FramebufferDescription*) Response;
		//Framebuffer = (uint8*) FramebufferData->Pointer;
		
		//MemorySet(FramebufferData->Pointer, 0, FramebufferData->Size);
		
		//SetColor(255, 255, 255);
		//SetTextColors(0, 0, 0, 255, 255, 255);
		//SetTextFont(1);
	}
	
	void* GetFramebuffer()
	{
		return Framebuffer;
	}
};