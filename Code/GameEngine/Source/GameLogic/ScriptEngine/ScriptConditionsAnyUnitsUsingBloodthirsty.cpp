// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ScriptConditions::evaluateAnyUnitsUsingBloodthirsty, retail RVA
// 0x0032CCC0 (186 bytes).
//
// Identity is established by executeCondition's BFME dispatch table: table
// index 176 (Condition type 181) tail-jumps through ILT 0x000344DC to this
// body.  ScriptConditions' canonical template at index 181 is
// ANY_UNITS_USING_BLOODTHIRSTY with one player-mask parameter.  The BFME
// player/team/object offsets and the three helper routes below are the same
// layouts used by the matched Player team walks and the ScriptConditions
// team-member family.

typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

class Parameter;
class Player;

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class BfmePlayerObjectDlinkObject;

class BfmePlayerObjectVirtualTail
{
public:
	UnsignedByte m_vt[4];
};

class BfmePlayerObjectVbptrCarrier : public virtual BfmePlayerObjectVirtualTail
{
public:
	UnsignedByte m_carrier[4];
};

class BfmePlayerObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmePlayerObjectDlinkBase
{
public:
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmePlayerObjectDlinkPad
{
public:
	UnsignedByte m_pad[0x64];
};

class BfmePlayerObjectDlinkObject : public BfmePlayerObjectVtbl,
	public BfmePlayerObjectDlinkBase, public BfmePlayerObjectDlinkPad,
	public BfmePlayerObjectVbptrCarrier
{
public:
	UnsignedByte m_tail[0x40];
};

template <class ObjectType> class BfmePlayerDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmePlayerDlinkIterator(ObjectType *cur, GetNextFunc getNext)
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
	GetNextFunc m_getNext;
};

class BfmePlayerTeamView
{
public:
	UnsignedByte m_unmodelled_000[0x0c];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>
	iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			BfmePlayerObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) { }

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
	Int m_unmodelled;
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	BfmePlayerTeamPrototypeInstances *m_prototype;
};

struct BfmePlayerTeamListField
{
	UnsignedByte m_unmodelled_000[0x288];
	BfmePlayerTeamListNode *m_head;
};

struct BfmeBloodthirstyObjectFields
{
	UnsignedByte m_beforeStatus[0x98];
	UnsignedByte m_status98;
};

class ScriptConditions
{
protected:
	Bool evaluateAnyUnitsUsingBloodthirsty(Parameter *playerParameter);
};

// ?evaluateAnyUnitsUsingBloodthirsty@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateAnyUnitsUsingBloodthirsty(
	Parameter *playerParameter)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	for (BfmePlayerTeamListNode *it =
			((BfmePlayerTeamListField *)player)->m_head->m_next;
		it != ((BfmePlayerTeamListField *)player)->m_head; it = it->m_next)
	{
		BfmePlayerTeamInstanceIterator teams(
			it->m_prototype->m_teamInstanceList);
		for (; !teams.done(); teams.advance())
		{
			BfmePlayerTeamView *team = teams.cur();
			if (!team)
				continue;

			BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> objects =
				team->iterate_TeamMemberList();
			for (; !objects.done(); objects.advance())
			{
				BfmePlayerObjectDlinkObject *object = objects.cur();
				if (!object)
					continue;

				if (((BfmeBloodthirstyObjectFields *)object)->m_status98 & 1)
					return true;
			}
		}
	}

	return false;
}
