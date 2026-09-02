// ?Rva009B62A0ExpandTable@@YAXPBIPAG@Z
// partial score=0.75 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

void Rva009B62A0ExpandTable(const unsigned *tree, unsigned short *output)
{
	union PackedNode {
		unsigned raw;
		unsigned char low;
	} value;
	int index = 0;
	int prefix;
	int bit;

	do {
		prefix = 0;
		value.raw &= 0xffffff00;
		bit = 6;
		do {
			++prefix;
			--bit;
		int branch = index >> bit;
		value.raw >>= 1;
		value.raw &= 0x7f;
		if (branch & 1)
			value.raw = tree[value.raw * 3 + 1];
		else
			value.raw = tree[value.raw * 3];
		++value.low;
		} while (index != 0 && bit > 0);

		unsigned result = (value.raw >> 1) & 0x7f;
		unsigned low = value.low & 1;
		result = (result | (prefix << 11)) << 1;
		result |= low;
		output[index] = (unsigned short)result;
		++index;
	} while (index < 64);
}
