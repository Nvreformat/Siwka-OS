#include <Stdlib/string.h>
#include <Stdlib/memutil.h>
#include <USPI/uspi.h>
#include <Kernel/memory.h>
#include <Kernel/propertytags.h>
#include <Kernel/interrupt.h>
#include <Kernel/console.h>
#include <Kernel/text.h>
#include <Kernel/timer.h>
#include <Kernel/sysutils.h>
#include <Kernel/program.h>

char Testa[50];

void KernelMain(void)
{
	ConsolePrintLine("Fetching program list... ");
	
	LoadProgramList();
	
	ConsolePrintLine("Jumping to init");
	
	while(true)
	{
		//char* ProgramName = (char*) ExecuteProgram("Init");
		
		//if (!StringEqual(ProgramName, "Init"))
		//{
		//	ExecuteProgram(ProgramName);
		//}
		
		ConsolePrintLine(StringFormat(Testa, "1 Returned: %u", ExecuteProgram("Snake")));
		ConsolePrintLine(StringFormat(Testa, "2 Returned: %u", ExecuteProgram("Snake")));
	}
}


