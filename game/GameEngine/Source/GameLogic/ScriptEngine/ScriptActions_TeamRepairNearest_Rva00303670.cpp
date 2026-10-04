// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// stlport
// ScriptActions arm for TEAM_REPAIR_NEAREST (action template 479), retail RVA 0x00303670 (534 B).

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;

// Incremental-link thunks the retail body calls through directly.
extern void j_00001140(void);
extern void j_000022bb(void);
extern void j_0002369b(void);
extern void j_0002990b(void);
extern void j_00029c08(void);

class Object;
class Player;
class Team;
class PartitionManager;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	__declspec(nothrow) BitFlags(BogusInitType, Int bit)
	{
		m_bits._Unchecked_set(static_cast<size_t>(bit));
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class ScriptEngine
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class Overridable
{
public:
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad_008[0xc8 - 8];
	unsigned int m_flagsC8;
};

// Retail 0x000022BB is an incremental-link thunk for
// Overridable::getFinalOverride() const; call it through the same thiscall
// shape the thunk preserves, with no linker alias involved.
static __forceinline const Overridable *finalOverride(const Overridable *overridable)
{
	typedef const Overridable *(Overridable::*Fn)() const;
	union
	{
		void (*fn)();
		Fn call;
	} u = { j_000022bb };

	return (overridable->*u.call)();
}

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)finalOverride(value->m_nextOverride);
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	ThingTemplate *m_template;
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0() = 0;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
};

class BfmeAIUpdateView
{
public:
	unsigned char m_pad_00[0x20];
	AICommandInterface m_command;
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template == 0 ? m_template : m_template->m_nextOverride ?
			(const ThingTemplate *)finalOverride(m_template->m_nextOverride) : m_template;
	}

	unsigned char m_pad_70[0x194];
	BfmeAIUpdateView *m_ai;
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class Team
{
public:
	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		typedef Object *(BfmeObjectDlinkBase::*Fn)() const;
		union
		{
			void (*fn)();
			Fn call;
		} next = { j_00001140 };

		return BfmeDlinkIterator<Object>(m_head, next.call);
	}

private:
	unsigned char m_pad_00[0x0c];
	Object *m_head;
};

class RvaBodySlotView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Real RvaBodySlot05() = 0;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player,
		unsigned int affiliation, Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) { }

	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
	unsigned int m_affiliation;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) { }
	virtual Bool allow(Object *object);

private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

static __forceinline PartitionFilter *filterAddress(
	const PartitionFilter &filter)
{
	return (PartitionFilter *)&filter;
}

struct ResultEntry
{
	Object *object;
	unsigned int distanceBits;
};

struct ResultData
{
	std::vector<ResultEntry> entries;
	ResultEntry *current;
	int references;
};

struct BfmeWideResult
{
	ResultData *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult()
	{
		if (--m_value->references == 0)
			delete m_value;
	}

	Object *next()
	{
		if (m_value->current == m_value->entries.end())
			return 0;
		return (m_value->current++)->object;
	}
};

class BfmeWideResultSource
{
public:
	BfmeWideResult bfmeMakeWideResult(int a, int b, int c, int d, int e, int f);
};

class BfmeWideForwardC
{
	unsigned char m_pad_00[0x0c];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class BfmeWideForwardCView
{
};

extern ScriptEngine *TheScriptEngine;
extern PartitionManager *ThePartitionManager;
extern Real g_bfmeDefaultBU;



class ScriptActions
{
protected:
	void Rva00303670(const AsciiString &teamName, Real radius);
};

// ?Rva00303670@ScriptActions@@IAEXABVAsciiString@@M@Z
void ScriptActions::Rva00303670(const AsciiString &teamName, Real radius)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D teamPosition;
	int radiusBits = *(int *)&radius;
	typedef Coord3D *(Team::*EstimatePosFn)(Coord3D *) const;
	union
	{
		void (*fn)();
		EstimatePosFn call;
	} estimatePos = { j_0002990b };
	typedef Player *(Team::*ControllingPlayerFn)() const;
	union
	{
		void (*fn)();
		ControllingPlayerFn call;
	} controllingPlayer = { j_0002369b };
	BfmeWideResult result = ((BfmeWideForwardC *)ThePartitionManager)->
		bfmeForwardWideC((int)(team->*estimatePos.call)(&teamPosition),
			radiusBits, 0,
			(int)PartitionFilterPlayerAffiliation(
				(team->*controllingPlayer.call)(), 2, true).link(
					filterAddress(PartitionFilterAcceptByKindOf(
						KindOfMaskType(KindOfMaskType::kInit, 7),
						KINDOFMASK_NONE))), 1);

	while (Object *candidate = result.next())
	{
		RvaBodySlotView *body = (RvaBodySlotView *)
			*(void **)((char *)candidate + 0x200);
		if (body && body->RvaBodySlot05() < g_bfmeDefaultBU)
		{
			for (BfmeDlinkIterator<Object> members = team->iterate_TeamMemberList();
				!members.done(); members.advance())
			{
				Object *member = members.cur();
				if (!member)
					continue;
				const ThingTemplate *thing = member->m_template;
				if (thing && thing->m_nextOverride)
					thing = (const ThingTemplate *)finalOverride(thing->m_nextOverride);
				if ((thing->m_flagsC8 & 0x4000) != 0)
				{
					BfmeAIUpdateView *ai = member->m_ai;
					if (ai)
					{
						typedef void (AICommandInterface::*RepairFn)(Object *,
							CommandSourceType);
						union
						{
							void (*fn)();
							RepairFn call;
						} repair = { j_00029c08 };

						(ai->m_command.*repair.call)(candidate, CMD_FROM_SCRIPT);
					}
				}
			}
			break;
		}
	}
}
