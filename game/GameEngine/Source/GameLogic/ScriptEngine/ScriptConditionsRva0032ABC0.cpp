// ?rva0032ABC0@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1111@Z
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0032ABC0, 820 bytes (ret 0x18; jump table inside the boundary).
//
// Identity: reached only from the matched condition dispatcher
// Rva0032D720::evaluate (Rva0032D720Dispatcher.cpp, case 75) through ILT
// j_0001bc25 with (Condition, five Parameters). ECX is never read. Case 74 is
// the matched sibling rva0032A710 (ZH evaluatePlayerHasUnitTypeInArea shape);
// this body is BFME's version of Zero Hour's
// ScriptConditions::evaluatePlayerHasUnitKindInArea (trigger lookup, KindOf
// parameter, team-instance change cache, member walk, comparison switch,
// setCustomData(frame) at the end) extended with the same player MASK loop, so
// no ZH name fits exactly; the name keeps the address token.
//
// Layouts follow the matched sibling ScriptConditionsRva0032A710.cpp.
// Team member-walk siblings (Rva000F4830TeamCountKind.cpp).

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

class Object;
class PolygonTrigger;

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

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
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
	BfmeOverride<class ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xc0];
	UnsignedInt m_kindOf[6];

	Bool hasKind(UnsignedInt kind) const
	{
		UnsignedInt mask = 1u << (kind & 31);
		return (m_kindOf[kind >> 5] & mask) == mask;
	}
	Bool isKindOf(UnsignedInt kind) const
	{
		UnsignedInt word = m_kindOf[kind >> 5];
		return (word & (1u << (kind & 31))) != 0;
	}
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}
	Bool isInside(const PolygonTrigger *pTrigger) const;

	unsigned char m_tail[0x344 - 0x70];
	unsigned char m_status344;
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)() const;

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Team
{
public:
	Bool didEnterOrExit() const { return m_enteredOrExited; }
	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_firstMember,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}

	unsigned char m_pad00[0x0c];
	Object *m_firstMember;
	unsigned char m_pad10[0x30 - 0x10];
	Bool m_enteredOrExited;
};

typedef BfmeTeamInstanceLink *(BfmeTeamInstanceLink::*BfmeGetNextTeamFunc)();

class BfmeTeamIterator
{
public:
	BfmeTeamIterator(Team *cur, BfmeGetNextTeamFunc getNext) : m_cur(cur), m_getNext(getNext) { }
	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = (Team *)(((BfmeTeamInstanceLink *)m_cur)->*m_getNext)();
	}

private:
	Team *m_cur;
	BfmeGetNextTeamFunc m_getNext;
};

class TeamPrototype
{
public:
	unsigned char m_pad[0x274];
	Team *m_firstInstance;
	BfmeTeamIterator iterate_TeamInstanceList() const { return BfmeTeamIterator(m_firstInstance, &BfmeTeamInstanceLink::_bfme_nextInInstanceList); }
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_data;
};

struct PlayerTeamList
{
	PlayerTeamNode *m_node;
	PlayerTeamNode *begin() const { return m_node->m_next; }
	PlayerTeamNode *end() const { return m_node; }
};

class Player
{
public:
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }

	unsigned char m_pad[0x288];
	PlayerTeamList m_playerTeamPrototypes;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &maskToAdjust);
};
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };

	unsigned char m_pad00[0x08];
	Int m_int;
	unsigned char m_pad0c[0x04];
	AsciiString m_string;
};

class Condition
{
public:
	Int getCustomData() const { return m_customData; }
	void setCustomData(Int data) { m_customData = data; }
	UnsignedInt getCustomFrame() const { return m_customFrame; }
	void setCustomFrame(UnsignedInt frame) { m_customFrame = frame; }

	unsigned char m_pad[0x44];
	Int m_customData;
	UnsignedInt m_customFrame;
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);	// vtable+0x58

	UnsignedShort unidentified_0034DB40(Parameter *pParam);
	UnsignedInt getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }

	unsigned char m_pad[0x170d8 - 4];
	UnsignedInt m_frameObjectCountChanged;
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool rva0032ABC0(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm,
		Parameter *pCountParm, Parameter *pKindParm, Parameter *pTriggerParm);
};

Bool ScriptConditions::rva0032ABC0(Condition *pCondition, Parameter *pPlayerParm,
	Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pKindParm,
	Parameter *pTriggerParm)
{
	AsciiString triggerName = pTriggerParm->m_string;
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->m_string);
	if (pTrig == 0)
		return false;

	Int kind = pKindParm->m_int;
	UnsignedShort playerMask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	Int count = 0;
	while (playerMask)
	{
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
		const PlayerTeamNode *it;
		Bool anyChanges = false;
		Int customData = pCondition->getCustomData();
		if (customData != 0 && TheScriptEngine->getFrameObjectCountChanged() <= pCondition->getCustomFrame())
		{
			const PlayerTeamNode *end = pPlayer->getPlayerTeams()->end();
			for (it = pPlayer->getPlayerTeams()->begin(); it != end; it = it->m_next)
			{
				if (anyChanges)
					break;
				for (BfmeTeamIterator iter = it->m_data->iterate_TeamInstanceList(); !iter.done(); iter.advance())
				{
					if (anyChanges)
						break;
					Team *team = iter.cur();
					if (!team)
						continue;
					if (team->didEnterOrExit())
						anyChanges = true;
				}
			}

			if (!anyChanges)
			{
				if (customData == -1)
					continue;
				if (customData == 1)
					return true;
			}
		}

		for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); it = it->m_next)
		{
			for (BfmeTeamIterator titer = it->m_data->iterate_TeamInstanceList(); !titer.done(); titer.advance())
			{
				Team *team = titer.cur();
				if (!team)
					continue;
				for (BfmeDlinkIterator<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
				{
					Object *pObj = iter.cur();
					if (!pObj)
						continue;
					if (pObj->getTemplate()->isKindOf(kind))
					{
						if (!pObj->getTemplate()->hasKind(88) && pObj->isInside(pTrig))
						{
							if (!(pObj->m_status344 & 1))
								count++;
						}
					}
				}
			}
		}
	}

	Bool comparison = false;
	switch (pComparisonParm->m_int)
	{
		case Parameter::LESS_THAN:		comparison = (count < pCountParm->m_int); break;
		case Parameter::LESS_EQUAL:		comparison = (count <= pCountParm->m_int); break;
		case Parameter::EQUAL:			comparison = (count == pCountParm->m_int); break;
		case Parameter::GREATER_EQUAL:	comparison = (count >= pCountParm->m_int); break;
		case Parameter::GREATER:		comparison = (count > pCountParm->m_int); break;
		case Parameter::NOT_EQUAL:		comparison = (count != pCountParm->m_int); break;
	}
	pCondition->setCustomData(TheScriptEngine->getFrameObjectCountChanged());
	return comparison;
}
