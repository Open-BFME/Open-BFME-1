// cl: /O2
// 0x007EB8B0: FESL debug.cpp vararg log. vsprintf into mVarArgBuffer, emit
// through vslot 1, then assert the last byte is still NUL.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *g_Va0130A5A0;

extern "C"
{
	int __cdecl vsprintf(char *buf, const char *fmt, char *args);
}

class Rva007EB8B0Log
{
public:
	virtual void setFields_007EB760(int valueAt08, int valueAt04);
	virtual void emit(char *buf);
	void bfmeSetSizeVLR(int size);

	int m_04;
	int m_08;
	char *m_0C;
	int m_10;
};

void Rva007EB8B0(Rva007EB8B0Log *self, unsigned int need, const char *fmt, ...)
{
	if (need > (unsigned int)self->m_10 || !self->m_0C)
		self->bfmeSetSizeVLR((int)need);
	vsprintf(self->m_0C, fmt, (char *)(&fmt + 1));
	self->emit(self->m_0C);
	if (self->m_0C[self->m_10 - 1])
		g_Va0130A5A0->fail(
			"!mVarArgBuffer[mVarArgBufferSize - 1]",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\debug.cpp",
			123);
}

// Retail vtable 0x01129D30 slot 0 points directly to RVA 0x007EB760.
// Slots 2-4 are the matched log/assert/error methods in this class family.
// Both boundaries are padded; the complete 17-byte body ends in ret 8.
// The field meanings remain unproven, so preserve their witnessed offsets.
void Rva007EB8B0Log::setFields_007EB760(int valueAt08, int valueAt04)
{
	m_04 = valueAt04;
	m_08 = valueAt08;
}
