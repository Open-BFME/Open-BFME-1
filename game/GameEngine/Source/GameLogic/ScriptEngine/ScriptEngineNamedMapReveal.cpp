// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The four named-map-reveal entry points, which are one feature:
//
//   0x0034D200  doNamedMapReveal      226 bytes  reveal it
//   0x0034D320  undoNamedMapReveal    226 bytes  un-reveal it
//   0x0034D440  removeNamedMapReveal  217 bytes  drop the entry
//   0x0034EF80  createNamedMapReveal  379 bytes  add the entry
//
// All four scan the same 0x10-stride vector at ScriptEngine+0x175F8 for an
// entry whose name matches, using the same inlined AsciiString compare, and
// then diverge: two act on the shroud, one erases, one refuses a duplicate and
// pushes a new element. The scan is written once here instead of four times.
//
// NamedReveal's layout is the reason this merge is worth more than its line
// count. Three of the four files put the reveal radius at +0x08 and the player
// name at +0x0C -- the reference has them the other way round, and BFME
// reordered them. doNamedMapReveal proves it from the instruction operands: the
// two `lea`s off the element feed the player-mask lookup and the radius push
// respectively. removeNamedMapReveal still carried the reference's order,
// player name at +0x08 and radius at +0x0C, and byte-matched anyway because its
// body never reads either field -- it compares the name at +0x00 and erases the
// element. Nothing inside that file could have caught it. One declaration now
// states the order its siblings proved.
//
// AsciiString drifted the same way and for the same reason: removeNamedMapReveal
// declared the copy constructor out of line where the other three define it as
// an inline forwarder into StringBase, which is what puts the __$SEHRec$ store
// ahead of `mov ecx, esp` when a name is built by value in an outgoing argument
// slot. That file never builds one, so its spelling was unconstrained.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// Delegating, and visibly so: it is what puts the __$SEHRec$ store ahead of
	// `mov ecx, esp` when the by-value name is built in the outgoing argument
	// slot for getWaypointByName.
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString();

	AsciiString &operator=(const AsciiString &that);

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
struct NamedReveal
{
	// Declared, so the whole element is one object to the unwinder: retail
	// carries a single state across the three strings, not one apiece.
	NamedReveal(void) {}

	AsciiString m_revealName;				// +0x00
	AsciiString m_waypointName;				// +0x04
	Real m_radiusToReveal;					// +0x08
	AsciiString m_playerName;				// +0x0C
};

typedef _STL::vector<NamedReveal> VecNamedReveal;
typedef VecNamedReveal::iterator VecNamedRevealIt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation(void) const { return &m_location; }

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	Coord3D m_location;					// this+0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void doShroudReveal(const Coord3D *pos, Real radius, UnsignedInt playerMask);	// retail 0x008F7680
	void undoShroudReveal(const Coord3D *pos, Real radius, UnsignedInt playerMask);	// retail 0x008F7730
};

// The shroud subsystem is a SEPARATE global from the partition manager in BFME:
// the engine-init tag block at 0x0038A1F0 stores 0x012ED5BC and then pushes the
// tag "TheShroudManager", while ThePartitionManager is constructed just before it
// at 0x012ED5B8.  These entry points reach the former.
extern PartitionManager *TheShroudManager;				///< retail 0x012ED5BC

// The mask resolver the ledger already pins on its ILT.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name, Bool *found);
};

extern BfmeScriptEngine_getPlayerMaskFromAsciiString *TheScriptEngine;	// 0x012F076C

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void doNamedMapReveal(const AsciiString &revealName);
	void undoNamedMapReveal(const AsciiString &revealName);
	void removeNamedMapReveal(const AsciiString &revealName);
	void createNamedMapReveal(const AsciiString &revealName, const AsciiString &waypointName,
														Real radiusToReveal, const AsciiString &playerName);

private:
	char m_slice_pad[0x175F8];				// retail this+0x00 .. +0x175F7, untouched
	VecNamedReveal m_namedReveals;				// this+0x175F8
};

void ScriptEngine::doNamedMapReveal(const AsciiString& revealName)
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

	TheShroudManager->doShroudReveal(way->getLocation(), reveal->m_radiusToReveal, playerMask);
}

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

	TheShroudManager->undoShroudReveal(way->getLocation(), reveal->m_radiusToReveal, playerMask);
}

void ScriptEngine::removeNamedMapReveal(const AsciiString& revealName)
{
	VecNamedRevealIt it;

	for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it) {
		if (it->m_revealName == revealName) {
			m_namedReveals.erase(it);
			return;
		}
	}
}

void ScriptEngine::createNamedMapReveal(const AsciiString& revealName, const AsciiString& waypointName, Real radiusToReveal, const AsciiString& playerName)
{
	VecNamedRevealIt it;

	// Will fail if there's already one in existence of the same name.
	for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it) {
		if (it->m_revealName == revealName) {
			return;
		}
	}

	NamedReveal reveal;
	reveal.m_playerName = playerName;
	reveal.m_radiusToReveal = radiusToReveal;
	reveal.m_revealName = revealName;
	reveal.m_waypointName = waypointName;

	m_namedReveals.push_back(reveal);
}
