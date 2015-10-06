#ifndef PROGRAM_H
#define PROGRAM_H

#define PROGRAM_ADDRESS 0x2000000
#define PROGRAM_MAGIC 0x13371337
#define MAX_PROGRAM_COUNT 32
#define MAX_MESSAGE_COUNT 256


typedef struct __attribute__((packed))
{
	unsigned int Signature;
	unsigned int Size;
	unsigned char Name[32];
	unsigned int Start;
} SiwkaHeader;

typedef struct
{
	uint32 Message;
	char Data[64];
} ProgramMessage;

typedef void* (*ProgramStart)(void* SVC);
typedef void (*ProgramMessageHandler)(uint32 Message, void* Param);

void LoadProgramList();
SiwkaHeader** GetProgramList();
SiwkaHeader* GetProgramByName(char* Name);
void* ExecuteProgram(char* Name);
void ProgramSendMessage(uint32 Message, void* Data);
void ProgramSetMessageHandler(void* Handler);
void DispatchMessages();

#endif