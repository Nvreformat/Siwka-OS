#ifndef CONSOLE_H
#define CONSOLE_H

void ConsolePrintString(const char* Text);
void ConsolePrintLine(const char* Text);
void ConsoleClear();
void ConsoleOnKeyPressed(char Character);
void ConsoleScroll();
void ConsoleSetCursorPos(uint32 X, uint32 Y);

#endif
