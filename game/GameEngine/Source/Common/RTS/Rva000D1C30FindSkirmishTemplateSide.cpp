// ?findSkirmishTemplateSide@Rva000D1C30Owner@@QAE_NPAH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// Scans TheSidesList's skirmish sides for a faction whose PlayerTemplate side equals this+0x28.
// Only caller: Player::initFromDict (0x000DB020) via ILT 0x00032952 with its Player as ECX.
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "unicode_string.h"
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Dict.h"

// 24-byte skirmish side record; the Dict sits at +4 as in PlayerRva000D1E30.cpp.
struct BfmeSkirmishSide
{
	char m_prefix[4];
	Dict m_dict;
	char m_suffix[0x10];
};

// TU-local layout view of the 0x012EF428 singleton, kept for the member call
// shape.  The global itself is declared with its canonical retail type below.
class BfmeSidesList
{
public:
	char m_prefix[0x32c];
	int m_numSkirmishSides;
	BfmeSkirmishSide m_skirmishSides[1];

	BfmeSkirmishSide *getSkirmishSideInfo(int index)
	{
		if (index >= 0 && index < m_numSkirmishSides)
			return &m_skirmishSides[index];
		return 0;
	}
};

// Canonical retail type of the 0x012EF428 singleton; pointee only, so a forward
// declaration is enough.  The definition lives in
// game/GameEngine/Source/Common/System/game_engine_subsystems.h.
class SidesList;

// Retail global at 0x012EF428, ?TheSidesList@@3PAVSidesList@@A.
extern SidesList *TheSidesList;
// The key global at 0x012A7938; the Zero Hour twin reads TheKey_playerFaction here.
extern const StaticNameKey TheKey_playerFaction;

class PlayerTemplate
{
public:
	char m_pad00[8];
	AsciiString m_side;					///< retail this+0x08
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class Rva000D1C30Owner
{
public:
	Bool findSkirmishTemplateSide(int *index);

private:
	char m_prefix[0x28];
	AsciiString m_compareSide;				///< retail this+0x28
};

// Owner stays address-derived; retail's unwind funclets destroy both locals through ~AsciiString (ILT 0x0000D828).
Bool Rva000D1C30Owner::findSkirmishTemplateSide(int *index)
{
	int count = ((BfmeSidesList *)TheSidesList)->m_numSkirmishSides;
	AsciiString compareSide(m_compareSide);

	for (int i = 0; i < count; ++i)
	{
		AsciiString sideName =
			((BfmeSidesList *)TheSidesList)->getSkirmishSideInfo(i)->m_dict.getAsciiString(TheKey_playerFaction.key());
		const PlayerTemplate *tmpl = ThePlayerTemplateStore->findPlayerTemplate(
			TheNameKeyGenerator->nameToKey(sideName.str()));
		if (tmpl != 0 && tmpl->m_side.compare(compareSide) == 0)
		{
			*index = i;
			return true;
		}
	}
	return false;
}
