// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef void (__cdecl *Rva009C84D0FilterCopy)(void *, void *, int, int);
typedef void (__cdecl *Rva009C84D0FilterRow)(void *, int, int);

extern Rva009C84D0FilterCopy g_rva01356B40;
extern Rva009C84D0FilterRow g_rva01356E8C;
extern Rva009C84D0FilterRow g_rva01356E98;

struct Rva009C84D0Vp6Context
{
	unsigned char m_pad00[0x74];
	int m_stride;
	unsigned char m_pad78[4];
	int m_shift;
	unsigned char m_pad80[8];
	int m_verticalStride;
	unsigned char m_pad8C[0x13C - 0x8C];
	void *m_rowState;
	unsigned char m_pad140[0x290 - 0x140];
	void *m_copyState;
};

// ?Rva009C84D0Vp6Filter@@YAXPAURva009C84D0Vp6Context@@PAXHH@Z
void __cdecl Rva009C84D0Vp6Filter(
	Rva009C84D0Vp6Context *context, void *base, int x, int y)
{
	void *copyState = context->m_copyState;
	int scaledX = x;
	int scaledY = y;
	if (scaledX > 0) {
		scaledX >>= context->m_shift;
	} else {
		scaledX = -scaledX;
		scaledX >>= context->m_shift;
		scaledX = -scaledX;
	}
	if (scaledY > 0) {
		scaledY >>= context->m_shift;
	} else {
		scaledY = -scaledY;
		scaledY >>= context->m_shift;
		scaledY = -scaledY;
	}

	int source = context->m_verticalStride * scaledY;
	source -= context->m_stride * 2 + 2;
	source += scaledX;
	source += (int)base;
	g_rva01356B40((void *)source, copyState,
		context->m_stride, 0x10);

	scaledX = -scaledX;
	scaledY = -scaledY;
	scaledX &= 7;
	scaledY &= 7;
	if (scaledX != 0) {
		void *row = *(void **)context->m_rowState;
		g_rva01356E8C(row, scaledX + (int)copyState + 2, 0x10);
	}
	if (scaledY != 0) {
		void *row = *(void **)context->m_rowState;
		scaledY += 2;
		scaledY <<= 4;
		scaledY += (int)copyState;
		g_rva01356E98(row, scaledY, 0x10);
	}
}
