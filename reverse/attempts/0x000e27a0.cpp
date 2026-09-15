// ??1PlayerTemplate@@QAE@XZ
// partial score=0.78 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Retail BFME PlayerTemplate layout recovered from its constructor, destructor,
// image-name INI table, and the exact 0x124-byte vector stride.

#include "Common/INI.h"
#include "Common/Money.h"
#include "Common/NameKeyGenerator.h"
#include <vector>

template <class CharT> class BfmeStringBase
{
public:
	~BfmeStringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	CharT *m_data;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

#pragma comment(linker, "/alternatename:?releaseBuffer@?$BfmeStringBase@G@@AAEXXZ=?releaseBuffer@?$StringBase@G@@AAEXXZ")
#pragma comment(linker, "/alternatename:?releaseBuffer@BFMERetailAsciiString@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

struct BfmeRGBColor
{
	float red;
	float green;
	float blue;
};

class BfmeMap60
{
public:
	~BfmeMap60();
	char m_data[0x0c];
};

class BfmeMap6C
{
public:
	~BfmeMap6C();
	char m_data[0x14];
};

class BfmeMap80
{
public:
	~BfmeMap80();
	char m_data[0x0c];
};

class BfmeMapE8
{
public:
	~BfmeMapE8();
	char m_data[0x0c];
};

#pragma comment(linker, "/alternatename:??1BfmeMap60@@QAE@XZ=?j_000032b5@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeMap6C@@QAE@XZ=?j_00032227@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeMap80@@QAE@XZ=?j_0002ac20@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeMapE8@@QAE@XZ=?j_00026ab2@@YAXXZ")

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *value);

class BfmeSoundObject
{
public:
	virtual ~BfmeSoundObject();
	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}
	volatile long m_refCount;
};

class BfmeSoundEvent
{
public:
	~BfmeSoundEvent()
	{
		BfmeSoundObject *object = m_object;
		if (object != 0)
			object->Release_Ref();
	}

	BfmeSoundObject *m_object;
};

class PlayerTemplate
{
public:
	~PlayerTemplate();

private:
	NameKeyType m_nameKey;                         // +0x000
	BfmeStringBase<unsigned short> m_displayName;  // +0x004
	BFMERetailAsciiString m_side;                  // +0x008
	char m_handicap[0x10];                         // +0x00c
	Money m_money;                                 // +0x01c
	BfmeRGBColor m_preferredColor;                 // +0x028
	BFMERetailAsciiString m_startingBuilding;      // +0x034
	BFMERetailAsciiString m_startingUnits[10];     // +0x038
	BfmeMap60 m_productionCostChanges;             // +0x060
	BfmeMap6C m_productionTimeChanges;             // +0x06c
	BfmeMap80 m_productionVeterancyLevels;         // +0x080
	_STL::vector<int> m_intrinsicSciences;         // +0x08c
	_STL::vector<int> m_intrinsicSciencesMP;       // +0x098
	BFMERetailAsciiString m_purchaseScienceCommandSet;       // +0x0a4
	BFMERetailAsciiString m_purchaseScienceCommandSetMP;     // +0x0a8
	BFMERetailAsciiString m_specialPowerShortcutCommandSet;  // +0x0ac
	BFMERetailAsciiString m_specialPowerShortcutWinName;     // +0x0b0
	int m_specialPowerShortcutButtonCount;         // +0x0b4
	BFMERetailAsciiString m_loadScreenMusic;       // +0x0b8
	bool m_observer;                               // +0x0bc
	bool m_playableSide;                           // +0x0bd
	char m_padBE[2];
	int m_intrinsicSPP;                            // +0x0c0
	int m_maxLevelMP;                              // +0x0c4
	int m_maxLevelSP;                              // +0x0c8
	BFMERetailAsciiString m_scoreScreenImage;      // +0x0cc
	BFMERetailAsciiString m_loadScreenImage;       // +0x0d0
	BFMERetailAsciiString m_headWaterMark;          // +0x0d4
	BFMERetailAsciiString m_flagWaterMark;          // +0x0d8
	BFMERetailAsciiString m_enabledImage;           // +0x0dc
	BFMERetailAsciiString m_sideIconImage;          // +0x0e0
	BFMERetailAsciiString m_beaconTemplate;         // +0x0e4
	BfmeMapE8 m_initialUpgrades;                   // +0x0e8
	BfmeMapE8 m_buildableHeroesMP;                 // +0x0f4
	BfmeSoundEvent m_lightPointsUpSound;           // +0x100
	BfmeSoundEvent m_objectiveAddedSound;          // +0x104
	BfmeSoundEvent m_objectiveCompletedSound;      // +0x108
	BFMERetailAsciiString m_defaultPlayerAIType;   // +0x10c
	BFMERetailAsciiString m_spellBook;             // +0x110
	BFMERetailAsciiString m_spellBookMP;           // +0x114
	bool m_evil;                                   // +0x118
	char m_pad119[3];
	BFMERetailAsciiString m_spellStoreCurrentPowerLabel;     // +0x11c
	BFMERetailAsciiString m_spellStoreMaximumPowerLabel;     // +0x120
};

// ??1PlayerTemplate@@QAE@XZ present-unmatched
PlayerTemplate::~PlayerTemplate()
{
}
