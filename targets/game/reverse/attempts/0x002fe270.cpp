// ?doTeamGiveNearestTeamUpgrade@ScriptActions@@IAEXPAVParameter@@@Z
// partial score=0.96 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// TEAM_GIVE_NEAREST_TEAM_UPGRADE, retail RVA 0x002FE270.
// The action resolves the source team, then gives its upgrade to the nearest
// eligible member of another team owned by the source object's player.

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;
};

struct Coord3D : Coord3DBase
{
	Bool equals(const Coord3DBase &that) const;
	Real length() const;
	void sub(const Coord3DBase *that)
	{
		x -= that->x;
		y -= that->y;
		z -= that->z;
	}
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeStringLiteralBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringLiteralBase(const char *text);
	~BfmeStringLiteralBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	BfmeAsciiStringArg(const char *text)
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(text);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class Team;
class Object;
class SpecialPowerTemplate;

class UpgradeTemplate
{
public:
	unsigned char m_beforeMask[0x20];
	UnsignedInt m_upgradeMask;
};

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class BfmeScriptEngineVtbl_44
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

class BfmeSpecialPowerStoreView
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(BfmeAsciiStringArg name);
};

class BfmeTeamKindMemberCall
{
public:
	Object *findFirst(UnsignedInt kind);
};

class BfmeThingNDCall
{
public:
	UpgradeTemplate *bfmeFindND(const UnsignedInt *mask);
};

class BfmeTeamUpgradeCheckCall
{
public:
	Bool canReceive(UpgradeTemplate *upgrade);
};

class BfmeTeamNextCall
{
public:
	Team *nextInInstanceList();
};

class BfmeObjectKindCall
{
public:
	Bool isKindOf(UnsignedInt kind) const;
};

class BfmeObjectContainCall
{
public:
	void *unidentified_001BFE20() const;
};

class BfmeObjectPlayerCall
{
public:
	void *getControllingPlayer() const;
};

class BfmeObjectSpecialPowerCall
{
public:
	void doSpecialPowerAtObject(const SpecialPowerTemplate *power,
		Object *target, UnsignedInt options, Bool forced);
};

extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern void *TheUpgradeCenter;
extern void *TheSpecialPowerStore;

extern void j_00044e18(void);
extern void j_0001df16(void);
extern void j_00018449(void);
extern void j_00022a70(void);
extern void j_0003251f(void);
extern void j_0000d3b9(void);
extern void j_00020824(void);
extern void j_0000e02a(void);

static __forceinline Object *bfmeFirstKindMember(Team *team,
	UnsignedInt kind)
{
	typedef Object *(BfmeTeamKindMemberCall::*Function)(UnsignedInt);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00044e18;
	return (reinterpret_cast<BfmeTeamKindMemberCall *>(team)->*fn.member)(kind);
}

static __forceinline UpgradeTemplate *bfmeFindUpgrade(void *upgradeCenter,
	const UnsignedInt *mask)
{
	typedef UpgradeTemplate *(BfmeThingNDCall::*Function)(const UnsignedInt *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001df16;
	return (reinterpret_cast<BfmeThingNDCall *>(upgradeCenter)->*fn.member)(mask);
}

static __forceinline Bool bfmeTeamCanReceiveUpgrade(Team *team,
	UpgradeTemplate *upgrade)
{
	typedef Bool (BfmeTeamUpgradeCheckCall::*Function)(UpgradeTemplate *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00018449;
	return (reinterpret_cast<BfmeTeamUpgradeCheckCall *>(team)->*fn.member)(
		upgrade);
}

static __forceinline Team *bfmeNextTeam(Team *team)
{
	typedef Team *(BfmeTeamNextCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00022a70;
	return (reinterpret_cast<BfmeTeamNextCall *>(team)->*fn.member)();
}

static __forceinline Bool bfmeIsKindOf(const Object *object,
	UnsignedInt kind)
{
	typedef Bool (BfmeObjectKindCall::*Function)(UnsignedInt) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<const BfmeObjectKindCall *>(object)->*fn.member)(
		kind);
}

static __forceinline void *bfmeContainInterface(const Object *object)
{
	typedef void *(BfmeObjectContainCall::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000d3b9;
	return (reinterpret_cast<const BfmeObjectContainCall *>(object)->*fn.member)();
}

static __forceinline void *bfmeControllingPlayer(const Object *object)
{
	typedef void *(BfmeObjectPlayerCall::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020824;
	return (reinterpret_cast<const BfmeObjectPlayerCall *>(object)->*fn.member)();
}

static __forceinline void bfmeDoSpecialPower(Object *object,
	const SpecialPowerTemplate *power, Object *target, UnsignedInt options,
	Bool forced)
{
	typedef void (BfmeObjectSpecialPowerCall::*Function)(
		const SpecialPowerTemplate *, Object *, UnsignedInt, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000e02a;
	(reinterpret_cast<BfmeObjectSpecialPowerCall *>(object)->*fn.member)(
		power, target, options, forced);
}

#define BFME_SLOT(N) virtual Int bfmeSlot##N() = 0

class BfmeUpgradeInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41);
	virtual Bool hasUpgrade(UnsignedInt mask) = 0;
	BFME_SLOT(43); BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46);
	BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50);
	BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58);
	BFME_SLOT(59); BFME_SLOT(60);
	virtual Object *getTarget() = 0;
};

#undef BFME_SLOT

class BfmeObjectFields
{
public:
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
};

class BfmePlayerTeamNode
{
public:
	BfmePlayerTeamNode *m_next;
	BfmePlayerTeamNode *m_previous;
	class TeamPrototype *m_teamPrototype;
};

class BfmePlayerTeamFields
{
public:
	unsigned char m_beforeTeams[0x288];
	BfmePlayerTeamNode *m_playerTeams;
};

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

class TeamPrototype
{
public:
	unsigned char m_beforeInstances[0x274];
	Team *m_teamInstanceList;
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *current) : m_current(current) { }

	bool done() const { return m_current == 0; }
	Team *current() const { return m_current; }

	void advance()
	{
		if (m_current)
			m_current = bfmeNextTeam(m_current);
	}

private:
	Team *m_current;
};

template<class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *current, GetNextFunc getNext)
		: m_current(current), m_getNext(getNext) { }

	void advance()
	{
		m_current = (m_current->*m_getNext)();
	}

	bool done() const { return m_current == 0; }
	ObjectType *current() const { return m_current; }

private:
	ObjectType *m_current;
	GetNextFunc m_getNext;
};

static __forceinline Object *bfmeNextTeamMember(Object *object)
{
	typedef Object *(Object::*Function)() const;
	Function next = Object::dlink_next_TeamMemberList;
	return (object->*next)();
}

static __forceinline Bool bfmeHasUpgrade(void *interfaceObject,
	UnsignedInt mask)
{
	return ((BfmeUpgradeInterface *)interfaceObject)->hasUpgrade(mask);
}

static __forceinline Object *bfmeInterfaceTarget(void *interfaceObject)
{
	return ((BfmeUpgradeInterface *)interfaceObject)->getTarget();
}

class ScriptActions
{
protected:
	void doTeamGiveNearestTeamUpgrade(Parameter *sourceTeam);
};

void ScriptActions::doTeamGiveNearestTeamUpgrade(Parameter *sourceTeam)
{
	Team *source = TheScriptEngine->getTeamNamed(sourceTeam->m_string, false);
	if (!source)
		return;

	const SpecialPowerTemplate *power =
		((BfmeSpecialPowerStoreView *)TheSpecialPowerStore)
			->findSpecialPowerTemplate((const char *)0x01083C00);
	if (!power)
		return;

	Object *sourceObject = bfmeFirstKindMember(source, 0x34);
	if (!sourceObject)
		return;

	UpgradeTemplate *upgrade = bfmeFindUpgrade(TheUpgradeCenter,
		(const UnsignedInt *)((const char *)sourceObject + 0x224));
	if (!upgrade)
		return;

	void *player = bfmeControllingPlayer(sourceObject);
	if (!player)
		return;

	Coord3D sourcePosition;
	sourcePosition.z = ((BfmeObjectFields *)sourceObject)->m_position.z;
	sourcePosition.y = ((BfmeObjectFields *)sourceObject)->m_position.y;
	sourcePosition.x = ((BfmeObjectFields *)sourceObject)->m_position.x;
	Object *bestTarget[1];
	bestTarget[0] = 0;
	Real bestDistance;
	BfmePlayerTeamNode *node =
		((BfmePlayerTeamFields *)player)->m_playerTeams->m_next;

	while (node != ((BfmePlayerTeamFields *)player)->m_playerTeams)
	{
		BfmeTeamInstanceIterator teams(
			node->m_teamPrototype->m_teamInstanceList);
		for (; !teams.done(); teams.advance())
		{
			Team *team = teams.current();
			if (team != source && bfmeTeamCanReceiveUpgrade(team, upgrade))
			{
				BfmeDlinkIterator<Object> members(team->m_head,
					Object::dlink_next_TeamMemberList);
				for (; !members.done(); members.advance())
				{
					Object *member = members.current();
					if (!bfmeIsKindOf(member, 0x6c))
						continue;

					void *upgradeInterface = bfmeContainInterface(member);
					if (!upgradeInterface || bfmeHasUpgrade(upgradeInterface,
						upgrade->m_upgradeMask))
						continue;

					Coord3D memberPosition;
					Coord3D distance;
					memberPosition.x =
						((BfmeObjectFields *)member)->m_position.x;
					memberPosition.y =
						((BfmeObjectFields *)member)->m_position.y;
					memberPosition.z =
						((BfmeObjectFields *)member)->m_position.z;
					(void)distance.equals(sourcePosition);
					distance.sub(&memberPosition);
					Real distanceValue = distance.length();
					Object *target = bfmeInterfaceTarget(upgradeInterface);
					if (!target)
						continue;
					if (!bestTarget[0])
					{
						bestTarget[0] = target;
						bestDistance = distanceValue;
					}
					else if (distanceValue < bestDistance)
					{
						bestTarget[0] = target;
						bestDistance = distanceValue;
					}
				}
			}
		}
		node = node->m_next;
	}

	if (bestTarget[0])
		bfmeDoSpecialPower(sourceObject, power, bestTarget[0],
			0x40000, false);
}
