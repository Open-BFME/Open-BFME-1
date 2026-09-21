// ?rva0032C990@@YG_NPAUParameter@@00@Z
// partial score=0.17 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x0032C990 (288 B). ScriptConditions-family
// predicate: resolves a player from parameter[0]'s mask and an upgrade
// template from parameter[1]'s name, then walks every team the player
// owns (player+0x288, a circular list) and every object in each team
// (Team::iterate_TeamMemberList, the BfmeDlinkIterator<Object> pattern
// already landed in RTS/Team_countObjects.cpp) counting objects whose
// 0x94 flag byte does not have bit 0x20 set and that report the upgrade
// via Object::hasUpgrade; returns whether that count reached
// parameter[2]'s +8 threshold. Every callee below is the already-landed
// real body its ILT jumps to (see brief evidence), not a fresh guess:
// ScriptEngine::unidentified_0034DB40, PlayerList::getPlayerFromMask,
// UpgradeCenter::findUpgrade, Object::hasUpgrade, and the DLink next/
// instance-list-advance pair from the same family as Team_countObjects.

typedef unsigned short PlayerMaskType;
typedef bool Bool;

class AsciiString
{
public:
	void *m_data;
};

struct Parameter
{
	unsigned char m_pad00[0x10];
	AsciiString m_string;
};

class Player;

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *);
};

extern ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType);
};

extern PlayerList *ThePlayerList;

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	Object *dlink_next_TeamMemberList() const;
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;

	unsigned char m_pad00[0x94];
	unsigned char m_flags94;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();

	unsigned char m_pad00[8];
	unsigned char m_teamPad[0x274 - 8];
	Object *m_head;
};

class Player
{
public:
	unsigned char m_pad00[0x288];
	BfmeTeamInstanceLink m_teamListHead;
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext)
	{
	}

	bool done() const { return m_cur == 0; }
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

bool __stdcall rva0032C990(Parameter *playerParam, Parameter *upgradeParam, Parameter *thresholdParam)
{
	Player *player = ThePlayerList->getPlayerFromMask(
		TheScriptEngine->unidentified_0034DB40(playerParam));
	if (player == 0)
		return false;

	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeParam->m_string);
	if (upgrade == 0)
		return false;

	int count = 0;

	BfmeTeamInstanceLink *node = &player->m_teamListHead;
	BfmeTeamInstanceLink *cur = *(BfmeTeamInstanceLink **)node;
	if (cur != node)
	{
		do
		{
			Object *head = cur->m_head;
			for (BfmeDlinkIterator<Object> iter(head, &Object::dlink_next_TeamMemberList);
				 !iter.done(); iter.advance())
			{
				Object *obj = iter.cur();
				if ((obj->m_flags94 & 0x20) == 0 && obj->hasUpgrade(upgrade))
					++count;
			}
			cur = cur->_bfme_nextInInstanceList();
		} while (cur != node);
	}

	return count >= *(int *)(thresholdParam->m_pad00 + 8);
}

// @?rva0032C990@@YA_NPAUParameter@@00@Z 0x0032C990
