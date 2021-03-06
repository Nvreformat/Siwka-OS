#ifndef TEXT_H
#define TEXT_H

#define CHAR_COUNT_X (1920 / 16)
#define CHAR_COUNT_Y (1080 / 28)

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} ColorRGB;

void SetupScreen();
void ScreenPutChar(int Char, int PosX, int PosY);
void ScreenSetBackgroundColor(int Color);
void ScreenSetForegroundColor(int Color);
void ScreenSetColors(int BColor, int FColor);
void ScreenPutString(char* Text, int X, int Y, int Alignment);
void ScreenSetFont(int Font);
const char* ScreenGetCharAt(int X, int Y);

#endif
