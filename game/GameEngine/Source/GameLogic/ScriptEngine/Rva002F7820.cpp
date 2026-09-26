// ?rva002F7820@ScriptActions@@IAEXPAVParameter@@0H@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/objectdlink
// Retail 0x002F7820 dispatches action IDs 539, 540 and 541. The method name
// is unknown, so retain its address. The body ends at RET 12 at 0x002F7A2E;
// INT3 padding starts at 0x002F7A31 (529 decoded bytes).
// Callees: lookup 0003A751 -> 00383880 -> 00363360 (name -> army record),
// assimilate 0003A279 -> 00383930 -> 00361250 (Object*, army index),
// mask 0004B290 -> 0034CB60 (zero-extended 16-bit mask returned in EAX),
// player walk 0002EE60 -> 000DF4A0 (consumes ushort mask by reference),
// team link 00022A70 -> 000C8A30 (reads +0x14), Object PMF 00001140 ->
// 000C8980 (reads +0x260 from Object's +4 DLINK base).
// Native team iterator PMF supplies the observed 8-byte iterator layout.
// The player-mask loop must repeat: the old bank incorrectly visited one player.

#include "StringInline.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

struct BfmeNode2B0
{
public:
	unsigned char m_beforeValue[4];
	int m_army;
	unsigned char m_beforeState[0x18];
	int m_state;
};

class BfmeMgr2B0
{
public:
	BfmeNode2B0 *lookupByField(void *field10);
};

class BfmeGlobFEA : public BfmeMgr2B0
{
public:
	void bfmeCallFEA(void *object, int army);
};

template<class ObjectType>
class DLINK_ITERATOR
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)(void) const;

	DLINK_ITERATOR(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

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
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class BfmeScriptEngineVtbl_68
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
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class Player;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class BfmePlayerTeamView
{
public:
	unsigned char m_beforeHead[0x0c];
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_beforeInstances[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class BfmePlayerTeamInstanceIterator
{
public:
    typedef BfmeTeamInstanceLink *(BfmeTeamInstanceLink::*GetNextFunc)();
    BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head)
        : m_cur(head), m_getNext(&BfmeTeamInstanceLink::_bfme_nextInInstanceList) {}
    Bool done() const { return m_cur == 0; }
    BfmePlayerTeamView *cur() const { return m_cur; }
    void advance() {
        if(m_cur) m_cur = (BfmePlayerTeamView *)(((BfmeTeamInstanceLink *)m_cur)->*m_getNext)();
    }
private:
    BfmePlayerTeamView *m_cur;
    GetNextFunc m_getNext;
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	BfmePlayerTeamPrototypeInstances *m_prototype;
};

class Player
{
public:
	unsigned char m_beforeTeams[0x288];
	BfmePlayerTeamListNode *m_playerTeamPrototypes;
};

class ScriptActions
{
protected:
	void rva002F7820(Parameter *objectParameter, Parameter *armyParameter,
		int actionType);
};

extern BfmeGlobFEA *TheGameLogic;
extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::rva002F7820(Parameter *objectParameter,
	Parameter *armyParameter, int actionType)
{
	int savedState;
	BfmeNode2B0 *army = TheGameLogic->lookupByField(
		(char *)armyParameter + 0x10);
	if (!army)
		return;

	savedState = army->m_state;
	army->m_state = 4;

	switch (actionType)
	{
	case 541:
		{
			Object *object = ((BfmeScriptEngineVtbl_68 *)TheScriptEngine)
				->getUnitNamed(*(const AsciiString *)objectParameter);
			if (object)
				TheGameLogic->bfmeCallFEA(object,
					army->m_army);
			break;
		}
	case 540:
		{
		Team *team = ((BfmeScriptEngineVtbl_44 *)TheScriptEngine)->getTeamNamed(
			objectParameter->m_string, false);
		if (team)
		{
			for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList();
				!objects.done(); objects.advance())
			{
				Object *object = objects.cur();
				if (object)
					TheGameLogic->bfmeCallFEA(object,
						army->m_army);
			}
		}
		break;
		}
	case 539:
		{
			PlayerMaskType mask =
				((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
					->getPlayerMaskFromAsciiString(objectParameter->m_string, 0);
			while ((PlayerMaskType)mask)
			{
				Player *player = ThePlayerList->getEachPlayerFromMask(
					(PlayerMaskType &)mask);
				if (player)
				{
					objectParameter = (Parameter *)
						((Player *)player)->m_playerTeamPrototypes->m_next;
					if ((BfmePlayerTeamListNode *)objectParameter !=
						((Player *)player)->m_playerTeamPrototypes)
					{
						do
						{
							BfmePlayerTeamInstanceIterator teams(
								((BfmePlayerTeamListNode *)objectParameter)->m_prototype
									->m_teamInstanceList);
							for (; !teams.done(); teams.advance())
							{
								BfmePlayerTeamView *team = teams.cur();
								if (!team)
									continue;
							DLINK_ITERATOR<Object> objects =
								team->iterate_TeamMemberList();
							for (; !objects.done(); objects.advance())
							{
								Object *object = objects.cur();
								if (object)
										TheGameLogic->bfmeCallFEA(object,
											army->m_army);
								}
							}
							objectParameter = (Parameter *)
								((BfmePlayerTeamListNode *)objectParameter)->m_next;
						} while ((BfmePlayerTeamListNode *)objectParameter !=
							((Player *)player)->m_playerTeamPrototypes);
					}
				}
			}
			break;
		}
	}

	army->m_state = savedState;
}
