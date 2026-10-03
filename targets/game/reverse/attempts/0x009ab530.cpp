// ?Rva009AB530BuildProbabilityTables@@YAXRAE_N@Z
// partial score=0.1888 date=2026-10-03
// ?Rva009AB530BuildProbabilityTables@@YAXRAE_N@Z
// Bank only: corrected control flow; full556B extent through RET009AB75B.
// Original stash incorrectly enclosed all remaining updates in !reuse,
// used index<65, called BuildTable outside its decoder guard, and omitted
// last-pass history update/fallback. See identity_evidence/009ab530-control-flow.md.
// This bank547B/433dif improves measured quality0.1565 to0.1888.
// Volatile parameter cursor/counters are experimental stack-lifetime controls;
// data region and typed callee declarations still need full binding verification.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4800State;
struct Rva009AAFE0Context;
int Rva009B4800DecodeBool(Rva009B4800State *state, int probability);
int bfmeGoUSC(void *state, int count);
void Rva009AAFE0BuildTable(Rva009AAFE0Context *self, const unsigned char *ctx);
void Rva009B64A0BuildTone(unsigned char *self);

extern const unsigned char Rva011430B0Data[];

extern "C" void * __cdecl memcpy(void *destination, const void *ctx, unsigned int size);
#pragma intrinsic(memcpy)
extern "C" void * __cdecl memset(void *destination, int value, unsigned int size);
#pragma intrinsic(memset)

void Rva009AB530BuildProbabilityTables(unsigned char *volatile ctx, bool reuse)
{
	unsigned char *self = ctx;
	unsigned char previous[11];
	memset(previous, 0x80, sizeof(previous));
	Rva009B4800State *state = (Rva009B4800State *)(self + 0x150);

	for (register unsigned int rowOffset = 0; rowOffset < 0x16; rowOffset += 11)
	{
		for (register unsigned int index = 0; index < 11; ++index)
		{
			int offset = rowOffset + index;
			if (Rva009B4800DecodeBool(state,
			Rva011430B0Data[offset]))
			{
				unsigned char value = (unsigned char)bfmeGoUSC(state, 7);
				value <<= 1;
				value += (value == 0);
				previous[index] = value;
				self[0x3A0 + offset] = value;
			}
			else if (!reuse)
			{
				self[0x3A0 + offset] = previous[index];
			}
		}
	}

	if (!reuse)
	{
		unsigned char *destination = self + 0x560;
		memcpy(destination, Rva011430B0Data + 0x74, 0x1C);
	}
	if (Rva009B4800DecodeBool(state, 0x80))
	{
		for (unsigned int index = 1; index < 0x40; ++index)
		{
			if (Rva009B4800DecodeBool(state,
			Rva011430B0Data[0x18 + index]))
			{
				self[0x63C + index] = (unsigned char)bfmeGoUSC(state, 4);
			}
		}
		Rva009AAFE0BuildTable((Rva009AAFE0Context *)self, self + 0x63C);
	}

	for (unsigned int row = 0; row < 28; row += 14)
	{
		for (unsigned int column = 0; column < 14; ++column)
		{
			int index = row + column;
			if (Rva009B4800DecodeBool(state,
			Rva011430B0Data[0x58 + index]))
			{
				unsigned char value = (unsigned char)bfmeGoUSC(state, 7);
				value <<= 1;
				value += (value == 0);
				self[0x560 + index] = value;
			}
		}
	}

	ctx = (unsigned char *)(Rva011430B0Data + 0x90);
	volatile int outputOffset = 0;
	do
	{
		volatile int groups = 2;
		register int blockOffset = outputOffset;
		while (groups != 0)
		{
			register unsigned int row = 0;
			while (row < 6)
			{
				for (register unsigned int column = 0; column < 11; ++column)
				{
					int index = column;
					if (Rva009B4800DecodeBool((Rva009B4800State *)(self + 0x150), ctx[index]))
					{
						unsigned char value = (unsigned char)bfmeGoUSC(self + 0x150, 7);
						value <<= 1;
						value += (value == 0);
						previous[column] = value;
						self[0x3B6 + (blockOffset + row) * 11 + column] = value;
					}
					else if (!reuse)
					{
						self[0x3B6 + (blockOffset + row) * 11 + column] = previous[column];
					}
				}
				++row;
				ctx += 11;
			}
			blockOffset += 18;
			--groups;
		}
		outputOffset += 6;
	} while ((int)ctx < (int)(Rva011430B0Data + 0x21C));

	Rva009B64A0BuildTone(self);
}
