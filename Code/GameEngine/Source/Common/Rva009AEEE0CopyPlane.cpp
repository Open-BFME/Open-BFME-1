// BFME VP6 plane pass for one of the three planes, retail [0x009AEEE0,0x009AF0C8).
// The matched caller Rva009AF200CopyPlanes passes the context, the two buffer
// offsets and the plane selector (pin ?copyPlane009AEEE0). The switch picks
// the plane's stride, size, base and first callback index; the first four and
// the trailing four rows are copied byte by byte; every eight-row band in
// between goes through the row callback read from 0x01356E94 or 0x01356E88,
// and the last band through the fixed body at 0x009AD750 or 0x009ACC80, with
// the same seven-argument cdecl ABI as the sibling pass at 0x009AF0D0.
// The second switch compares unsigned (jbe/ja) while the pinned selector is
// an int, hence the cast.

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[0x78 - 0x04];
	unsigned char *m_planeY;       // 0x78
	unsigned char *m_planeU;       // 0x7c
	unsigned char *m_planeV;       // 0x80
	int m_indexBaseU;              // 0x84, callback index of the first U band
	int m_indexSpanU;              // 0x88, added for the first V band
	unsigned m_scratchCount;       // 0x8c
	unsigned m_width;              // 0x90
	unsigned m_height;             // 0x94
	unsigned m_strideY;            // 0x98
	unsigned m_strideUV;           // 0x9c
};

typedef void (__cdecl *Rva009AEEE0Filter)(
	Rva009AF200Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);

extern Rva009AEEE0Filter g_rva01356E94;
extern Rva009AEEE0Filter g_rva01356E88;
extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;
extern const unsigned int *g_rva01356A88;

void __cdecl Rva009AD750(
	Rva009AF200Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);
void __cdecl Rva009ACC80(
	Rva009AF200Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);

void copyPlane009AEEE0(Rva009AF200Context *ctx, int x, int y, int plane)
{
	unsigned int i, j, k;
	unsigned int stride;
	int offset = 0;
	unsigned char *source, *destination;
	unsigned int width, height;
	const unsigned int *table = 0;
	Rva009AEEE0Filter rowFilter;
	Rva009AEEE0Filter lastFilter;

	if (ctx->m_mode >= 2) {
		rowFilter = g_rva01356E94;
		lastFilter = Rva009AD750;
	} else {
		rowFilter = g_rva01356E88;
		lastFilter = Rva009ACC80;
	}

	switch (plane) {
	case 0:
		stride = ctx->m_strideY;
		width = ctx->m_width;
		height = ctx->m_height;
		offset = 0;
		source = ctx->m_planeY + x;
		destination = ctx->m_planeY + y;
		break;
	case 1:
		stride = ctx->m_strideUV;
		width = ctx->m_width >> 1;
		height = ctx->m_height >> 1;
		offset = ctx->m_indexBaseU;
		source = ctx->m_planeU + x;
		destination = ctx->m_planeU + y;
		break;
	default:
		stride = ctx->m_strideUV;
		width = ctx->m_width >> 1;
		height = ctx->m_height >> 1;
		offset = ctx->m_indexBaseU + ctx->m_indexSpanU;
		source = ctx->m_planeV + x;
		destination = ctx->m_planeV + y;
		break;
	}

	if (ctx->m_mode >= 2) {
		switch ((unsigned int)plane) {
		case 0:
			table = g_rva01356AA0;
			break;
		case 1:
		case 2:
			table = g_rva01356A98;
			break;
		}
	} else {
		table = g_rva01356A88;
	}

	for (i = 0; i < 4; i++)
		for (j = 0; j < stride; j++)
			destination[i * stride + j] = source[i * stride + j];

	k = 1;
	while (k < height) {
		source += 8 * stride;
		destination += 8 * stride;
		rowFilter(ctx, source, destination, stride, width, offset, table);
		offset += width;
		k++;
	}

	for (i = 0; i < 4; i++)
		for (j = 0; j < stride; j++)
			destination[(i + 4) * stride + j] = source[(i + 4) * stride + j];

	lastFilter(ctx, source, destination, stride, width, offset, table);
}
