// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4880State
{
	unsigned char pad0[4];
	short *values;
	int selector;
};

struct Rva009B4880Neighbor
{
	unsigned char pad0[8];
	short selector;
	short value;
};

// Retail .rdata 0x01142BA0: ten 32-bit entries {1,0,1,1,1,2,2,1,2,2} (VP6's
// per-mode reference-frame map), read here and by 0x009AB950/0x009AB990 as
// low 16-bit words; zero padding follows up to the 0x01142BE0 mask table.
extern const unsigned short Rva01142BA0Table[20] = {
	1, 0, 0, 0, 1, 0, 1, 0, 1, 0,
	2, 0, 2, 0, 1, 0, 2, 0, 2, 0
};

void Rva009B4880PredictValue(Rva009B4880State *state, int block,
	short *output, const Rva009B4880Neighbor *left,
	const Rva009B4880Neighbor *above)
{
	unsigned char selector = (unsigned char)Rva01142BA0Table[state->selector * 2];
	unsigned char count = 0;
	int sum = 0;

	if ((unsigned short)selector == (unsigned short)above->selector) {
		sum = above->value;
		count = 1;
	}
	if ((unsigned short)selector == (unsigned short)left->selector) {
		sum += left->value;
		++count;
	}

	if (count == 0)
		sum = output[selector];
	else if (count == 2)
		sum = (sum + ((unsigned short)sum >> 15)) >> 1;

	state->values[block << 6] += (short)sum;
	output[selector] = state->values[block << 6];
}
