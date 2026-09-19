// ?evaluateUnitHasToggledWeapon@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.91 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// ScriptConditions::evaluateUnitHasToggledWeapon at retail RVA 0x0032CB00.
// The condition table names slot 180 UNIT_HAS_TOGGLED_WEAPON. Its two
// parameters select the player and the ThingTemplate to compare.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	UnsignedByte m_beforeString[0x10];
	AsciiString m_string;
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

class BfmeThingFactory;
class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

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
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		Overridable *raw = (Overridable *)m_overridable;
		const T *value;
		if (raw != 0) {
			Overridable *next = raw->m_nextOverride;
			if (next != 0)
				raw = (Overridable *)next->getFinalOverride();
			value = (const T *)raw;
		} else {
			value = 0;
		}
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectVirtualTail
{
public:
	UnsignedByte m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	UnsignedByte m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmePlayerObjectDlinkObject;

class BfmeObjectDlinkBase
{
public:
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	UnsignedByte m_pad[0x60];
};

class BfmePlayerObjectDlinkObject : public BfmeObjectVtbl,
	public BfmeObjectDlinkBase, public BfmeObjectDlinkPad,
	public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

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
			m_cur = callMemberFunction(*m_cur, m_getNext)();
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
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[0x274];
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

class Gen_001C4990
{
public:
	Int bfmeHasBit(Int bit) const;
};

class BfmeObjectStatusView
{
public:
	UnsignedByte m_beforeStatus[0x98];
	UnsignedInt m_status;
};

class ScriptConditions
{
protected:
	Bool evaluateUnitHasToggledWeapon(Parameter *playerParameter,
		Parameter *templateParameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeThingFactory *TheThingFactory;

// ?evaluateUnitHasToggledWeapon@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateUnitHasToggledWeapon(
	Parameter *playerParameter, Parameter *templateParameter)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	const ThingTemplate *wanted = TheThingFactory->findTemplate(
		templateParameter->getString());
	if (!wanted)
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

				if (object->getTemplate()->isEquivalentTo(wanted))
				{
					Gen_001C4990 *flags = (Gen_001C4990 *)object;
					if (flags->bfmeHasBit(0x18) ||
						flags->bfmeHasBit(0x19) ||
						flags->bfmeHasBit(0x1a) ||
						(((BfmeObjectStatusView *)object)->m_status & 0x10000) != 0)
						return true;
				}
			}
		}
	}

	return false;
}
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVBfmePlayerObjectDlinkObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeHasBit@Gen_001C4990@@QBEHH@Z=?j_000225f7@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
