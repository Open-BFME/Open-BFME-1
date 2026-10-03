// ?aptSetRectField008B6F90@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// RVA 008B6F90, 73 bytes through RET at 008B6FD8; followed by INT3.
// The address-qualified owner is an ABI view, not a recovered EA identity.
// 008B65E0 uses its third argument as a signed integer; refreshNeg is the
// existing integer-ABI binding, also used by the neighboring setters.
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: int toInteger() const; };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
struct Rva008B6D70Obj {
	char m_pad0[0x20];
	int m_rect[8];
	int m_extra[8];
	int m_context;
	void refreshNeg(void* rect, void* extra, int context);
};
class AptInteger { public: static AptInteger* Create(int value); };
AptValue* aptSetRectField008B6F90(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	int value = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->m_rect[0] = value;
	self->refreshNeg(self->m_rect, self->m_extra, self->m_context);
	return (AptValue*)AptInteger::Create(0);
}
