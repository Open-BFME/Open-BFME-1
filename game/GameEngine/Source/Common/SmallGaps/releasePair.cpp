// ?releasePair@@YAXXZ
struct Rva008A4AC0Object { virtual void slot0(); virtual void release(); };
// Retail .bss VA 0x01337AC0/0x01337AC4: the two objects releasePair releases. Address-derived names.
Rva008A4AC0Object* g_Va01337AC0;
Rva008A4AC0Object* g_Va01337AC4;
void releasePair()
{
	if (g_Va01337AC0) { g_Va01337AC0->release(); g_Va01337AC0 = 0; }
	if (g_Va01337AC4) { g_Va01337AC4->release(); g_Va01337AC4 = 0; }
}
