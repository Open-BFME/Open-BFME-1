// ?bfmeAreaBody@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.312857 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
//
// BFME ScriptConditions area-body recovery. The named sibling bfmeAreaGate
// (0x0032C400, matched) calls this body through ILT 0x0000C586 as
// `!bfmeAreaBody(a, b, c)` with its own params in the same order, confirming
// conditionParm=a, playerParm=b, triggerParm=c. The brief's callee count
// Retail makes five independent final-template calls for five bit tests;
// containment and the dead-bit test sit between the fourth and fifth tests.

#include "ObjectDlinkPmf.h"
#include "../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

// Retail calls StringBase::releaseBuffer directly for this local's cleanup.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class PolygonTrigger;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class BfmeP1087
{
public:
	UnsignedShort bfmeNext1087(Parameter *parameter);
};

extern BfmeP1087 *g_bfmeP1087;

class Player;

class BfmePlayerList
{
};

extern BfmePlayerList *ThePlayerList;
extern void j_0002ee60();

static Player *bfmeGetEachPlayerFromMask(BfmePlayerList *players,
	UnsignedShort &mask)
{
	typedef Player *(BfmePlayerList::*Function)(UnsignedShort &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002ee60;
	return (reinterpret_cast<BfmePlayerList *>(players)->*fn.member)(mask);
}

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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;

template <class ObjectType> class DLINK_ITERATOR
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	DLINK_ITERATOR(ObjectType *current, GetNextFunc next)
		: m_current(current), m_next(next) {}

	void advance()
	{
		if (m_current)
			m_current = (m_current->*m_next)();
	}

	Bool done() const { return m_current == 0; }
	ObjectType *cur() const { return m_current; }

private:
	ObjectType *m_current;
	GetNextFunc m_next;
};

struct BfmeConditionCache
{
	unsigned char m_beforeCustomData[0x44];
	Int m_customData;
	UnsignedInt m_customFrame;
};

struct BfmeScriptEngineFrames
{
	unsigned char m_beforeFrames[0x170d8];
	UnsignedInt m_frameChanged;
	UnsignedInt m_frame;
};

struct BfmePlayerTeamNode;

struct BfmePlayerTeams
{
	unsigned char m_beforeTeams[0x288];
	BfmePlayerTeamNode *m_sentinel;
};

struct BfmePlayer
{
	BfmePlayerTeams m_teams;
};

struct BfmePlayerTeamNode
{
	BfmePlayerTeamNode *m_next;
	BfmePlayerTeamNode *m_prev;
	void *m_prototype;
};

class Team;

class TeamPrototype
{
public:
	unsigned char m_beforeInstances[0x274];
	Team *m_teamInstanceList;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	void *m_vtable;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_current(head) {}

	Bool done() const { return m_current == 0; }
	Team *cur() const { return m_current; }
	void advance()
	{
		if (m_current)
			m_current = m_current->_bfme_nextInInstanceList();
	}

private:
	Team *m_current;
};

struct BfmeOverridable
{
	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

struct BfmeObjectTemplate
{
	void *m_vtable;
	BfmeOverridable *m_template;
};

struct BfmeObjectState
{
	unsigned char m_beforeDead[0x344];
	unsigned char m_dead;
};

struct BfmeThingTemplate
{
	unsigned char m_beforeKindOf[0xd0];
	UnsignedInt m_kindOf2;
	UnsignedInt m_kindOf3;
	UnsignedInt m_kindOf4;
	UnsignedInt m_kindOf5;
};

extern void j_000022bb();
extern void j_0000d6ed();

static BfmeOverridable *bfmeFinalTemplate(Object *object)
{
	BfmeOverridable *templateObject =
		((BfmeObjectTemplate *)object)->m_template;
	if (templateObject && templateObject->m_nextOverride) {
		typedef BfmeOverridable *(BfmeOverridable::*Function)() const;
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_000022bb;
		templateObject =
			(reinterpret_cast<BfmeOverridable *>(templateObject->m_nextOverride)->*fn.member)();
	}
	return templateObject;
}

static Bool bfmeObjectIsInside(Object *object, PolygonTrigger *trigger)
{
	class ObjectInsideCall
	{
	public:
		Bool isInside(PolygonTrigger *) const;
	};
	typedef Bool (ObjectInsideCall::*Function)(PolygonTrigger *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000d6ed;
	return (reinterpret_cast<ObjectInsideCall *>(object)->*fn.member)(trigger);
}

class ScriptConditions
{
protected:
	Bool bfmeAreaBody(Parameter *, Parameter *, Parameter *);
};

// ?bfmeAreaBody@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::bfmeAreaBody(Parameter *conditionParm,
	Parameter *playerParm, Parameter *triggerParm)
{
	AsciiString triggerName = triggerParm->getString();
	PolygonTrigger *trigger =
		TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
	BfmeConditionCache *condition =
		reinterpret_cast<BfmeConditionCache *>(conditionParm);
	if (!trigger)
		return false;

	UnsignedShort playerMask = g_bfmeP1087->bfmeNext1087(playerParm);
	if (!playerMask)
		goto failed;

	do {
		Player *player = bfmeGetEachPlayerFromMask(ThePlayerList, playerMask);
		if (!player)
			goto failed;

		BfmeScriptEngineFrames *engine =
			reinterpret_cast<BfmeScriptEngineFrames *>(TheScriptEngine);
		if (condition->m_customData != 0 &&
			engine->m_frameChanged <= condition->m_customFrame &&
			engine->m_frame <= condition->m_customFrame) {
			if (condition->m_customData == -1)
				goto failed;
			if (condition->m_customData == 1)
				return true;
		}

		Int count = 0;
		BfmePlayerTeamNode *sentinel =
			reinterpret_cast<BfmePlayer *>(player)->m_teams.m_sentinel;
		for (BfmePlayerTeamNode *node = sentinel->m_next;
			node != reinterpret_cast<BfmePlayer *>(player)->m_teams.m_sentinel;
			node = node->m_next) {
			TeamPrototype *prototype =
				reinterpret_cast<TeamPrototype *>(node->m_prototype);
			for (BfmeTeamInstanceIterator teams(prototype->m_teamInstanceList);
				!teams.done(); teams.advance()) {
				for (DLINK_ITERATOR<Object> members =
						teams.cur()->iterate_TeamMemberList();
					!members.done(); members.advance()) {
					Object *object = members.cur();
					if ((reinterpret_cast<BfmeThingTemplate *>(bfmeFinalTemplate(object))->m_kindOf2 & 0x01000000) != 0)
						continue;
					if ((reinterpret_cast<BfmeThingTemplate *>(bfmeFinalTemplate(object))->m_kindOf4 & 0x20) != 0)
						continue;
					if ((reinterpret_cast<BfmeThingTemplate *>(bfmeFinalTemplate(object))->m_kindOf4 & 0x00800000) != 0)
						continue;
					if ((reinterpret_cast<BfmeThingTemplate *>(bfmeFinalTemplate(object))->m_kindOf5 & 0x00002000) != 0)
						continue;
					if (!bfmeObjectIsInside(object, trigger))
						continue;
					if ((reinterpret_cast<BfmeObjectState *>(object)->m_dead & 1) != 0)
						continue;
					if ((*(UnsignedInt *)((char *)bfmeFinalTemplate(object) + 0xc8) & 0x02000000) != 0)
						continue;
					++count;
				}
			}
		}

		condition->m_customFrame = reinterpret_cast<BfmeScriptEngineFrames *>(TheScriptEngine)->m_frameChanged;
		if (count > 0) {
			condition->m_customData = 1;
			return true;
		}
	} while (playerMask != 0);

	failed:
	condition->m_customData = -1;
	return false;
}
