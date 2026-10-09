// ?copyPlane009AEEE0@@YAXPAURva009AF200Context@@HHH@Z
// partial score=0.3238 date=2026-10-09
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;
extern const void *g_rva01356A88;

struct Rva009AF200Context;

typedef void (__cdecl *Rva009AEEE0Operation)(
	Rva009AF200Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, int, const unsigned int *);

extern Rva009AEEE0Operation g_rva01356E94;
extern Rva009AEEE0Operation g_rva01356E88;

void __cdecl Rva009AD750(
	Rva009AF200Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, int, const unsigned int *);
struct Rva009ACC80Context;
void __cdecl Rva009ACC80Filter(
	Rva009ACC80Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, int, const unsigned int *);

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	void *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
	unsigned char m_pad3C[0x78 - 0x3C];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned m_extra84;
	unsigned m_extra88;
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

struct Rva009AEEE0DirectRows
{
	unsigned char *row;
	unsigned rows;
};

void copyPlane009AEEE0(Rva009AF200Context *ctx, int x, int y, int plane)
{
	Rva009AF200Context *self = ctx;
	int mode = self->m_mode;
	int sourceOffset;
	const unsigned int *callback = 0;
	Rva009AEEE0Operation operation;
	Rva009AEEE0Operation finalOperation;
	unsigned char *base;
	struct { unsigned width; unsigned height; } dimensions;
	unsigned stride;
	unsigned char *source;
	unsigned char *destination;
	int delta;
	Rva009AEEE0DirectRows direct;

	if (mode >= 2) {
		operation = g_rva01356E94;
		finalOperation = Rva009AD750;
	} else {
		operation = g_rva01356E88;
		finalOperation = reinterpret_cast<Rva009AEEE0Operation>(Rva009ACC80Filter);
	}

	int selector = plane;
	switch (selector) {
	case 0:
		sourceOffset = 0;
		dimensions.width = self->m_width;
		stride = self->m_strideY;
		base = self->m_planeY;
		dimensions.height = self->m_height;
		break;
	case 1:
		stride = self->m_strideUV;
		sourceOffset = self->m_extra84;
		base = self->m_planeU;
		dimensions.width = self->m_width >> 1;
		dimensions.height = self->m_height >> 1;
		break;
	default:
		stride = self->m_strideUV;
		sourceOffset = self->m_extra84 + self->m_extra88;
		base = self->m_planeV;
		dimensions.width = self->m_width >> 1;
		dimensions.height = self->m_height >> 1;
		break;
	}

	source = base + x;
	destination = base + y;

	if (mode >= 2) {
		switch ((unsigned)plane) {
		case 0:
			callback = g_rva01356AA0;
			break;
		case 1:
		case 2:
			callback = g_rva01356A98;
			break;
		}
	} else {
		callback = static_cast<const unsigned int *>(g_rva01356A88);
	}

	delta = (int)(source - destination);
	direct.row = destination;
	direct.rows = 4;
	while (direct.rows != 0) {
		unsigned char *cursor = direct.row;
		unsigned bytes = stride;
		while (bytes != 0) {
			*cursor = cursor[delta];
			++cursor;
			--bytes;
		}
		direct.row += stride;
		--direct.rows;
	}

	if (dimensions.height > 1) {
		unsigned count = dimensions.height - 1;
		unsigned eightRows = stride * 8;
		do {
			source += eightRows;
			destination += eightRows;
			operation(self, source, destination, stride, dimensions.width, sourceOffset, callback);
			sourceOffset += dimensions.width;
			--count;
		} while (count != 0);
	}

	delta = (int)(source - destination);
	direct.row = destination + stride * 4;
	direct.rows = 4;
	while (direct.rows != 0) {
		unsigned char *cursor = direct.row;
		unsigned bytes = stride;
		while (bytes != 0) {
			*cursor = cursor[delta];
			++cursor;
			--bytes;
		}
		direct.row += stride;
		--direct.rows;
	}

	finalOperation(self, source, destination, stride, dimensions.width, sourceOffset, callback);
}

