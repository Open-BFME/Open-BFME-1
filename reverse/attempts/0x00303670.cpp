// ?d_00303670@@YAXXZ
// partial score=0.3443 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// stlport

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;

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
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad_008[0xc8 - 8];
	unsigned int m_flagsC8;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
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
	void aiRepair(Object *target, CommandSourceType source);
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
		return m_template.operator->();
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

class BfmeTeamEstimatePositionCall
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *position) const;
};

extern void j_0002990b(void);

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_0002990b;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		function.member)(position);
}

class Team
{
public:
	Player *getControllingPlayer() const;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
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
		const KindOfMaskType &mustBeClear);
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

extern void j_00001140(void);
extern void j_000022bb(void);
extern void j_0002369b(void);
extern void j_00029c08(void);

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Team@@QBEPAVPlayer@@XZ=?j_0002369b@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiRepair@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z=?j_00029c08@@YAXXZ")

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
	Coord3D *position = bfmeGetEstimateTeamPosition(team, &teamPosition);
	int radiusBits = *(int *)&radius;
	BfmeWideResult result = ((BfmeWideForwardC *)ThePartitionManager)->
		bfmeForwardWideC((int)position, radiusBits, 0,
			(int)PartitionFilterPlayerAffiliation(
				team->getControllingPlayer(), 2, true).link(
					filterAddress(PartitionFilterAcceptByKindOf(
						KindOfMaskType(KindOfMaskType::kInit, 39),
						KINDOFMASK_NONE))), 1);

	while (Object *candidate = result.next())
	{
		RvaBodySlotView *body = (RvaBodySlotView *)
			*(void **)((char *)candidate + 0x200);
		if (body && body->RvaBodySlot05() < g_bfmeDefaultBU)
		{
			BfmeDlinkIterator<Object> members = team->iterate_TeamMemberList();
			while (!members.done())
			{
				Object *member = members.cur();
				const ThingTemplate *thing = member->getTemplate();
				if (thing && (thing->m_flagsC8 & 0x4000) != 0)
				{
					BfmeAIUpdateView *ai = member->m_ai;
					if (ai)
						ai->m_command.aiRepair(candidate, CMD_FROM_SCRIPT);
				}
				members.advance();
			}
			break;
		}
	}
}
