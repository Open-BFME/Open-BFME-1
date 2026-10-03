// ?aptSetFieldNeg008B6FF0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: five more Apt script setter callbacks (70 B each): store the
// last argument as an integer into one member then refresh with the extra
// block first and the context negated.
class AptValue { public: int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
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
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x50) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B70D0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B70D0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x48) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B7120@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B7120(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x5C) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B7170@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B7170(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x44) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// ?aptSetFieldNeg008B71C0@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
AptValue* aptSetFieldNeg008B71C0(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x54) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}

// Same negative refresh path, using the first integer in the extra block.
AptValue* aptSetFieldNeg008B7210(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	*(int*)((char*)self + 0x40) = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	self->refreshNeg(self->m_extra, self->m_rect, -self->m_context);
	return Rva008B6D70MakeValue(0);
}
