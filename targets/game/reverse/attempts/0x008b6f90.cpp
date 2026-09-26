// ?aptSetRectField008B6F90@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
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
AptValue* aptSetRectField008B6F90(Rva008B6D70Obj* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	int* field = (int*)self->m_rect;
	int value = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
	self->refresh(&(*field = value), self->m_extra, self->m_context);
	return Rva008B6D70MakeValue(0);
}
