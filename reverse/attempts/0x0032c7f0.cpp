// ?rva0032C7F0@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.88 date=2026-09-23
// ?rva0032C7F0@ScriptConditions@@IAE_NPAVParameter@@00@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Parameter
{
	public:
	unsigned char m_beforeInt[8];
	int m_int;
};

class Object;

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

class BfmeObjectVbptrCarrierBase
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVbptrCarrierBase
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class RvaObjectDlinkBase
{
public:
	ThingTemplate *m_template;
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public RvaObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_beforeFlags[0x94 - 0x70];
	unsigned char m_flags94;
	unsigned char m_beforeModule[0x210 - 0x95];
	Rva0032C7F0Module *m_module210;
};

class Player
{
};

struct BfmePlayerTeamView
{
	unsigned char m_beforeHead[0x0c];
	Object *m_head;
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
	BfmePlayerTeamView *m_cur;
	int m_unmodelled;

	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head)
		: m_cur(head) { }
	Bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	BfmePlayerTeamPrototypeInstances *m_prototype;
};

struct BfmePlayerTeamListField
{
	unsigned char m_beforeHead[0x288];
	BfmePlayerTeamListNode *m_head;
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

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

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

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000347E3@Rva0032C7F0Module@@QBEHXZ=?j_000347e3@@YAXXZ")
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@RvaObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")

Bool ScriptConditions::rva0032C7F0(Parameter *playerParameter,
	Parameter *thresholdParameter, Parameter *includeHeroesParameter)
{
	int count;
	Player *player = ThePlayerList->getPlayerFromMask(
		TheScriptEngine->unidentified_0034DB40(playerParameter));
	if (player == 0)
		return false;

	count = 0;
	BfmePlayerTeamListNode *teamNode =
		((BfmePlayerTeamListField *)player)->m_head->m_next;
	if (teamNode != ((BfmePlayerTeamListField *)player)->m_head)
	{
		do
		{
		BfmePlayerTeamInstanceIterator teams(
			teamNode->m_prototype->m_teamInstanceList);
		for (; !teams.done(); teams.advance())
		{
			BfmePlayerTeamView *team = teams.cur();
			if (team == 0)
				continue;

			BfmePlayerDlinkIterator<Object> objects(
				team->m_head, &Object::dlink_next_TeamMemberList);
			for (; !objects.done(); objects.advance())
			{
				Object *object = objects.cur();
				if ((object->m_flags94 & 0x20) != 0)
					continue;

				if (includeHeroesParameter->m_int == 0)
				{
					ThingTemplate *thingTemplate = object->m_template;
					if (thingTemplate != 0 &&
						thingTemplate->m_nextOverride != 0)
					{
						thingTemplate = (ThingTemplate *)
							thingTemplate->m_nextOverride->getFinalOverride();
					}
					if ((thingTemplate->m_kind & 0x02000000) != 0)
						continue;
					}

				Rva0032C7F0Module *module = object->m_module210;
				if (module != 0)
				{
					int level = module->m_level;
					if (level > module->rva000347E3())
						++count;
				}
			}
		}
			teamNode = teamNode->m_next;
		} while (teamNode != ((BfmePlayerTeamListField *)player)->m_head);
	}

	return count >= thresholdParameter->m_int;
}
