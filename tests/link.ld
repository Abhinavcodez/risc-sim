ENTRY(_start)
OUTPUT_ARCH(riscv)
SECTIONS {
  . = 0x0;
  .text : { *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss  : { *(.bss*) }
}