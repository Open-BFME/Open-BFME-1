// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <utility>
#include "ascii_string.h"

// Object's Snapshot-table slot 1, retail 0x001CEE10 (336 bytes).
// Object's Snapshot table at +0x60 routes slot 1 here through ILT 0x0001D51B
// (targets/game/reverse/identity_evidence/001cee10-object-loadpostprocess.md).
// The body is the Zero Hour loadPostProcess twin, but retail's ILT hash window
// for that thunk rejects every ?loadPostProcess@Object spelling, so the method
// keeps its address until the real decorated name is found.
// The receiver is the Snapshot subobject, so the Object members below sit at
// their Object offsets and MSVC addresses them from this-0x60.  Beyond the
// Zero Hour contained-by fixup, BFME resolves the (index, name) pairs queued at
// +0x310 into m_triggerInfo through TerrainLogic slot 36, updates the weapon
// set and re-registers the object with the pathfinder.  Members and the
// TerrainLogic slot without witnessed names keep their offsets.

#include "../../../Include/Common/ScalarTypes.h"


typedef Int ObjectID;
#define NULL 0

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

// Inline first level of the override walk, as a free helper: a member would
// make cl emit its own friend_getFinalOverride COMDAT that is not retail's.
static __forceinline const Overridable *friendGetFinalOverride( const Overridable *o )
{
	if( o->m_nextOverride )
		return o->m_nextOverride->getFinalOverride();
	return o;
}

class ThingTemplate : public Overridable
{
public:
	// Kind-of flags are three words at +0xc8.
	UnsignedInt getKindOfWord1() const { return m_kindof[1]; }

private:
	unsigned char m_pad[0xc0];
	UnsignedInt m_kindof[3];
};

enum { KINDOF_WORD1_BIT27_MASK = 0x08000000 };

class Object;
class PolygonTrigger;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	void Rva003E4190(Object *obj);
	void addObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad[0xc];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b();
	virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual PolygonTrigger *slot24(AsciiString name);
};
extern TerrainLogic *TheTerrainLogic;

class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);
};

class Thing
{
public:
	virtual ~Thing();

protected:
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x58];
};

class Snapshot
{
protected:
	virtual ~Snapshot();
	virtual void rva001CEE10() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
struct TriggerInfo
{
	PolygonTrigger *pTrigger;
	unsigned char entered;
	unsigned char exited;
	unsigned char isInside;
	unsigned char padding;
};

typedef std::pair<Int, AsciiString> TriggerNameEntry;

class Object : public Thing, public Snapshot
{
public:
	void rva001CE530();
	Bool getFlag3A8() const { return m_flag3A8; }
	Int getValue314() const { return m_value314; }

protected:
	virtual void rva001CEE10();

private:
	unsigned char m_pad64[0x30];
	UnsignedInt m_status94;
	unsigned char m_pad98[0x17c];
	Object *m_containedBy;
	ObjectID m_xferContainedByID;
	unsigned char m_pad21c[0x48];
	WeaponSet m_weaponSet;
	unsigned char m_pad268[0x70];
	TriggerInfo m_triggerInfo[7];
	std::list<TriggerNameEntry> m_list310;
	Int m_value314;
	unsigned char m_pad318[0x90];
	Bool m_flag3A8;
};

// ?rva001CEE10@Object@@MAEXXZ
void Object::rva001CEE10()
{
	if (m_xferContainedByID != 0)
		m_containedBy = TheGameLogic->findObjectByID(m_xferContainedByID);
	else
		m_containedBy = NULL;

	if (m_status94 & 0x40000)
		rva001CE530();

	std::list<TriggerNameEntry>::iterator it = m_list310.begin();
	while (it != m_list310.end())
	{
		Int index = it->first;
		AsciiString name = it->second;
		m_triggerInfo[index].pTrigger = TheTerrainLogic->slot24(name);
		it = m_list310.erase(it);
	}

	m_weaponSet.updateWeaponSet(this);
	Object *obj = this;
	if (!obj->getFlag3A8() && obj->getValue314() != 1)
		TheAI->pathfinder()->Rva003E4190(obj);

	const ThingTemplate *tmpl = m_template == NULL ? NULL :
		static_cast<const ThingTemplate *>(friendGetFinalOverride( m_template ));
	if ((tmpl->getKindOfWord1() & KINDOF_WORD1_BIT27_MASK) == 0)
		TheAI->pathfinder()->addObjectToPathfindMap(this);
}
