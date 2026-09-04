// ?Rva009C2320Vp6FilterDiag4@@YAXPAX00HHPAH@Z
// partial score=0.28 date=2026-09-04
// cl: /O2 /Ob0 /Oy- /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The optimized VP6 block filter makes three signed-byte edge-weight planes
// (above, left and right), then folds them into an eight-row four-neighbour
// reconstruction.  The first argument is the dispatcher's unused context.

static int rva009c2320Weight(unsigned char a, unsigned char b,
	int selectorWeight, int edgeTag)
{
	int difference = (int)a - (int)b;
	int weight;

	if (difference < 0)
		difference = -difference;

	weight = selectorWeight + 0x20 - difference;
	if (weight < 0)
		weight = 0;
	if (weight > 3 * selectorWeight)
		weight = 3 * selectorWeight;

	// The retail MMX path marks a steep edge by OR-ing the signed tag into
	// the clamped byte.  This is the signed negative tap used by the final
	// psubusw/packuswb reconstruction.
	if (difference > selectorWeight + 0x60)
		weight = (int)((unsigned char)weight | (unsigned char)edgeTag);
	if (weight >= 0x80)
		weight -= 0x100;
	return weight;
}

static int rva009c2320ClipByte(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return value;
}

void __cdecl Rva009C2320Vp6FilterDiag4(
	void *, void *sourceArgument, void *destinationArgument,
	int stride, int selector, int *filterTable)
{
	unsigned char *source = (unsigned char *)sourceArgument;
	unsigned char *destination = (unsigned char *)destinationArgument;
	const int *edgeTable = (const int *)0x012D8158;
	int selectorWeight = filterTable[selector];
	int edgeTag = edgeTable[selector];
	__declspec(align(16)) short verticalWeight[9][8];
	__declspec(align(16)) short horizontalWeight[16][8];
	int y;
	int x;

	// The hand-written body keeps one extra vertical row for the lower tap;
	// the first eight rows are the rows materialized by its MMX loop.
	for (y = 0; y < 9; ++y) {
		for (x = 0; x < 8; ++x) {
			verticalWeight[y][x] = (short)rva009c2320Weight(
				source[y * stride + x], source[(y - 1) * stride + x],
				selectorWeight, edgeTag);
		}
	}

	for (y = 0; y < 8; ++y) {
		for (x = 0; x < 8; ++x) {
			unsigned char *row = source + y * stride;
			horizontalWeight[y][x] = (short)rva009c2320Weight(
				row[x], row[x - 1], selectorWeight, edgeTag);
			horizontalWeight[y + 8][x] = (short)rva009c2320Weight(
				row[x], row[x + 1], selectorWeight, edgeTag);
		}
	}

	for (y = 0; y < 8; ++y) {
		unsigned char *row = source + y * stride;
		unsigned char *out = destination + (y - 1) * stride;
		for (x = 0; x < 8; ++x) {
			int up = verticalWeight[y][x];
			int down = verticalWeight[y + 1][x];
			int left = horizontalWeight[y][x];
			int right = horizontalWeight[y + 8][x];
			int centre = 128 - up - down - left - right;
			int value = source[(y - 1) * stride + x] * up;

			value += source[(y + 1) * stride + x] * down;
			value += row[x - 1] * left;
			value += row[x + 1] * right;
			value += row[x] * centre;
			value += 64;
			if (value < 0)
				value = 0;
			out[x] = (unsigned char)rva009c2320ClipByte(value >> 7);
		}
	}
}
