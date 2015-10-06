#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((packed))
{
	unsigned int Signature;
	unsigned int Size;
	unsigned char Name[32];
	unsigned int Start;
} SiwkaHeader;

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		FILE* Output = fopen(argv[2], "wb");
		FILE* InputFile = fopen(argv[1], "rb");
		unsigned char* FileBuffer;
		unsigned int FileSize;
		
		fseek(InputFile, 0, SEEK_END);
		FileSize = ftell(InputFile);
		fseek(InputFile, 0, SEEK_SET);
		FileBuffer = malloc(FileSize + 1);
		fread(FileBuffer, FileSize, 1, InputFile);
		fclose(InputFile);
			
		// Construct the header;
		SiwkaHeader Header;
		
		memset((void*) &Header, 0, sizeof(SiwkaHeader));
		Header.Signature = 0x13371337;
		Header.Size = FileSize + sizeof(SiwkaHeader);
		memcpy((void*) &Header.Name, (void*) argv[3], strlen(argv[3]));
		Header.Start = sizeof(SiwkaHeader);
		
		fwrite((void*) &Header, sizeof(SiwkaHeader), 1, Output);
		fwrite((void*) FileBuffer, FileSize, 1, Output);
		
		fclose(Output);
		free(FileBuffer);
	}
	
	return 0;
}
