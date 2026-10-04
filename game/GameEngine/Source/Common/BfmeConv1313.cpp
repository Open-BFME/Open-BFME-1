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
extern "C" char __identifier("?g_bfme928Vft@@3PADA")[];

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