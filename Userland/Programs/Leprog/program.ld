SECTIONS
{
	. = 0x2000000;

	.init : {
		*(.init)
	}

	__PROGRAM_START = .;	
	__PROGRAM_SIZE = (__PROGRAM_END - __PROGRAM_START);
	
	.text : {
		*(.text*)
	}

	_etext = .;

	.rodata : {
		*(.rodata*)
	}

	.data : {
		*(.data*)
	}

	__BSS_START = .;
	.bss : {
		*(.bss*)
	}
	__BSS_END = .;

	__exidx_start = .;
	.ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) }
	__exidx_end = .;

	__PROGRAM_END = .;
	}
