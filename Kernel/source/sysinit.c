#include <USPI/uspi.h>
#include <Stdlib/memutil.h>
#include <Kernel/memory.h>
#include <Kernel/interrupt.h>
#include <Kernel/timer.h>
#include <Kernel/sysutils.h>
#include <Kernel/text.h>
#include <Kernel/input.h>
#include <Kernel/framebuffer.h>
#include <Kernel/sysconfig.h>
#include <Kernel/console.h>

void KernelMain();

extern "C" void SystemInit(void)
{
	#if RASPPI != 1
	InvalidateDataCache();
	#endif

	extern unsigned char __BSS_START;
	extern unsigned char __BSS_END;
	for (unsigned char *BSS = &__BSS_START; BSS < &__BSS_END; BSS++)
	{
		*BSS = 0;
	}
	
	SetupMemory();
	Framebuffer::Setup();
	
	ConsolePrintLine("Kernel bare metal environment");
	
	SetupInterrupts();
	SetupTimer();
	
	ConsolePrintLine("Kernel bare metal environment");
	ConsolePrintString("Initializing USPI... ");
	
	USPiInitialize();
	SetupInput();
	
	ConsolePrintLine("done");
	ConsolePrintLine("Jumping to KernelMain");

	KernelMain();
	Halt();
}
