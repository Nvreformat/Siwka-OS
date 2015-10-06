#include <Stdlib/string.h>
#include <Kernel/console.h>
#include <Kernel/text.h>
#include <Kernel/framebuffer.h>

int CursorX = 0;
int CursorY = 0;

extern "C" void memcpy2(void* src, void* dst, size_t size);
void ConsolePrintChar(int Character);

void ConsolePrintChar(int Character)
{
	if (Character == '\n')
	{
		CursorX = 0;
	
		if (CursorY < (CHAR_COUNT_Y - 1))
		{
			++CursorY;
		}
		else
		{
			ConsoleScroll();
		}
			
		return;
	}

	ScreenPutChar(Character, CursorX, CursorY);
	
	++CursorX;
	if (CursorX == CHAR_COUNT_X)
	{
		CursorX = 0;	
		
		if (CursorY < (CHAR_COUNT_Y - 1))
		{
			++CursorY;
		}
		else
		{
			ConsoleScroll();
		}
	}
}

void ConsolePrintString(const char* Text)
{
	int i = 0;

	while(1)
	{	
		char Character = Text[i];
		
		if (Character == '\0')
		{
			break;
		}
		
		ConsolePrintChar(Character);
		
		i++;
	}
}

void ConsoleClear()
{
	for (int Y = 1; Y < CHAR_COUNT_Y; ++Y)
	{
		for (int X = 0; X < CHAR_COUNT_X; ++X)
		{
			ScreenPutChar(' ', X, Y);
		}
	}
	
	CursorX = 0;
	CursorY = 0;
}

void ConsolePrintLine(const char* Text)
{
	ConsolePrintString(Text);
	ConsolePrintChar('\n');
}

void ConsoleScroll()
{
	memcpy2(Framebuffer::Description.Pointer + (Framebuffer::Description.Pitch * 28 * 2), Framebuffer::Description.Pointer + (Framebuffer::Description.Pitch * 28), (Framebuffer::Description.Pitch * 28 * (CHAR_COUNT_Y - 2)));
	
	for (int X = 0; X < CHAR_COUNT_X; ++X)
	{
		ScreenPutChar(' ', X, CHAR_COUNT_Y - 1);
	}
}
