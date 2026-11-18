// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include
// stlport
// readable body of ?doUnitGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// ScriptActions::doUnitGarrisonNearestBuilding, retail RVA 0x00302630, 451
// bytes (ret 4 at +0x1C0). executeAction's NAMED_GARRISON_NEAREST_BUILDING
// case reaches it; the Zero Hour twin (ScriptActions.cpp) has the same
// unit/AI lookup, the sorted near-to-far REALLY_FAR query and the
// getContain()/getPlayerWhoEntered()/aiEnter(CMD_FROM_SCRIPT) loop.
// BFME differs: two filters (structure-type KindOf bits 7 and 117, then the
// same-map filter of retail table 0x01085DD0) built as temporaries of the
// query expression -- retail destroys both right after bfmeForwardWideC --
// no money-hacker branch, no chooseLocomotorSet, and an extra test of the
// contain's slot-0 data (+0xB6 byte) before the player check.
// The partition types repeat the layout the matched
// StealthDetectorUpdate/BroadcastStealthUpdate units use.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
#include "Lib/Coord3D.h"

#include "../../../Include/Common/ScalarTypes.h"


typedef unsigned short PlayerMaskType;


class AsciiString;
class Object;

#include "../command_source_type.h"

template <int NUMBITS> class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags() { }
	BitFlags(_dummy_kInit, Int idx1, Int idx2)
	{
		m_bits._Unchecked_set(idx1);
		m_bits._Unchecked_set(idx2);
	}
private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class Player
{
public:
	PlayerMaskType getPlayerMask() const { return (PlayerMaskType)(1 << m_playerIndex); }
	unsigned char m_unmodelled_00[0x24];
	Int m_playerIndex;
};

// Slot-0 data of the contain module: only its +0xB6 byte is read here.
class Rva00302630ContainData { public: unsigned char m_unmodelled_00[0xB6]; Bool m_atB6; };

class ContainModuleInterface
{
public:
	virtual const Rva00302630ContainData *rva00302630Slot00();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual PlayerMaskType getPlayerWhoEntered() const;
};

class AICommandInterface
{
public:
	void aiEnter(Object *obj, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_00[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_pos; }

	unsigned char m_unmodelled_00[0x38];
	Coord3D m_pos;
	unsigned char m_unmodelled_44[0x1FC - 0x44];
	ContainModuleInterface *m_contain;		// +0x1FC
	unsigned char m_unmodelled_200[4];
	AIUpdateInterface *m_ai;				// +0x204
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);
	Object *m_object;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const BitFlags<192> &, const BitFlags<192> &);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);
	BitFlags<192> m_yes;
	BitFlags<192> m_no;
};

struct Rva0025ED50Entry { Object *object; UnsignedInt unknown04; };

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0025ED50ResultData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};
// Retail 0x012ED5B8: use the existing data owner; retain the local pointee view.
extern class PartitionManager *ThePartitionManager;

class ScriptEngine
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60(); virtual void v64();
	virtual Object *getUnitNamed(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doUnitGarrisonNearestBuilding(const AsciiString &unitName);
};

static const Real REALLY_FAR = 1000000.0f;

// ?doUnitGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doUnitGarrisonNearestBuilding(const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai)
		return;

	BfmeWideResult iter = reinterpret_cast<BfmeWideForwardC *>(ThePartitionManager)->bfmeForwardWideC(
		(int)theUnit->getPosition(), *(const int *)&REALLY_FAR, 2,
		(int)PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 7, 117), KINDOFMASK_NONE).link(
			&Rva0025ED50ObjectFilter(theUnit)),
		1);

	while (Object *theBuilding = iter.next())
	{
		ContainModuleInterface *contain = theBuilding->getContain();
		if (!contain)
			continue;
		const Rva00302630ContainData *data = contain->rva00302630Slot00();
		if (data && !contain->rva00302630Slot00()->m_atB6)
			continue;
		PlayerMaskType player = theBuilding->getContain()->getPlayerWhoEntered();
		if (player != 0 && player != theUnit->getControllingPlayer()->getPlayerMask())
			continue;

		ai->m_commands.aiEnter(theBuilding, CMD_FROM_SCRIPT);
		return;
	}
}
