// ?Rva009AB530BuildProbabilityTables@@YAXPAE_N@Z
// partial score=0.9 date=2026-09-20
// ?Rva009AB530BuildProbabilityTables@@YAXPAE_N@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int Rva009B4800DecodeBool(void *state, int probability);
int bfmeGoUSC(void *state, int count);
void Rva009AAFE0BuildTable(void *self, const unsigned char *source);
void Rva009B64A0BuildTone(unsigned char *ctx);

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int size);
#pragma intrinsic(memcpy)
extern "C" void * __cdecl memset(void *destination, int value, unsigned int size);
#pragma intrinsic(memset)

void Rva009AB530BuildProbabilityTables(unsigned char *ctx, bool reuse)
{
	unsigned char previous[11];
	memset(previous, 0x80, sizeof(previous));
	void *state = ctx + 0x150;

	for (register int rowOffset = 0; rowOffset < 0x16; rowOffset += 11)
	{
		for (register int index = 0; index < 11; ++index)
		{
			int offset = rowOffset + index;
			if (Rva009B4800DecodeBool(state,
				*(const unsigned char *)(0x011430B0 + offset)))
			{
				unsigned char value = (unsigned char)bfmeGoUSC(state, 7);
				value <<= 1;
				if (value == 0)
					++value;
				previous[index] = value;
				ctx[0x3A0 + offset] = value;
			}
			else if (!reuse)
			{
				ctx[0x3A0 + offset] = previous[index];
			}
		}
	}

	if (!reuse)
	{
		unsigned char *destination = ctx + 0x560;
		memcpy(destination, (const void *)0x01143124, 0x1C);
		if (Rva009B4800DecodeBool(state, 0x80))
		{
			for (int index = 1; index < 0x41; ++index)
			{
				if (Rva009B4800DecodeBool(state,
					*(const unsigned char *)(0x011430C8 + index)))
				{
					ctx[0x63C + index] = (unsigned char)bfmeGoUSC(state, 4);
				}
			}
		}
			Rva009AAFE0BuildTable(ctx, ctx + 0x63C);

		for (int row = 0; row < 2; ++row)
		{
			for (int column = 0; column < 14; ++column)
			{
				int index = row * 14 + column;
				if (Rva009B4800DecodeBool(state,
					*(const unsigned char *)(0x01143108 + index)))
				{
					unsigned char value = (unsigned char)bfmeGoUSC(state, 7);
					value <<= 1;
					if (value == 0)
						++value;
					ctx[0x560 + index] = value;
				}
			}
		}

	const unsigned char *source = (const unsigned char *)0x01143140;
	int outputOffset = 0;
	while (source < (const unsigned char *)0x011432CC)
	{
		register int groups = 2;
		register int blockOffset = outputOffset;
		while (groups != 0)
		{
			register int row = 0;
			while (row < 6)
			{
				for (register int column = 0; column < 11; ++column)
				{
					int index = column;
					if (Rva009B4800DecodeBool(state, source[index]))
					{
						unsigned char value = (unsigned char)bfmeGoUSC(state, 7);
						value <<= 1;
						if (value == 0)
							++value;
						ctx[0x3B6 + (blockOffset + row) * 11 + column] = value;
					}
				}
				++row;
				source += 11;
			}
			blockOffset += 18;
			--groups;
		}
		outputOffset += 6;
	}
	}

	Rva009B64A0BuildTone(ctx);
}
