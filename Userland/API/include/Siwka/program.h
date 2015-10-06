#ifndef PROGRAM_H
#define PROGRAM_H

#define PROGRAM_ADDRESS 0x2000000
#define PROGRAM_MAGIC 0x13371337
#define MAX_PROGRAM_COUNT 32

typedef struct __attribute__((packed))
{
	unsigned int Signature;
	unsigned int Size;
	unsigned char Name[32];
	unsigned int Start;
} SiwkaHeader;

SiwkaHeader* GetProgramByName(char* Name);
SiwkaHeader** GetProgramList();
uint32 DispatchMessages();

#endif