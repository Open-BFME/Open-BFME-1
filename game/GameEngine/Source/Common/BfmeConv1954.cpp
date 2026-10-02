// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/PlayerList.h"

// Shared empty string at retail VA 0x0107388B.
extern const char g_bfmeEmptyAscii[];

struct BfmeStrDataERJ
{
	int m_bfmeRefERJ;
	int m_bfmeLenERJ;
	char m_bfmeTextERJ[1];
};

class BfmeStrERJ
{
public:
	const char *bfmeTextERJ() const
	{
		return m_bfmeDataERJ ? m_bfmeDataERJ->m_bfmeTextERJ : g_bfmeEmptyAscii;
	}

	BfmeStrDataERJ *m_bfmeDataERJ;
};

class BfmePlayerERJ
{
public:
	unsigned char m_bfmeHeadERJ[0x20];
	int m_bfmeKeyERJ;
};

// Retail's player-list global at 0x012ED748, spelled canonically so this TU
// links against game/GameEngine/Source/Common/RTS/PlayerList.cpp's definition.
class PlayerList;
extern PlayerList *ThePlayerList;

struct BfmeEntryERJ
{
	unsigned char m_bfmeHeadERJ[8];
	void *m_bfmeValueERJ;
	unsigned char m_bfmeTailERJ[12];
};

// TU-local view of the same object, kept for the member call shape.
class BfmeTableERJ
{
public:
	BfmeEntryERJ *bfmeAtERJ(int index)
	{
		if (index >= 0 && index < m_bfmeCountERJ)
			return m_bfmeEntriesERJ + index;

		return 0;
	}

	unsigned char m_bfmeHeadERJ[0x28];
	int m_bfmeCountERJ;
	BfmeEntryERJ m_bfmeEntriesERJ[1];
};

// Retail's side-table global at 0x012EF428, spelled canonically so this TU links
// against the definition.  The definition lives in
// game/GameEngine/Source/Common/System/game_engine_subsystems.h.
class SidesList;
extern SidesList *TheSidesList;

void * __stdcall bfmeLookupERJ(BfmeStrERJ *name)
{
	int key = TheNameKeyGenerator->nameToKey(name->bfmeTextERJ());

	for (int i = 0; i < ((BfmeTableERJ *)TheSidesList)->m_bfmeCountERJ; ++i)
	{
		BfmePlayerERJ *player = (BfmePlayerERJ *)ThePlayerList->getNthPlayer(i);

		if (player != 0 && player->m_bfmeKeyERJ == key)
			return ((BfmeTableERJ *)TheSidesList)->bfmeAtERJ(i)->m_bfmeValueERJ;
	}

	return 0;
}
