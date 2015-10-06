#ifndef UTIL_H
#define UTIL_H

void MemorySet(void* Addrress, register char Value, register int Size);
void* MemoryCopy(void* Source, void* Destination, register int Size);
int MemoryCompare(void* Source, void* Destination, register int Size);

#endif
