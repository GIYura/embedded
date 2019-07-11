MEMORY
{
  UNPLACED_SECTIONS (wx) : ORIGIN = 0x100000000, LENGTH = 0
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x00040000
  RAM (wx) : ORIGIN = 0x20000000, LENGTH = 0x00004000
}

SECTIONS
{
  __FLASH_segment_start__ = 0x08000000;
  __FLASH_segment_end__ = 0x08040000;
  __FLASH_segment_size__ = 0x00040000;
  __RAM_segment_start__ = 0x20000000;
  __RAM_segment_end__ = 0x20004000;
  __RAM_segment_size__ = 0x00004000;

  __HEAPSIZE__ = 1024;
  __STACKSIZE_PROCESS__ = 0;
  __STACKSIZE__ = 1024;

}

