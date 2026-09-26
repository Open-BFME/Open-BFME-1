// ?rva0032c680@ScriptConditions@@IAE_NPAVParameter@@00@Z
// Retail RVA 0x0032C680, 286 bytes. The dispatcher at 0x0032D720 calls this
// as a ScriptConditions member with three Parameter pointers. Its semantic
// identity is unresolved, so the method name stays address-derived.
//
// Retail resolves parameter 0 to a player mask, walks that Player's team
// prototype list (+0x288), walks each prototype's live Team instances
// (+0x274), and DLINK-walks each instance's members. It follows each member
// template's override chain, requires template flag 0x02000000, and counts
// members whose non-null +0x210 subobject has a +0x28 value meeting parameter
// 2's integer threshold. The result compares the count with parameter 1.

// stlport
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib

#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short PlayerMaskType;

class Parameter
{
public:
	Int getInt() const { return m_int; }
private: unsigned char m_prefix[8]; Int m_int;
};

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	UnsignedInt flags() const
	{
		return *(const UnsignedInt *)((const char *)this + 0xD0);
	}
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList() const;
};

// Preserve the native pointer-to-member representation used by both loops.
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}
};

class BfmePlayerTeamPrototypeInstances;

class Player
{
public:
	UnsignedByte m_beforeTeamList[0x288];
	std::list<BfmePlayerTeamPrototypeInstances *> m_playerTeamPrototypes;
};

class BfmePlayerTeamPrototypeInstances
{
public:
	UnsignedByte m_beforeInstances[0x274];
	BfmeTeamInstanceLink *m_teamInstanceList;
};

class BfmeTeamInstance
{
public:
	UnsignedByte m_beforeMemberHead[0x0C];
	Object *m_memberHead;

	DLINK_ITERATOR<Object> iterateMembers() const
	{
		return DLINK_ITERATOR<Object>(m_memberHead,
			Object::dlink_next_TeamMemberList);
	}
};

// These are offset views, not claims about the semantic names of the fields.
// Retail reads the template pointer at Object+4 and tests its +0xD0 flags.
static inline const char *rva0032c680_subobject(const Object *obj)
{
	return *(const char *const *)((const char *)obj + 0x210);
}

static inline Int rva0032c680_subobjectValue(const char *subobject)
{
	return *(const Int *)(subobject + 0x28);
}

class ScriptConditions
{
protected:
	Bool rva0032c680(Parameter *, Parameter *, Parameter *);
};

Bool ScriptConditions::rva0032c680(
	Parameter *playerParameter, Parameter *minimumCountParameter,
	Parameter *memberThresholdParameter)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	Int count = 0;
	for (std::list<BfmePlayerTeamPrototypeInstances *>::iterator node=player->m_playerTeamPrototypes.begin();
         node!=player->m_playerTeamPrototypes.end(); ++node)
	{
		DLINK_ITERATOR<BfmeTeamInstanceLink> teams((*node)->m_teamInstanceList, &BfmeTeamInstanceLink::_bfme_nextInInstanceList);
		for (; !teams.done(); teams.advance())
		{
			BfmeTeamInstance *team = (BfmeTeamInstance *)teams.cur();
			if (!team) continue;
			DLINK_ITERATOR<Object> members = team->iterateMembers();
			for (; !members.done(); members.advance())
			{
				Object *member = members.cur();
				if (!member)
					continue;
				const ThingTemplate *objectTemplate =
					*(const ThingTemplate *const *)((const char *)member + 4);
				if (objectTemplate && objectTemplate->m_nextOverride)
					objectTemplate = (const ThingTemplate *)
						objectTemplate->m_nextOverride->getFinalOverride();
				if (!(objectTemplate->flags() & 0x02000000))
					continue;

				const char *subobject = rva0032c680_subobject(member);
				if (subobject &&
					rva0032c680_subobjectValue(subobject) >=
						memberThresholdParameter->getInt())
					++count;
			}
		}
	}

	// Explicit Boolean branches reproduce the retail return sequence.
	if (count >= minimumCountParameter->getInt())
		return true;
	return false;
}

