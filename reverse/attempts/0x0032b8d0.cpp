// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// BFME's ScriptConditions predicate at retail RVA 0x0032B8D0 (471 bytes).
// The named source dispatcher selects SKIRMISH_SPECIAL_POWER_READY; this TU
// keeps the BFME Parameter cache, player/team intrusive lists, and retail ILT
// routes local to the recovered body.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMaskType;

class GameLogic;
class SpecialPowerStore;
class ScriptEngine;
class PlayerList;
class Player;
class Object;
class SpecialPowerTemplate;

class Parameter
{
};

class ScriptConditions
{
protected:
	Bool evaluateSkirmishSpecialPowerIsReady(Parameter *, Parameter *);
};

// Retail's by-value special-power lookup uses the out-of-line narrow string
// copy/release bodies through this canonical BFME view.
class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class BfmeSpecialPowerStoreView
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(BfmeAsciiStringArg name);
};

class BfmeParameterView
{
public:
	const AsciiString &getString(void) const { return m_string; }

	unsigned char m_beforeString[0x10];
	AsciiString m_string;
	unsigned char m_beforeCachedValue[0x0c];
	Int m_cachedValue;
};

class BfmeGameLogicView
{
public:
	unsigned char m_beforeFrame[0x3c];
	Int m_frame;
};

class BfmePlayerTeamNode;
class BfmeTeamPrototype;
class BfmeTeam;
class BfmeObject;

class BfmePlayerView
{
public:
	unsigned char m_beforeTeams[0x288];
	BfmePlayerTeamNode *m_teams;
};

class BfmePlayerTeamNode
{
public:
	BfmePlayerTeamNode *m_next;
	unsigned char m_beforePrototype[4];
	BfmeTeamPrototype *m_prototype;
};

class BfmeTeamPrototype
{
public:
	unsigned char m_beforeInstances[0x274];
	BfmeTeam *m_instances;
};

class BfmeTeam
{
public:
	unsigned char m_beforeMembers[0x0c];
	BfmeObject *m_head;
};

class BfmeObject
{
};

class BfmeObjectFields
{
public:
	unsigned char m_beforeStatus[0x90];
	UnsignedInt m_status[3];
	unsigned char m_beforeFlags[0x1a4 - 0x9c];
	Int m_flags;
};

class BfmeSpecialPowerModuleView
{
public:
	virtual void slot00(void) = 0;
	virtual Bool isReady(void) const = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual UnsignedInt getReadyFrame(void) const = 0;
};

class BfmeObjectSpecialPowerCall
{
public:
	BfmeSpecialPowerModuleView *getSpecialPowerModule(
		const SpecialPowerTemplate *power);
};

class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087(Parameter *parameter);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

extern GameLogic *TheGameLogic;
extern SpecialPowerStore *TheSpecialPowerStore;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeP1087 *g_bfmeP1087;

extern void j_00001140(void);
extern void j_0002e4a1(void);
extern void j_000401bf(void);
extern void j_00022a70(void);

static __forceinline BfmeSpecialPowerModuleView *bfmeGetSpecialPowerModule(
	BfmeObject *object, const SpecialPowerTemplate *power)
{
	typedef BfmeSpecialPowerModuleView *(
		BfmeObjectSpecialPowerCall::*Function)(const SpecialPowerTemplate *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000401bf;
	return (reinterpret_cast<BfmeObjectSpecialPowerCall *>(object)->*
		fn.member)(power);
}

static __forceinline Bool bfmeCanUseSpecialPower(
	BfmeSpecialPowerStoreView *store, BfmeObject *object,
	const SpecialPowerTemplate *power)
{
	typedef Bool (BfmeSpecialPowerStoreView::*Function)(
		Object *, const SpecialPowerTemplate *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002e4a1;
	return (reinterpret_cast<BfmeSpecialPowerStoreView *>(store)->*
		fn.member)(reinterpret_cast<Object *>(object), power);
}

static __forceinline BfmeTeam *bfmeNextTeam(BfmeTeam *team)
{
	typedef BfmeTeam *(BfmeTeam::*Function)(void);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00022a70;
	return (reinterpret_cast<BfmeTeam *>(team)->*fn.member)();
}

typedef BfmeObject *(__fastcall *BfmeDlinkNext)(BfmeObject *);
struct BfmeDlinkPmf
{
	BfmeDlinkNext pfn;
	Int delta;
	Int vbindex;
};

class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(BfmeObject *current, BfmeDlinkPmf next)
		: m_current(current), m_next(next) {}

	void advance(void)
	{
		BfmeObject *object = m_current;
		Int vbindex = m_next.vbindex;
		char *vbptr = *(char **)((char *)object + 0x68);
		char *adjusted = (char *)object + 0x68;
		adjusted += *(Int *)(vbptr + vbindex);
		adjusted += m_next.delta;
		m_current = m_next.pfn((BfmeObject *)adjusted);
	}

	Bool done(void) const { return m_current == 0; }
	BfmeObject *cur(void) const { return m_current; }

private:
	BfmeObject *m_current;
	Int m_padding;
	BfmeDlinkPmf m_next;
	Int m_tailPadding;
};

// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateSkirmishSpecialPowerIsReady(
	Parameter *pSkirmishPlayerParm, Parameter *pPower)
{
	BfmeParameterView *powerParameter =
		reinterpret_cast<BfmeParameterView *>(pPower);
	Int cachedFrame = powerParameter->m_cachedValue;
	if (cachedFrame == -1)
		return false;

	if (cachedFrame > 0 && (UnsignedInt)cachedFrame >
		(UnsignedInt)reinterpret_cast<BfmeGameLogicView *>(TheGameLogic)->m_frame)
		return false;

	BfmeGameLogicView *logic =
		reinterpret_cast<BfmeGameLogicView *>(TheGameLogic);
	UnsignedInt nextFrame = logic->m_frame + 50;
	const SpecialPowerTemplate *power =
		((BfmeSpecialPowerStoreView *)TheSpecialPowerStore)
			->findSpecialPowerTemplate(powerParameter->getString());
	if (!power)
	{
		powerParameter->m_cachedValue = -1;
		return false;
	}

	PlayerMaskType mask = g_bfmeP1087->bfmeNext1087(pSkirmishPlayerParm);
	if (!mask)
		return false;

	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (!player)
		return false;

	BfmePlayerView *bfmePlayer = reinterpret_cast<BfmePlayerView *>(player);
	BfmePlayerTeamNode *teamIt = bfmePlayer->m_teams->m_next;
	while (teamIt != bfmePlayer->m_teams)
	{
		BfmeTeamPrototype *prototype = teamIt->m_prototype;
		BfmeTeam *team = prototype->m_instances;
		while (team)
		{
			BfmeDlinkPmf pmf = {
				(BfmeDlinkNext)j_00001140, -100, 0};
			BfmeDlinkIterator objects(team->m_head, pmf);
			for (; !objects.done(); objects.advance())
			{
				BfmeObject *object = objects.cur();
				BfmeObjectFields *fields =
					reinterpret_cast<BfmeObjectFields *>(object);
				if (fields->m_status[0] & 4 || fields->m_flags)
					continue;

				BfmeSpecialPowerModuleView *module =
					bfmeGetSpecialPowerModule(object, power);
				if (!module || !bfmeCanUseSpecialPower(
					(BfmeSpecialPowerStoreView *)TheSpecialPowerStore,
					object, power))
					continue;
				if (module->isReady())
					return true;

				UnsignedInt readyFrame = module->getReadyFrame();
				if (readyFrame < nextFrame)
					nextFrame = readyFrame;
			}
			team = bfmeNextTeam(team);
		}
		teamIt = teamIt->m_next;
	}

	powerParameter->m_cachedValue = nextFrame;
	return false;
}
