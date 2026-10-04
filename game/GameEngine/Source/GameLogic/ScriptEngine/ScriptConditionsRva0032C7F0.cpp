// ?rva0032C7F0@ScriptConditions@@IAE_NPAVParameter@@00@Z
// Condition 177 from the 0x0032D720 dispatcher: counts a player's team members whose +0x210
// module level exceeds its getContainCount (0x000347E3), optionally skipping 0x02000000 templates.
// stlport
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib

#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef unsigned short PlayerMaskType;

// Retail reaches these four members through incremental-link thunks, so the
// thunks are referenced directly instead of the stand-in member names.
extern void j_000230b5();
extern void j_0001dde5();
extern void j_000022bb();
extern void j_00022a70();

class Parameter
{
	public:
	unsigned char m_beforeInt[8];
	int m_int;
};

class ScriptEngine
{
};

class PlayerList
{
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeKind[0xd0 - 8];
	unsigned int m_kind;
};

class Rva0032C7F0Module
{
public:
	unsigned char m_beforeLevel[0x28];
	int m_level;
	void *m_nested;
};

// Pinned spelling of the 0x000347E3 getter; called on the +0x210 module.
class BfmeNamedContain
{
public:
	int getContainCount() const;
};


struct BfmePlayerTeamView { unsigned char m_beforeHead[0x0c]; Object *m_head; };
class BfmeTeamInstanceLink
{
};
class BfmePlayerTeamPrototypeInstances
{
public:
    unsigned char m_beforeInstances[0x274];
    BfmeTeamInstanceLink *m_teamInstanceList;
};

class Player
{
public:
    unsigned char m_beforeTeamList[0x288];
    std::list<BfmePlayerTeamPrototypeInstances *> m_playerTeamPrototypes;
};

template <class ObjectType>
class BfmePlayerDlinkIterator
{
public:
    typedef ObjectType *(ObjectType::*GetNextFunc)() const;
    BfmePlayerDlinkIterator(ObjectType *cur, GetNextFunc getNext)
        : m_cur(cur), m_getNext(getNext) { }
    Bool done() const { return m_cur == 0; }
    ObjectType *cur() const { return m_cur; }
    void advance() { if (m_cur) m_cur = (m_cur->*m_getNext)(); }
private:
    ObjectType *m_cur;
    GetNextFunc m_getNext;
};

// TU-local helper: hands the caller the pointer-to-member that the ILT thunk
// stands for, so the thunk address still materializes as an immediate.
typedef const Overridable *(Overridable::*FinalOverridePtr)() const;
static __forceinline FinalOverridePtr finalOverridePtr()
{
	typedef const Overridable *(Overridable::*Fn)() const;
	union { void (*fn)(); Fn call; } u = { j_000022bb };
	return u.call;
}

class ScriptConditions
{
protected:
	Bool rva0032C7F0(Parameter *playerParameter,
		Parameter *thresholdParameter, Parameter *includeHeroesParameter);
};

Bool ScriptConditions::rva0032C7F0(Parameter *playerParameter,
	Parameter *thresholdParameter, Parameter *includeHeroesParameter)
{
	typedef PlayerMaskType (ScriptEngine::*ScriptEngineMaskFn)(Parameter *);
	union { void (*fn)(); ScriptEngineMaskFn call; } scriptEngineMask = { j_000230b5 };
	typedef Player *(PlayerList::*PlayerListMaskFn)(PlayerMaskType);
	union { void (*fn)(); PlayerListMaskFn call; } playerListMask = { j_0001dde5 };

	int count;
	Player *player = (ThePlayerList->*playerListMask.call)(
		(TheScriptEngine->*scriptEngineMask.call)(playerParameter));
	if (player == 0)
		return false;

	count = 0;
	for (std::list<BfmePlayerTeamPrototypeInstances *>::iterator node =
		player->m_playerTeamPrototypes.begin();
		node != player->m_playerTeamPrototypes.end(); ++node)
	{
		typedef BfmeTeamInstanceLink *(BfmeTeamInstanceLink::*TeamInstanceNextFn)() const;
		union { void (*fn)(); TeamInstanceNextFn call; } teamInstanceNext = { j_00022a70 };
		BfmePlayerDlinkIterator<BfmeTeamInstanceLink> teams(
			(*node)->m_teamInstanceList,
			teamInstanceNext.call);
		for (; !teams.done(); teams.advance())
		{
			BfmePlayerTeamView *team =
                (BfmePlayerTeamView *)teams.cur();
			if (team == 0)
				continue;

			// The DLINK pointer-to-member needs a link-time constant member
			// address; this getter carries its own pin (symbols.csv,
			// route=0x000C8980) so the literal is 0x00401140 with no
			// linker alias needed.
			BfmePlayerDlinkIterator<Object> objects(
				team->m_head, &Object::dlink_next_TeamMemberList);
			for (; !objects.done(); objects.advance())
			{
				Object *object = objects.cur();
				if (object == 0)
					continue;
				if ((*((unsigned char *)object + 0x94) & 0x20) != 0)
					continue;

				if (includeHeroesParameter->m_int == 0)
				{
					ThingTemplate *thingTemplate = *(ThingTemplate **)((char *)object + 4);
					if (thingTemplate != 0 &&
						thingTemplate->m_nextOverride != 0)
					{
						thingTemplate = (ThingTemplate *)
							(thingTemplate->m_nextOverride->*finalOverridePtr())();
					}
					if ((thingTemplate->m_kind & 0x02000000) != 0)
						continue;
				}

				Rva0032C7F0Module *module = (Rva0032C7F0Module *)*(void **)((char *)object + 0x210);
				if (module != 0)
				{
					int level = module->m_level;
					if (level > ((BfmeNamedContain *)module)->getContainCount())
						++count;
				}
			}
		}
	}

	if (count >= thresholdParameter->m_int)
		return true;
	return false;
}