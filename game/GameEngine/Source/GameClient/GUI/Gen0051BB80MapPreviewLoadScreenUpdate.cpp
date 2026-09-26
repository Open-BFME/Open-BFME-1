// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include

// Retail RVA 0x0051BB80 (236 bytes). Served from game/gen_asm/d_0051b7e0.asm.
// No named caller, vtable slot, or canonical class name proves the owner,
// but the tail of this body is byte-for-byte the same dispatch as
// MultiPlayerLoadScreen::update in the already-landed
// game/GameEngine/Source/GameClient/GUI/LoadScreenUpdates.cpp (TheNetwork
// branch calling NetworkInterface::updateLoadProgress/liteupdate, the
// no-network branch calling GameLogic::processProgress with
// GameInfo::getLocalSlotNum, then LoadScreen::update(percent) as the base
// call) -- and that base call is made with ecx=this (not through a vtable),
// so this class derives from the same LoadScreen. It is not any of that
// file's four catalogued subclasses (their addresses are all different), so
// it is a fifth, uncatalogued one: address-derived name kept. Unlike
// MultiPlayerLoadScreen, this override only runs that network dispatch when
// its own phase field (this+0x14) is 1, 2 or 5, and it first does one-time
// setup (an AptMapPreview map-name refresh) the first time update() runs.
//
// WHAT THE BYTES SHOW.  On the first call (this+0xA0 flag clear): if a
// has()-style predicate on the sub-object at this+0x18 passes, fetch
// GameInfo::getMap() from this+0x58 into a temporary AsciiString, hand it to
// AptMapPreview::rva005217A0 (this+0x18, still an unlanded dump reached
// through its own ILT thunk) and to BfmeThingBPF::bfmeGoBPF(this+0x18)
// with (GameInfo*, 1); then the flag is set so this only runs once. Every
// call then pokes a virtual notify at this+0x10 (vslot 2, arg 0), reads the
// phase at this+0x14, and for phase in {1,2,5} runs the
// MultiPlayerLoadScreen-shaped network dispatch using GameInfo at this+0x58
// (not the global) before falling into LoadScreen::update(percent) either
// way.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

// Reused verbatim from game/GameEngine/Source/Common/Rva00520460Has.cpp.
class Rva00520460
{
public:
	bool has();

private:
	char m_pad00[4];
	int m_04;
	char m_pad2[0xC];
	int m_vals[8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
// Reused from game/GameEngine/Source/GameClient/GUI/MpGameSetup.cpp so both
// getLocalSlotNum (vslot 5, +0x14) and getMap (this+0x3c) are in one layout.
class GameInfo
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual bool amIHost(void) const = 0;
	virtual int getLocalSlotNum(void) const = 0;

	AsciiString getMap(void) const;
};

// Still a dump; reached only through its own ILT thunk, called with the
// exact address-qualified signature already pinned in targets/game/reverse/symbols.csv
// (?rva005217A0@AptMapPreview@@QAEXABVAsciiString@@@Z).
class AptMapPreview
{
public:
	void rva005217A0(const AsciiString &mapName);
};

class BfmeThingBPF
{
public:
	void bfmeGoBPF(void *one, void *two);
};

#define BFME_VSLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
// Reused from LoadScreenUpdates.cpp's union-of-views table.
class NetworkInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8)
	virtual void liteupdate(int mode);              // +0x24
	virtual void update(int mode);                  // +0x28
	BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	BFME_VSLOT(14) BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17)
	BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20) BFME_VSLOT(21)
	BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24) BFME_VSLOT(25)
	BFME_VSLOT(26) BFME_VSLOT(27)
	virtual void updateLoadProgress(int percent);   // +0x70
};

#undef BFME_VSLOT

class GameLogic
{
public:
	void processProgress(int player, int percent);
};

// Address-derived interface for the object at this+0x10; only vslot 2
// (+0x08) is proven, called with one int argument.
class Rva0051BB80Notify
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void notify(int mode);   // +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class LoadScreen
{
public:
	virtual void slot00();
	virtual void update(int percent);
	virtual void init();
	virtual void reset();

protected:
	unsigned char m_unmodelled_04[4];
	void *m_loadScreen;        // +0x08
	unsigned char m_ready;     // +0x0C
	unsigned char m_unmodelled_0D[3];
};

// Address-derived: the four LoadScreenUpdates.cpp subclasses live at
// different retail addresses, so this is a fifth one.
class Gen_0051BB80 : public LoadScreen
{
public:
	virtual void update(int percent);

private:
	Rva0051BB80Notify *m_notifyTarget;  // +0x10 (vslot 2 notify)
	int m_phase;                // +0x14
	Rva00520460 m_hasSource;    // +0x18
	unsigned char m_pad30[0x58 - 0x18 - sizeof(Rva00520460)];
	GameInfo *m_gameInfo;       // +0x58
	unsigned char m_pad9C[0xA0 - 0x58 - 4];
	Bool m_mapShown;            // +0xA0
};

// ?update@Gen_0051BB80@@UAEXH@Z
void Gen_0051BB80::update(int percent)
{
	if (!m_mapShown)
	{
		if (m_hasSource.has())
		{
			((AptMapPreview *)&m_hasSource)->rva005217A0(m_gameInfo->getMap());
			((BfmeThingBPF *)&m_hasSource)->bfmeGoBPF(m_gameInfo, (void *)1);
			m_mapShown = true;
		}
	}

	m_notifyTarget->notify(0);

	int phase = m_phase;
	if (phase > 0 && (phase <= 2 || phase == 5))
	{
		extern NetworkInterface *TheNetwork;

		if (TheNetwork)
		{
			if (percent <= 100)
				TheNetwork->updateLoadProgress(percent);
			TheNetwork->liteupdate(0);
		}
		else if (percent <= 100)
		{
			extern GameLogic *TheBfmeGameLogic;
			TheBfmeGameLogic->processProgress(m_gameInfo->getLocalSlotNum(), percent);
		}
	}

	LoadScreen::update(percent);
}
