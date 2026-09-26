// ?Rva00462D40@@YAXPAX@Z
// partial score=0.35 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
#define WINDOW_MANAGER_SLOT(n) virtual void slot##n() = 0
	WINDOW_MANAGER_SLOT(00); WINDOW_MANAGER_SLOT(01); WINDOW_MANAGER_SLOT(02);
	WINDOW_MANAGER_SLOT(03); WINDOW_MANAGER_SLOT(04); WINDOW_MANAGER_SLOT(05);
	WINDOW_MANAGER_SLOT(06); WINDOW_MANAGER_SLOT(07); WINDOW_MANAGER_SLOT(08);
	WINDOW_MANAGER_SLOT(09); WINDOW_MANAGER_SLOT(10); WINDOW_MANAGER_SLOT(11);
	WINDOW_MANAGER_SLOT(12); WINDOW_MANAGER_SLOT(13); WINDOW_MANAGER_SLOT(14);
	WINDOW_MANAGER_SLOT(15); WINDOW_MANAGER_SLOT(16); WINDOW_MANAGER_SLOT(17);
	WINDOW_MANAGER_SLOT(18); WINDOW_MANAGER_SLOT(19); WINDOW_MANAGER_SLOT(20);
	WINDOW_MANAGER_SLOT(21); WINDOW_MANAGER_SLOT(22); WINDOW_MANAGER_SLOT(23);
	WINDOW_MANAGER_SLOT(24); WINDOW_MANAGER_SLOT(25); WINDOW_MANAGER_SLOT(26);
	WINDOW_MANAGER_SLOT(27); WINDOW_MANAGER_SLOT(28); WINDOW_MANAGER_SLOT(29);
	WINDOW_MANAGER_SLOT(30); WINDOW_MANAGER_SLOT(31); WINDOW_MANAGER_SLOT(32);
	WINDOW_MANAGER_SLOT(33); WINDOW_MANAGER_SLOT(34); WINDOW_MANAGER_SLOT(35);
	WINDOW_MANAGER_SLOT(36); WINDOW_MANAGER_SLOT(37); WINDOW_MANAGER_SLOT(38);
	WINDOW_MANAGER_SLOT(39); WINDOW_MANAGER_SLOT(40); WINDOW_MANAGER_SLOT(41);
	WINDOW_MANAGER_SLOT(42); WINDOW_MANAGER_SLOT(43);
#undef WINDOW_MANAGER_SLOT
	virtual void slot44( GameWindow *window ) = 0;
};

extern GameWindowManager *TheWindowManager;
extern char g_bfmeTwoSJA[];
extern char g_bfmeDoneSJA;

extern void j_00041afb(void);
extern void j_0001bdc9(void);
extern void j_00035b48(void);

typedef void (__cdecl *BfmeDoBSDFn)(void *, void *) throw();
typedef void (__cdecl *ForEachFn)(void *) throw();

// address-derived: g_bfmeTwoSJA (0x012F19A4) as the AsciiString-keyed hash_map
// already established by BfmeConv1292.cpp; begin() reached through its own
// ILT thunk (retail 0x0045FA00, byte-identical across every hashtable
// instantiation with this bucket layout -- landed as tg_0045fa00 in Player.cpp
// only because ICF folded it there first).
class Rva00462D40Iterator
{
public:
	void *m_cur;
	void *m_table;
};

class Rva00462D40Table
{
public:
	Rva00462D40Iterator begin()
	{
		typedef void (Rva00462D40Table::*BeginFn)(Rva00462D40Iterator *) throw();
		union
		{
			void (*freeFn)(void);
			BeginFn memberFn;
		} thunk;
		thunk.freeFn = j_0001bdc9;
		Rva00462D40Iterator result;
		(this->*thunk.memberFn)(&result);
		return result;
	}
};

// Retail 0x00462D40 (126B): given a non-empty string, run it through
// bfmeDoBSD, then for_each over the g_bfmeTwoSJA hashtable's [begin, end)
// range through the checker at 0x00462710. Retail also calls the matched
// StringBase<char>::releaseBuffer at +0x5A; this partial source omits that
// cleanup and must not be treated as a complete reconstruction. On a null or
// empty string, flag g_bfmeDoneSJA and dispatch TheWindowManager's slot44 with a null window
// instead. No caller, class or method identity survived the identity sweep
// (blocked once: t=5min model=gpt-5.6, "no direct caller, no vtable pointer
// reference, no source emitter"); every name here is address-derived.
void Rva00462D40(void *p)
{
	if (!p || !*(const char *)p)
	{
		g_bfmeDoneSJA = 1;
		TheWindowManager->slot44(0);
		return;
	}

	unsigned int bsdResult;
	((BfmeDoBSDFn)j_00041afb)(&bsdResult, p);

	Rva00462D40Iterator it = ((Rva00462D40Table *)g_bfmeTwoSJA)->begin();
	((ForEachFn)j_00035b48)(&it);
}
