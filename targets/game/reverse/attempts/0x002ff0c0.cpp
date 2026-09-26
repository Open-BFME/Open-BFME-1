// ?doDeploySiegeOnWaypoint@ScriptActions@@IAEXPAVParameter@@00@Z
// partial score=0.78 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// ScriptActions::doDeploySiegeOnWaypoint, retail 0x002FF0C0, 704 bytes (ret 0Ch
// at +0x2BD, int3 padding from +0x2C0). executeAction's jump-table entry 466
// passes its three Parameters here through ILT 0x00012085, and
// m_actionTemplates[466] is DEPLOY_SIEGE_ON_WAYPOINT.
//
// For every object near the waypoint that owns a SiegeDockingBehavior, walk the
// team (one shared member iterator, as the retail loop never restarts it) and
// fire each ready siege member's special power 46 at that object while the dock
// accepts the member's ID.

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <bitset>
#include <vector>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectID { INVALID_ID = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum KindOfType { KINDOF_INVALID = -1 };
enum CommandSourceType { CMD_FROM_SCRIPT = 2 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };

// Retail tests KindOf word 2 bit 28 on the template and asks for power 46;
// neither enum value is named here.
const KindOfType Rva002FF0C0SiegeKindOf = (KindOfType)(64 + 28);
const SpecialPowerType Rva002FF0C0SiegePower = (SpecialPowerType)46;
// A member whose status bit 63 (word 1 bit 31 of m_status) is set is skipped.
const ObjectStatusTypes Rva002FF0C0SkipStatus = (ObjectStatusTypes)63;
// The partition filter's must-be-set KindOf bit (word 1 bit 27).
const Int Rva002FF0C0FilterKindOf = 32 + 27;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	Real getReal(void) const { return m_real; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	Real m_real;						// this+0x0C
	AsciiString m_string;					// this+0x10
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(UnsignedInt)kind >> 5]
			& (1u << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_beforeKindOf[0xc8 - 8];
	UnsignedInt m_kindOf[6];
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate == 0)
		{
			thingTemplate = 0;
		}
		else if (thingTemplate->m_nextOverride != 0)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(
				thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate->isKindOf(kind);
	}

protected:
	virtual ~Thing();
	const ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx)
	{
		m_bits.set(idx);
	}

	Bool test(Int idx) const { return m_bits.test(idx); }
};

typedef BitFlags<86> ObjectStatusMaskType;

class SpecialPowerModuleInterface
{
public:
	virtual Bool isModuleForPower(const void *) const = 0;
	virtual Bool isReady() const = 0;
	virtual void slot02() const = 0;
	virtual void slot03() const = 0;
	virtual void slot04() const = 0;
	virtual void slot05() const = 0;
	virtual void slot06() const = 0;
	virtual void slot07() const = 0;
	virtual void slot08() const = 0;
	virtual void slot09() const = 0;
	virtual void slot10() const = 0;
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions) = 0;
};

class Module
{
public:
	virtual void moduleSlot();
	unsigned char m_moduleBody[0x1c];
};

// The interface SiegeDockingBehavior carries at +0x20; slot 3 takes the
// member's ObjectID and gates the special power.
class Rva002FF0C0DockInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual Bool slot03(ObjectID id) = 0;
};

class Rva002FF0C0SiegeDocking : public Module, public Rva002FF0C0DockInterface
{
};

// The BFME Object skeleton from reference/shims/objectdlink: vptr at +0, the
// DLINK base at +4, the vbptr-carrying base at +0x68.
class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	ObjectID getID() const { return m_id; }
	Bool testStatus(ObjectStatusTypes bit) const { return m_status.test(bit); }
	Module *findModule(NameKeyType key) const;
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;

	unsigned char m_before74[4];
	ObjectID m_id;						// Object+0x74
	unsigned char m_before90[0x18];
	ObjectStatusMaskType m_status;				// Object+0x90
	unsigned char m_tail[0x20];
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_unmodelled0;
	void *m_unmodelled1;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0xc];
	Coord3D m_location;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0;
	virtual Team *getTeamNamed(AsciiString name, Bool playerOwned) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

// BFME's KindOfMaskType is 192 bits; KINDOFMASK_NONE is pinned at VA 0x012ED8B8.
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

// BFME filters: virtual destructor, allow, getPlayerMask, then next at +4.
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

// vtable 0x01083B70; out-of-line ctor 0x000C3DD0 through ILT 0x000382FD.
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

struct Rva002FF0C0Entry
{
	Object *object;
	UnsignedInt word04;
};

struct Rva002FF0C0ResultData
{
	std::vector<Rva002FF0C0Entry> entries;
	Rva002FF0C0Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva002FF0C0ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

// ThePartitionManager's iterate forwarder, 0x009F2960 (ledger spelling).
class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

class ScriptActions
{
protected:
	void doDeploySiegeOnWaypoint(Parameter *pTeamParm, Parameter *pWaypointParm, Parameter *pRadiusParm);
};

// ?doDeploySiegeOnWaypoint@ScriptActions@@IAEXPAVParameter@@00@Z
void ScriptActions::doDeploySiegeOnWaypoint(Parameter *pTeamParm, Parameter *pWaypointParm, Parameter *pRadiusParm)
{
	Team *team = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!team)
		return;

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	if (iter.done())
		return;

	Waypoint *way = TheTerrainLogic->getWaypointByName(pWaypointParm->getString());
	if (!way)
		return;

	Coord3D pos;
	pos.set(way->getLocation());
	Real radius = pRadiusParm->getReal();

	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(int)&pos, *(int *)&radius, 0,
		(int)PartitionFilterAcceptByKindOf(
			KindOfMaskType(KindOfMaskType::kInit, Rva002FF0C0FilterKindOf),
			KINDOFMASK_NONE)
			.link(&Rva0025ED50RootFilter()),
		1);

	Object *other;
	while (result.next(other))
	{
		static NameKeyType siegeDockKey = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		Rva002FF0C0SiegeDocking *dock = (Rva002FF0C0SiegeDocking *)
			other->findModule(siegeDockKey);
		if (!dock)
			continue;

		for (; !iter.done(); iter.advance())
		{
			Object *member = iter.cur();
			if (!member)
				continue;
			if (!((Thing *)member)->isKindOf(Rva002FF0C0SiegeKindOf))
				continue;

			SpecialPowerModuleInterface *power =
				member->findSpecialPowerModuleInterface(Rva002FF0C0SiegePower);
			if (!power)
				continue;
			if (!power->isReady())
				continue;
			if (member->testStatus(Rva002FF0C0SkipStatus))
				continue;
			if (!dock->slot03(member->getID()))
				break;

			power->doSpecialPowerAtObject(other, CMD_FROM_SCRIPT);
		}
	}
}
