// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_GIVE_TEAM_UPGRADE at retail RVA 0x002F8880.
//
// The source team supplies the first member of kind 0x34.  Its upgrade mask
// is resolved through the BFME ThingND list, the destination team is checked
// for an eligible member, and the GiveUpgrade special power is fired from
// the source object at the destination team's first member.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString
{
private:
	char *m_text;
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

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Team;
class Object;
class SpecialPowerTemplate;

// BFME's ScriptEngine puts getTeamNamed at vtable slot 17 and passes the
// name by value, with the exact-match flag as its second argument.
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

// These three small methods have no safe canonical identity yet.  Their
// retail thunks are used as the function values, while the local PMF types
// preserve the MSVC thiscall argument order.
class BfmeTeamKindMemberCall
{
public:
	Object *findFirst(UnsignedInt kind);
};

class BfmeThingNDCall
{
public:
	void *bfmeFindND(const UnsignedInt *mask);
};

class BfmeTeamUpgradeCheckCall
{
public:
	Bool canReceive(void *upgrade);
};

class Object
{
public:
	void doSpecialPowerAtObject(const SpecialPowerTemplate *specialPower,
		Object *object, UnsignedInt options, Bool forced);
};

class TeamFirstMemberCall
{
public:
	Object *getFirstItemIn_TeamMemberList() const;
};

extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern void *TheUpgradeCenter;
extern void *TheSpecialPowerStore;

extern void j_00044e18();
extern void j_0001df16();
extern void j_00018449();
extern void j_0003fd41();

static __forceinline Object *bfmeFirstKindMember(Team *team,
	UnsignedInt kind)
{
	typedef Object *(BfmeTeamKindMemberCall::*Function)(UnsignedInt);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00044e18;
	return (reinterpret_cast<BfmeTeamKindMemberCall *>(team)->*fn.member)(kind);
}

static __forceinline void *bfmeFindUpgrade(void *upgradeCenter,
	const UnsignedInt *mask)
{
	typedef void *(BfmeThingNDCall::*Function)(const UnsignedInt *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001df16;
	return (reinterpret_cast<BfmeThingNDCall *>(upgradeCenter)->*fn.member)(mask);
}

static __forceinline Bool bfmeTeamCanReceiveUpgrade(Team *team,
	void *upgrade)
{
	typedef Bool (BfmeTeamUpgradeCheckCall::*Function)(void *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00018449;
	return (reinterpret_cast<BfmeTeamUpgradeCheckCall *>(team)->*fn.member)(
		upgrade);
}

static __forceinline Object *bfmeFirstTeamMember(const Team *team)
{
	typedef Object *(TeamFirstMemberCall::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003fd41;
	return (reinterpret_cast<const TeamFirstMemberCall *>(team)->*fn.member)();
}

class ScriptActions
{
protected:
	void doTeamGiveTeamUpgrade(Parameter *sourceTeam, Parameter *targetTeam);
};

void ScriptActions::doTeamGiveTeamUpgrade(Parameter *sourceTeam,
	Parameter *targetTeam)
{
	Team *source = TheScriptEngine->getTeamNamed(sourceTeam->m_string, false);
	Team *target = TheScriptEngine->getTeamNamed(targetTeam->m_string, false);
	if (!source || !target)
		return;

	Object *sourceObject = bfmeFirstKindMember(source, 0x34);
	if (!sourceObject)
		return;

	void *upgrade = bfmeFindUpgrade(TheUpgradeCenter,
		(const UnsignedInt *)((const char *)sourceObject + 0x224));
	if (!upgrade || !bfmeTeamCanReceiveUpgrade(target, upgrade))
		return;

	const SpecialPowerTemplate *power =
		((BfmeSpecialPowerStoreView *)TheSpecialPowerStore)
			->findSpecialPowerTemplate((const char *)0x01083C00);
	if (!power)
		return;

	// Keep the first-member call in the argument expression.  Retail leaves
	// the two trailing command arguments on the stack while it evaluates it.
	sourceObject->doSpecialPowerAtObject(power,
		bfmeFirstTeamMember(target), 0x40000, false);
}
