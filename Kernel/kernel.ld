SECTIONS
{
	. = 0x8000;
	
	.init : {
		*(.init*)
	}
	
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
}