// ?rva002F7820@ScriptActions@@IAEXPAVParameter@@0H@Z
// partial score=0.9 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Retail 0x002F7820 dispatches the three named-army assimilation actions.

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

class BfmeNode2B0
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
	int getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
};

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
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) {}

	Bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	BfmePlayerTeamView *m_cur;
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
	BfmePlayerTeamListNode *m_teamList;
};

class ScriptActions
{
protected:
	void rva002F7820(Parameter *objectParameter, Parameter *armyParameter,
		int actionType);
};

struct Rva002F7820SavedState
{
	int value;
	int padding;
};

extern BfmeGlobFEA *TheGameLogic;
extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::rva002F7820(Parameter *objectParameter,
	Parameter *armyParameter, int actionType)
{
	Rva002F7820SavedState savedState = { 0, 0 };
	armyParameter = (Parameter *)TheGameLogic->lookupByField(
		(char *)armyParameter + 0x10);
	if (!armyParameter)
		return;

	savedState.value = ((BfmeNode2B0 *)armyParameter)->m_state;
	savedState.padding = 0;
	((BfmeNode2B0 *)armyParameter)->m_state = 4;

	switch (actionType)
	{
	case 541:
		{
			Object *object = ((BfmeScriptEngineVtbl_68 *)TheScriptEngine)
				->getUnitNamed(*(const AsciiString *)objectParameter);
			if (object)
				TheGameLogic->bfmeCallFEA(object,
					((BfmeNode2B0 *)armyParameter)->m_army);
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
						((BfmeNode2B0 *)armyParameter)->m_army);
			}
		}
		break;
		}
	case 539:
		{
			actionType =
				((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
					->getPlayerMaskFromAsciiString(objectParameter->m_string, 0);
			if ((PlayerMaskType)actionType)
			{
				Player *player = ThePlayerList->getEachPlayerFromMask(
					(PlayerMaskType &)actionType);
				if (player)
				{
					objectParameter = (Parameter *)
						((Player *)player)->m_teamList->m_next;
					if ((BfmePlayerTeamListNode *)objectParameter !=
						((Player *)player)->m_teamList)
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
											((BfmeNode2B0 *)armyParameter)->m_army);
								}
							}
							objectParameter = (Parameter *)
								((BfmePlayerTeamListNode *)objectParameter)->m_next;
						} while ((BfmePlayerTeamListNode *)objectParameter !=
							((Player *)player)->m_teamList);
					}
				}
			}
			break;
		}
	}

	((BfmeNode2B0 *)armyParameter)->m_state = savedState.value;
}
