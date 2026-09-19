// ?aptSetField008B6D70@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: six Apt script setter callbacks (68 B each) that store the
// last argument as an integer into one member of the object and refresh it.
class AptValue { public: int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
struct Rva008B6D70Obj {
	char m_pad0[0x20];
	char m_rect[0x20];
	char m_extra[0x20];
	void* m_context;
	void refresh(void* rect, void* extra, void* context);
};
AptValue* __cdecl Rva008B6D70MakeValue(int value);

AptValue* aptSetField008B6D70(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x30) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetField008B6E50@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetField008B6E50(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x28) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetField008B6EA0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetField008B6EA0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x3C) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetField008B6EF0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetField008B6EF0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x24) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetField008B6F40@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetField008B6F40(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x34) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetField008B7260@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetField008B7260(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	*(int*)((char*)self + 0x38) = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(self->m_rect, self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}
