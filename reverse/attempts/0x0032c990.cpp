// ?rva0032C990@ScriptConditions@@IAE_NPAUParameter@@00@Z
// partial score=0.625 date=2026-09-25
// stlport
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/objectdlink /ICode/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x0032C990 (288 bytes), dispatcher-proven thiscall member.
// Parameters: player mask, minimum count, upgrade name. Three nested loops
// visit player prototypes, live Team instances, and Object team members.
// Object PMF layout mirrors ObjectDlinkPmf.h; this local view additionally
// declares hasUpgrade, which that narrow shim does not expose.
// The raw body reloads Player+0x288 after the nested calls, so the circular
// list head is read again for the closing comparison rather than cached.

#include "ascii_string.h"
#include <list>

typedef bool Bool;
typedef unsigned short PlayerMaskType;

struct Parameter
{
public:
	unsigned char m_beforeInt[8];
 int m_int; int m_at0C;
 int getInt() const {return m_int;}
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
	const UpgradeTemplate *findUpgrade(const AsciiString &) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Object;
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};
class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};
class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	Bool hasUpgrade(const UpgradeTemplate *) const;
	unsigned char m_tail[0x40];
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
	unsigned char m_link[8];
	void *m_prototype;
};

class Team { public: unsigned char m_prefix[12]; Object *m_head; Team *_bfme_nextInInstanceList() const; };

class TeamPrototypeView
{
public:
	unsigned char m_beforeMembers[0x274];
	Team *m_teamHead;
};

class Player
{
public:
	unsigned char m_beforeTeamList[0x288];
	std::list<TeamPrototypeView *> m_playerTeamPrototypes;
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;
	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
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

class ScriptConditions { protected: Bool rva0032C990(Parameter*,Parameter*,Parameter*); };

Bool ScriptConditions::rva0032C990(Parameter *playerParam, Parameter *thresholdParam,
	Parameter *upgradeParam)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParam);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	const UpgradeTemplate *upgrade =
		TheUpgradeCenter->findUpgrade(upgradeParam->m_string);
	if (!upgrade)
		return false;

	int count = 0;
	for (std::list<TeamPrototypeView *>::iterator node = player->m_playerTeamPrototypes.begin();
		node != player->m_playerTeamPrototypes.end(); ++node)
	{
		TeamPrototypeView *prototype = *node;
			for(BfmeDlinkIterator<Team> instances(prototype->m_teamHead,&Team::_bfme_nextInInstanceList); !instances.done(); instances.advance()) {
			Team *instance=instances.cur();
			if (!instance) continue;
			Object *head = instance->m_head;
			for (BfmeDlinkIterator<Object> iter(
				head, &BfmeObjectDlinkBase::dlink_next_TeamMemberList);
				 !iter.done(); iter.advance())
			{
				Object *object = iter.cur();
				if ((((unsigned char *)object)[0x94] & 0x20) == 0 &&
					object->hasUpgrade(upgrade))
					++count;
			}
			}
	}

	return count >= thresholdParam->getInt();
}
