#ifndef INPUT_H
#define INPUT_H

typedef struct
{
	int Type;
} Input;

typedef struct
{
	Input Event;
	int DisplacementX;
	int DisplacementY;
	int Button;
} MouseEvent;

void ProcessRawInput(Input* Event);
void SetMouseEventHandler(void(*Handler)(MouseEvent*));

#endif