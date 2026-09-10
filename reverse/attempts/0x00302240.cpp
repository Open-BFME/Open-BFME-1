// ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.58 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// ScriptActions::doTeamGarrisonNearestBuilding, retail RVA 0x00302240.
// The executeAction TEAM_GARRISON_NEAREST_BUILDING arm names this operation.
// This TU keeps the BFME-only wide iterator and Object/DLINK layouts local;
// the vendored Zero Hour declarations use a different iterator ABI here.

#include "StringInline.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;

namespace _STL
{
	template <bool __threads, int __inst>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *p, unsigned int bytes);
	};
}

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

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void) = 0;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && *(const void *const *)((const char *)value + 4))
			value = (const T *)((const Overridable *)
				*(const void *const *)((const char *)value + 4))->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum KindOfType
{
	KINDOF_INFANTRY = 16,
	KINDOF_NO_GARRISON = 27
};

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		const volatile UnsignedInt *kindOf =
			(const volatile UnsignedInt *)((const char *)this + 0xc8);
		return (kindOf[(UnsignedInt)kind >> 5] &
			(1u << ((UnsignedInt)kind & 31))) != 0;
	}
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

// Object+0x68 is the inherited vbptr used by the retail DLINK PMF.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class AICommandInterface
{
public:
	void aiEnter(Object *building, int source);
};

class BfmeAIUpdateView
{
public:
	unsigned char m_beforeCommands[0x20];
	AICommandInterface m_commands;
};

class ContainModuleInterface
{
public:
#define BFME_CONTAIN_SLOT(N) virtual void bfmeContainSlot##N(void) = 0
	BFME_CONTAIN_SLOT(00); BFME_CONTAIN_SLOT(01);
	BFME_CONTAIN_SLOT(02); BFME_CONTAIN_SLOT(03);
	BFME_CONTAIN_SLOT(04); BFME_CONTAIN_SLOT(05);
	BFME_CONTAIN_SLOT(06); BFME_CONTAIN_SLOT(07);
	BFME_CONTAIN_SLOT(08); BFME_CONTAIN_SLOT(09);
	BFME_CONTAIN_SLOT(10); BFME_CONTAIN_SLOT(11);
	BFME_CONTAIN_SLOT(12); BFME_CONTAIN_SLOT(13);
	BFME_CONTAIN_SLOT(14); BFME_CONTAIN_SLOT(15);
	BFME_CONTAIN_SLOT(16); BFME_CONTAIN_SLOT(17);
	BFME_CONTAIN_SLOT(18); BFME_CONTAIN_SLOT(19);
	BFME_CONTAIN_SLOT(20); BFME_CONTAIN_SLOT(21);
	BFME_CONTAIN_SLOT(22);
	virtual UnsignedInt getContainMax(void) const = 0;
#undef BFME_CONTAIN_SLOT
	virtual void bfmeContainSlot24(void) = 0;
	virtual void bfmeContainSlot25(void) = 0;
	virtual void bfmeContainSlot26(void) = 0;
	virtual void bfmeContainSlot27(void) = 0;
	virtual void bfmeContainSlot28(void) = 0;
	virtual void bfmeContainSlot29(void) = 0;
	virtual void bfmeContainSlot30(void) = 0;
	virtual void bfmeContainSlot31(void) = 0;
	virtual void bfmeContainSlot32(void) = 0;
	virtual void bfmeContainSlot33(void) = 0;
	virtual void bfmeContainSlot34(void) = 0;
	virtual void bfmeContainSlot35(void) = 0;
	virtual void bfmeContainSlot36(void) = 0;
	virtual void bfmeContainSlot37(void) = 0;
	virtual void bfmeContainSlot38(void) = 0;
	virtual void bfmeContainSlot39(void) = 0;
	virtual void bfmeContainSlot40(void) = 0;
	virtual void bfmeContainSlot41(void) = 0;
	virtual void bfmeContainSlot42(void) = 0;
	virtual void bfmeContainSlot43(void) = 0;
	virtual void bfmeContainSlot44(void) = 0;
	virtual void bfmeContainSlot45(void) = 0;
	virtual void bfmeContainSlot46(void) = 0;
	virtual void bfmeContainSlot47(void) = 0;
	virtual void bfmeContainSlot48(void) = 0;
	virtual void bfmeContainSlot49(void) = 0;
	virtual void bfmeContainSlot50(void) = 0;
	virtual void bfmeContainSlot51(void) = 0;
	virtual void bfmeContainSlot52(void) = 0;
	virtual void bfmeContainSlot53(void) = 0;
	virtual void bfmeContainSlot54(void) = 0;
	virtual void bfmeContainSlot55(void) = 0;
	virtual void bfmeContainSlot56(void) = 0;
	virtual void bfmeContainSlot57(void) = 0;
	virtual void bfmeContainSlot58(void) = 0;
	virtual void bfmeContainSlot59(void) = 0;
	virtual void bfmeContainSlot60(void) = 0;
	virtual void bfmeContainSlot61(void) = 0;
	virtual void bfmeContainSlot62(void) = 0;
	virtual void bfmeContainSlot63(void) = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:

	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	BfmeAIUpdateView *getAIUpdateInterface(void) const
	{
		return *(BfmeAIUpdateView *const *)((const char *)this + 0x204);
	}

	ContainModuleInterface *getContain(void) const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1fc);
	}

	const ThingTemplate *getTemplate(void) const
	{
		return m_template.operator->();
	}

	Bool isKindOf(KindOfType kind) const
	{
		const ThingTemplate *thingTemplate = getTemplate();
		return thingTemplate != 0 && thingTemplate->isKindOf(kind);
	}
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

template<class ObjectType>
class DLINK_ITERATOR
{
public:
	DLINK_ITERATOR(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

	void advance(void)
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	Bool done(void) const { return m_cur == 0; }
	ObjectType *cur(void) const { return m_cur; }

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

class Team
{
public:
	Player *getControllingPlayer(void) const;

	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			(BfmeGetNextTeamMemberFunc)
				BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}

private:
	unsigned char m_beforeMembers[0x0c];
	Object *m_head;
};

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	UnsignedInt m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object)
	{
		m_next = 0;
		m_vptr = 0x01085dd0;
		m_object = object;
	}

	~PartitionFilterSameMapStatus(void)
	{
		m_vptr = 0x01083b5c;
	}

	const Object *m_object;
};

class PartitionFilterGarrisonableByPlayer : public PartitionFilter
{
public:
	PartitionFilterGarrisonableByPlayer(const Player *player, Bool match,
		int source)
	{
		m_next = 0;
		m_vptr = 0x010cfff0;
		m_player = player;
		m_match = match;
		m_source = source;
	}

	~PartitionFilterGarrisonableByPlayer(void)
	{
		m_vptr = 0x01083b5c;
	}

	const Player *m_player;
	Bool m_match;
	int m_source;
};

struct BfmeRangeNode
{
	Object *m_object;
	UnsignedInt m_padding;
};

class SimpleObjectIterator
{
public:
	Object *first(void)
	{
		return next();
	}

	Object *next(void)
	{
		char *end = m_end;
		char *cur = m_current;
		if (cur == end)
			return 0;
		Object *object = *(Object **)cur;
		cur += 8;
		m_current = cur;
		return object;
	}

	void deleteInstance(void)
	{
		--m_refCount;
		if (m_refCount == 0)
		{
			char *begin = m_begin;
			if (begin != 0)
			{
				Int bytes = ((m_capacity - begin) >> 3) << 3;
				if (bytes > 0x80)
					::operator delete(begin);
				else
					_STL::__node_alloc<true, 0>::_M_deallocate(begin, bytes);
			}
			::operator delete(this);
		}
	}

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
	char *m_current;
	Int m_refCount;
};

struct BfmeWideResult
{
	SimpleObjectIterator *m_value;

	~BfmeWideResult(void)
	{
		m_value->deleteInstance();
	}
};

class BfmeWideResultSource
{
};

class BfmeWideForwardC
{
	char m_pad[0x0c];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class PartitionManager : public BfmeWideForwardC
{
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0; virtual void slot01(void) = 0;
	virtual void slot02(void) = 0; virtual void slot03(void) = 0;
	virtual void slot04(void) = 0; virtual void slot05(void) = 0;
	virtual void slot06(void) = 0; virtual void slot07(void) = 0;
	virtual void slot08(void) = 0; virtual void slot09(void) = 0;
	virtual void slot10(void) = 0; virtual void slot11(void) = 0;
	virtual void slot12(void) = 0; virtual void slot13(void) = 0;
	virtual void slot14(void) = 0; virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern PartitionManager *ThePartitionManager;

class ScriptActions
{
protected:
	void doTeamGarrisonNearestBuilding(const AsciiString &teamName);
};

// ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamGarrisonNearestBuilding(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	DLINK_ITERATOR<Object> diter = theTeam->iterate_TeamMemberList();
	Object *leader = diter.cur();
	if (!leader)
		return;

	PartitionFilterSameMapStatus f1(leader);
	PartitionFilterGarrisonableByPlayer f2(
		theTeam->getControllingPlayer(), true, 1);
	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(int)leader->getPosition(), 0x49742400, 3,
		(int)f2.link(&f1), 1);

	Object *theBuilding;
	while ((theBuilding = result.m_value->next()) != 0)
	{
		ContainModuleInterface *contain = theBuilding->getContain();
		if (!contain)
			continue;

		Int slotsAvailable = (Int)contain->getContainCount(false);
		slotsAvailable = (Int)contain->getContainMax() - slotsAvailable;
		for (Int i = 0; i < slotsAvailable; )
		{
			Object *object = diter.cur();
			if (diter.done() || !object)
				return;

			BfmeAIUpdateView *ai = object->getAIUpdateInterface();
			if (ai && object->isKindOf(KINDOF_INFANTRY) &&
				!object->isKindOf(KINDOF_NO_GARRISON))
			{
				ai->m_commands.aiEnter(theBuilding, 1);
				++i;
			}
			diter.advance();
		}
	}
}
