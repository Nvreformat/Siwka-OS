#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <Kernel/mmu.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TPageTable
{
	bool TableAllocated;
	TARMV6MMU_LEVEL1_SECTION_DESCRIPTOR *Table;
}
TPageTable;

// 4GB shared device
void PageTable(TPageTable* This);

// 0..nMemSize: normal,
// nMemSize..512MB: shared device (1024MB on Raspberry Pi 2)
void PageTable2(TPageTable* This, uint32 MemSize);
void _PageTable(TPageTable* This);

uint32 PageTableGetBaseAddress(TPageTable* This);	// with mode bits to be loaded into TTBRn
	
#ifdef __cplusplus
}
#endif

#endif
