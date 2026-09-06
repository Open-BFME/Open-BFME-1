// cl: /DNDEBUG /MD /O2
//
// Address-derived nonvirtual leaf at retail 0x009C81C0.  The object carries a
// 0x40-entry coefficient area ending at +0x4938 and a fill/count word at
// +0x4538.  The initializer writes the descending coefficient ramp, then
// fills the remaining lower table entries with one.

// ?rva009C81C0TableInit@@YAXPAX@Z
void __cdecl rva009C81C0TableInit(void *context)
{
	unsigned char *base = (unsigned char *)context;
	unsigned int index = 0;
	*(int *)(base + 0x4538) = 0x40;
	unsigned int offset = 0;
	volatile int *write = (volatile int *)(base + 0x4938);

	while (index < *(int *)(base + 0x4538))
	{
		unsigned int count = *(unsigned int *)(base + 0x4538);
		unsigned int value = (count * 6 - offset) / count;
		++index;
		offset += 5;
		write[0] = (int)value;
		--write;
	}

	unsigned int count = *(unsigned int *)(base + 0x4538);
	if (count < 0xff)
	{
		int *fill = (int *)(base + (0x124e - count) * 4);
		int remaining = 0xff - count;
		do
		{
			*fill = 1;
			--fill;
			--remaining;
		} while (remaining != 0);
	}
}
