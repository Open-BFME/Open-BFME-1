// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ScriptEngine::undoNamedMapReveal, retail 0x0034D320, 226 bytes.
//
// The reference's body, sharing its first half with removeNamedMapReveal --
// the same scan of the 0x10-stride vector at ScriptEngine+0x175F8 with the
// same inlined AsciiString compare -- and diverging once the entry is found.
//
// NamedReveal is reordered here: the reveal radius sits at +8 and the player
// name at +0x0C, where the reference has them the other way round. The two
// `lea`s off the element say so directly, one feeding the player-mask lookup
// and the other pushed as the radius.
//
// And the reference's three steps collapse to two. The player is never
// materialised: BFME asks the script engine for the mask straight from the
// name and never checks it, so the only bail-out left is the waypoint. The
// reveal then takes the waypoint location whole rather than an x and a y,
// three arguments instead of four.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct Coord3D { Real x, y, z; };

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// Delegating, and visibly so: it is what puts the __$SEHRec$ store ahead of
	// `mov ecx, esp` when the by-value name is built in the outgoing argument
	// slot for getWaypointByName.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString();

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

	Bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
struct NamedReveal
{
	AsciiString m_revealName;				// +0x00
	AsciiString m_waypointName;				// +0x04
	Real m_radiusToReveal;					// +0x08
	AsciiString m_playerName;				// +0x0C
};

typedef _STL::vector<NamedReveal> VecNamedReveal;
typedef VecNamedReveal::iterator VecNamedRevealIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation(void) const { return &m_location; }

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	Coord3D m_location;					// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;	// slot 31, vtable+0x7C
};

extern TerrainLogic *TheTerrainLogic;				// 0x012EF4CC

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void undoShroudReveal(const Coord3D *pos, Real radius, UnsignedInt playerMask);	// retail 0x008F7730
};

extern PartitionManager *ThePartitionManager;			// 0x012ED5BC

// The mask resolver the ledger already pins on its ILT.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name, Bool *found);
};

extern BfmeScriptEngine_getPlayerMaskFromAsciiString *TheScriptEngine;	// 0x012F076C

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void undoNamedMapReveal(const AsciiString &revealName);

private:
	char m_slice_pad[0x175F8];				// retail this+0x00 .. +0x175F7, untouched
	VecNamedReveal m_namedReveals;				// this+0x175F8
};

void ScriptEngine::undoNamedMapReveal(const AsciiString& revealName)
{
	VecNamedRevealIt it;

	NamedReveal *reveal = 0;
	for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it) {
		if (it->m_revealName == revealName) {
			reveal = &(*it);
			break;
		}
	}

	if (!reveal) {
		return;
	}

	Waypoint *way = TheTerrainLogic->getWaypointByName(reveal->m_waypointName);
	if (!way) {
		return;
	}

	UnsignedShort playerMask = TheScriptEngine->getPlayerMaskFromAsciiString(reveal->m_playerName, 0);

	ThePartitionManager->undoShroudReveal(way->getLocation(), reveal->m_radiusToReveal, playerMask);
}
