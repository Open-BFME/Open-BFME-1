// ?aptSetFieldNeg008B6FF0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: five more Apt script setter callbacks (70 B each): store the
// last argument as an integer into one member then refresh with the extra
// block first and the context negated.
class AptValue { public: int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
struct Rva008B6D70Obj {
	char m_pad0[0x20];
	char m_rect[0x20];
	char m_extra[0x20];
	int m_context;
	void refreshNeg(void* extra, void* rect, int negContext);
};
AptValue* __cdecl Rva008B6D70MakeValue(int value);

AptValue* aptSetFieldNeg008B6FF0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x50) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B70D0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B70D0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x48) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B7120@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B7120(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x5C) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B7170@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B7170(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x44) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B71C0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B71C0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x54) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}
