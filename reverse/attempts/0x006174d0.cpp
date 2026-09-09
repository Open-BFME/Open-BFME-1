// ?update@BfmeLivingWorldManager@@QAEXXZ
// partial score=0.99 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: retail RVA 0x006174D0, 369 bytes.
//
// The retail string xref names this body LivingWorldManager::update.  The
// adjacent constructor, cleanup, particle, and map methods use the same
// manager.  This update advances its integer-keyed object map, updates the
// eye-tower state, and handles the cursor transition after the map pass.

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class GameLogicFp
{
public:
	char m_pad00[0x1A0];
	int m_fp;
};

extern GameLogicFp *TheBfmeGameLogic;
extern void setFPMode();

class BfmeHostDQ
{
public:
	void bfmeTickDQ();
};

class Rva0060FEB0Owner
{
public:
	void resetAll();
};

class Gen0060CBB0
{
public:
	void updateState();
};

class Rva003BF540
{
public:
	bool anyMatching(int mask);
};

class BfmeC977
{
public:
	char bfmeGo977C();
};

class Mouse
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38(int cursor) = 0;

	void _bfme_setEngineVisibility(bool visible);
};

class Glo012F4B98Type
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void finish() = 0;
};

extern unsigned char Rva00563970GetFlag();
extern void ShowControlBar(int show);
extern void j_00004c3c();
extern void j_000231f0();
extern void j_00047dc5();
extern void j_0003a17a();

extern Mouse *TheMouse;

class Rva006174D0Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void update() = 0;
};

typedef _STL::hash_map<int, void *> Rva006174D0Map;

struct Rva006174D0State
{
	char m_pad00[4];
	int m_field04;
};

class BfmeLivingWorldManager
{
public:
	void update();

private:
	char m_pad00[0x210];
	char m_objects[0x14];
	char m_pad224[0x64];
	bool m_flag288;
	char m_pad289[3];
	Gen0060CBB0 *m_eyeTower;
};

#define TheState (*(Rva006174D0State **)0x012F7048)
#define TheGlobal012F1028 (*(Rva003BF540 **)0x012F1028)
#define TheGlobal012F19E8 (*(BfmeC977 **)0x012F19E8)
#define TheGlobal012F4B98 (*(Glo012F4B98Type **)0x012F4B98)
#define CritterDesyncSink (*(void **)0x012ED4FC)

// ?update@BfmeLivingWorldManager@@QAEXXZ
void BfmeLivingWorldManager::update()
{
	GameLogicFp *logic = TheBfmeGameLogic;
	int *fp = &logic->m_fp;
	if (*fp == 0)
		setFPMode();
	++*fp;

	if (CritterDesyncSink)
	{
		((void (__cdecl *)(void *, const char *))j_0003a17a)(
			CritterDesyncSink, (const char *)0x01116C60);
	}

	((void (__fastcall *)(BfmeLivingWorldManager *))j_00004c3c)(this);
	((Rva0060FEB0Owner *)this)->resetAll();
	((void (__fastcall *)(BfmeLivingWorldManager *))j_000231f0)(this);
	((BfmeHostDQ *)this)->bfmeTickDQ();

	if (m_eyeTower)
		m_eyeTower->updateState();

	Rva006174D0Map *objects = (Rva006174D0Map *)m_objects;
	for (Rva006174D0Map::iterator it = objects->begin();
		it != objects->end(); ++it)
	{
		((Rva006174D0Object *)it->second)->update();
	}

	if (!m_flag288 && TheState->m_field04 == 1
		&& Rva00563970GetFlag()
		&& !TheGlobal012F1028->anyMatching(8))
	{
		ShowControlBar(1);
		if (TheMouse)
			TheMouse->_bfme_setEngineVisibility(true);
	}

	Glo012F4B98Type *global012F4B98 = TheGlobal012F4B98;
	global012F4B98->finish();
	--TheBfmeGameLogic->m_fp;

	void *desyncSink = CritterDesyncSink;
	if (desyncSink)
	{
		((void (__cdecl *)(void *, const char *))j_0003a17a)(
			desyncSink, (const char *)0x01116C40);
	}

	if (TheState->m_field04 == 0
		&& !TheGlobal012F19E8->bfmeGo977C())
	{
		TheMouse->slot38(0x28);
	}
}
