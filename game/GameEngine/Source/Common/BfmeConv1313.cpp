// Open-BFME5 conversions.
//
// The retail calls land on ILT thunks (0x00039C2F, 0x0001E402, 0x0003F9EA,
// 0x0000C9B4), so each reference is spelled as that thunk's real symbol, the
// idiom BfmeConv1808.cpp uses. VC7.1 rejects __thiscall on a free function
// pointer (C4234), so the thunks called with ecx = this go through a
// member-function pointer, the idiom MilesAudioManagerRva006A5E60.cpp uses.

extern "C" void __cdecl __identifier("?j_00039c2f@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0001e402@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0003f9ea@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0000c9b4@@YAXXZ")(void *what, int *tail);

extern "C" __declspec(dllimport) void *__stdcall SetErrorMode(int a);

// 0x0111C9A8 is the W3D/Win32 GameEngine vftable; symbols.csv pins it as
// ?g_bfme928Vft@@3PADA, the spelling BfmeConv928.cpp already uses.
extern "C" void __cdecl __identifier("?j_00021571@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0002badf@@YAXXZ")();
extern "C" void __cdecl __identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")();
extern "C" void __cdecl __identifier("?j_000436b2@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00018d81@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00045ac0@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00033497@@YAXXZ")();
extern "C" void __cdecl __identifier("?method@Rva009A16C0@@UAEXXZ")();
extern "C" void __cdecl __identifier("?method@Rva009A16D0@@UAEXI@Z")();
extern "C" void __cdecl __identifier("?j_0003f512@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000173e6@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000190f6@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00040435@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0002a0ea@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0002700c@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00034ee6@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0001c6cf@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0003e789@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00023b7d@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0000eb7e@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0003da96@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0001c4ae@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000418f3@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00025644@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000260f8@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00041605@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0000c9c3@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00038eb0@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00041ab0@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00023df3@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0001dc7d@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0002cd45@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00008ce7@@YAXXZ")();
// C++ view of the same symbol: 33 four-byte slots (sizes the datum).
extern char g_bfme928Vft[132];
// Retail 0x0111C9A8 slots, read from the image (vtable_lookup.py); each is the
// ILT thunk or direct body retail stores there.
extern "C" void *__identifier("?g_bfme928Vft@@3PADA")[] =
{
	(void *)&__identifier("?j_00021571@@YAXXZ"),
	(void *)&__identifier("?j_0002badf@@YAXXZ"),
	(void *)&__identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ"),
	(void *)&__identifier("?j_000436b2@@YAXXZ"),
	(void *)&__identifier("?j_00018d81@@YAXXZ"),
	(void *)&__identifier("?j_00045ac0@@YAXXZ"),
	(void *)&__identifier("?j_00033497@@YAXXZ"),
	(void *)&__identifier("?method@Rva009A16C0@@UAEXXZ"),
	(void *)&__identifier("?method@Rva009A16D0@@UAEXI@Z"),
	(void *)&__identifier("?j_0003f512@@YAXXZ"),
	(void *)&__identifier("?j_000173e6@@YAXXZ"),
	(void *)&__identifier("?j_000190f6@@YAXXZ"),
	(void *)&__identifier("?j_00040435@@YAXXZ"),
	(void *)&__identifier("?j_0002a0ea@@YAXXZ"),
	(void *)&__identifier("?j_0002700c@@YAXXZ"),
	(void *)&__identifier("?j_00034ee6@@YAXXZ"),
	(void *)&__identifier("?j_0001c6cf@@YAXXZ"),
	(void *)&__identifier("?j_0003e789@@YAXXZ"),
	(void *)&__identifier("?j_00023b7d@@YAXXZ"),
	(void *)&__identifier("?j_0000eb7e@@YAXXZ"),
	(void *)&__identifier("?j_0003da96@@YAXXZ"),
	(void *)&__identifier("?j_0001c4ae@@YAXXZ"),
	(void *)&__identifier("?j_000418f3@@YAXXZ"),
	(void *)&__identifier("?j_00025644@@YAXXZ"),
	(void *)&__identifier("?j_000260f8@@YAXXZ"),
	(void *)&__identifier("?j_00041605@@YAXXZ"),
	(void *)&__identifier("?j_0000c9c3@@YAXXZ"),
	(void *)&__identifier("?j_00038eb0@@YAXXZ"),
	(void *)&__identifier("?j_00041ab0@@YAXXZ"),
	(void *)&__identifier("?j_00023df3@@YAXXZ"),
	(void *)&__identifier("?j_0001dc7d@@YAXXZ"),
	(void *)&__identifier("?j_0002cd45@@YAXXZ"),
	(void *)&__identifier("?j_00008ce7@@YAXXZ")
};

class BfmeThingTGE
{
public:
	BfmeThingTGE();
	void *m_bfmeVft;
	char m_bfmePad[0x58];
	void *m_bfmeHandle;
};

class BfmeSubTGB
{
public:
	void bfmeSetTGB(int a);
};

class BfmeThingTGB
{
public:
	void bfmeGoTGB(int a);
	void bfmeUseTGB(int a);
};

union BaseThunkTGE
{
	void (*raw)();
	void (BfmeThingTGE::*member)();
};

union SetThunkTGB
{
	void (*raw)();
	void (BfmeSubTGB::*member)(int);
};

union UseThunkTGB
{
	void (*raw)();
	void (BfmeThingTGB::*member)(int);
};

BfmeThingTGE::BfmeThingTGE()
{
	BaseThunkTGE base;
	base.raw = __identifier("?j_00039c2f@@YAXXZ");
	(this->*base.member)();
	m_bfmeVft = __identifier("?g_bfme928Vft@@3PADA");
	m_bfmeHandle = SetErrorMode(1);
}

void BfmeThingTGB::bfmeGoTGB(int a)
{
	SetThunkTGB set;
	set.raw = __identifier("?j_0001e402@@YAXXZ");
	((*(BfmeSubTGB **)((char *)this - 0x18))->*set.member)(3);

	UseThunkTGB use;
	use.raw = __identifier("?j_0003f9ea@@YAXXZ");
	(this->*use.member)(a);
}

struct BfmeArgTGC
{
	int m_bfmeHead;
	int m_bfmeTail;
};

class BfmeSourceTGC
{
public:
	virtual void bfmeV0TGC() = 0;
	virtual void bfmeV1TGC() = 0;
	virtual void bfmeV2TGC() = 0;
	virtual void bfmeV3TGC() = 0;
	virtual void bfmeV4TGC() = 0;
	virtual void bfmeV5TGC() = 0;
	virtual void bfmeV6TGC() = 0;
	virtual void bfmeV7TGC() = 0;
	virtual void bfmeV8TGC() = 0;
	virtual void bfmeV9TGC() = 0;
	virtual void bfmeV10TGC() = 0;
	virtual void bfmeV11TGC() = 0;
	virtual void bfmeV12TGC() = 0;
	virtual void bfmeV13TGC() = 0;
	virtual void bfmeV14TGC() = 0;
	virtual void bfmeV15TGC() = 0;
	virtual void bfmeV16TGC() = 0;
	virtual void bfmeV17TGC() = 0;
	virtual void bfmeV18TGC() = 0;
	virtual void bfmeV19TGC() = 0;
	virtual void bfmeV20TGC() = 0;
	virtual void bfmeV21TGC() = 0;
	virtual void bfmeV22TGC() = 0;
	virtual void bfmeV23TGC() = 0;
	virtual void bfmeV24TGC() = 0;
	virtual void bfmeV25TGC() = 0;
	virtual void *bfmeGetTGC(BfmeArgTGC *p) = 0;
};

void bfmeGoTGC(BfmeSourceTGC *src, BfmeArgTGC *p)
{
	__identifier("?j_0000c9b4@@YAXXZ")(src->bfmeGetTGC(p), &p->m_bfmeTail);
}