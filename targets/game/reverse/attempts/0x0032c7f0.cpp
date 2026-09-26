// ?rva0032C7F0@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.89 date=2026-09-26
// stlport
// ?rva0032C7F0@ScriptConditions@@IAE_NPAVParameter@@00@Z
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib

#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Parameter
{
	public:
	unsigned char m_beforeInt[8];
	int m_int;
};

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

class PlayerList
{
public:
	class Player *getPlayerFromMask(PlayerMaskType mask);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

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
	unsigned char m_beforeKind[0xd0 - 8];
	unsigned int m_kind;
};

class Rva0032C7F0Module
{
public:
	unsigned char m_beforeLevel[0x28];
	int m_level;
	void *m_nested;

	int rva000347E3() const;
};


struct BfmePlayerTeamView { unsigned char m_beforeHead[0x0c]; Object *m_head; };
class BfmeTeamInstanceLink
{
public:
    BfmeTeamInstanceLink *_bfme_nextInInstanceList() const;
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

class ScriptConditions
{
protected:
	Bool rva0032C7F0(Parameter *playerParameter,
		Parameter *thresholdParameter, Parameter *includeHeroesParameter);
};

#pragma comment(linker, "/alternatename:?unidentified_0034DB40@ScriptEngine@@QAEGPAVParameter@@@Z=?j_000230b5@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPlayerFromMask@PlayerList@@QAEPAVPlayer@@G@Z=?j_0001dde5@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000347E3@Rva0032C7F0Module@@QBEHXZ=?j_000347e3@@YAXXZ")
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QBEPAV1@XZ=?j_00022a70@@YAXXZ")

Bool ScriptConditions::rva0032C7F0(Parameter *playerParameter,
	Parameter *thresholdParameter, Parameter *includeHeroesParameter)
{
	int count;
	Player *player = ThePlayerList->getPlayerFromMask(
		TheScriptEngine->unidentified_0034DB40(playerParameter));
	if (player == 0)
		return false;

	count = 0;
	for (std::list<BfmePlayerTeamPrototypeInstances *>::iterator node =
		player->m_playerTeamPrototypes.begin();
		node != player->m_playerTeamPrototypes.end(); ++node)
	{
		BfmePlayerDlinkIterator<BfmeTeamInstanceLink> teams(
			(*node)->m_teamInstanceList,
			&BfmeTeamInstanceLink::_bfme_nextInInstanceList);
		for (; !teams.done(); teams.advance())
		{
			BfmePlayerTeamView *team =
                (BfmePlayerTeamView *)teams.cur();
			if (team == 0)
				continue;

			BfmePlayerDlinkIterator<Object> objects(
				team->m_head, &Object::dlink_next_TeamMemberList);
			for (; !objects.done(); objects.advance())
			{
				Object *object = objects.cur();
				if ((*((unsigned char *)object + 0x94) & 0x20) != 0)
					continue;

				if (includeHeroesParameter->m_int == 0)
				{
					ThingTemplate *thingTemplate = *(ThingTemplate **)((char *)object + 4);
					if (thingTemplate != 0 &&
						thingTemplate->m_nextOverride != 0)
					{
						thingTemplate = (ThingTemplate *)
							thingTemplate->m_nextOverride->getFinalOverride();
					}
					if ((thingTemplate->m_kind & 0x02000000) != 0)
						continue;
					}

				Rva0032C7F0Module *module = (Rva0032C7F0Module *)*(void **)((char *)object + 0x210);
				if (module != 0)
				{
					int level = module->m_level;
					if (level > module->rva000347E3())
						++count;
				}
			}
		}
	}

	if (count >= thresholdParameter->m_int)
		return true;
	return false;
}
