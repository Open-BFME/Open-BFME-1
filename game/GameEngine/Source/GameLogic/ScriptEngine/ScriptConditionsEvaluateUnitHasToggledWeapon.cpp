// ?evaluateUnitHasToggledWeapon@ScriptConditions@@IAE_NPAVParameter@@0@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// ScriptConditions::evaluateUnitHasToggledWeapon at retail RVA 0x0032CB00.
// The condition table names slot 180 UNIT_HAS_TOGGLED_WEAPON. Its two
// parameters select the player and the ThingTemplate to compare.

#include "ascii_string.h"

// Retail's incremental-link thunks. Each retail call site in this body goes
// straight to one of these 5-byte ILT stubs, so the call targets are named
// here directly instead of through a stand-in member function.
extern void j_00001140();
extern void j_00022a70();
extern void j_0003e80b();
extern void j_000225f7();
extern void j_00028560();

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
};

// The recursive call below is the only self-reference, so this TU emits its own
// 26-byte copy of the body; no link-time name mapping is needed for it.
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
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
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

	const T *m_overridable;
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
		typedef BfmePlayerObjectDlinkObject *(BfmeObjectDlinkBase::*GetNextFunc)()
			const;
		union { void (*fn)(); GetNextFunc call; } u = { j_00001140 };
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			u.call);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmeTeamInstanceLink
{
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
		{
			typedef BfmeTeamInstanceLink *(BfmeTeamInstanceLink::*Call)();
			union { void (*fn)(); Call call; } u = { j_00022a70 };
			m_cur = (BfmePlayerTeamView *)
				(((BfmeTeamInstanceLink *)m_cur)->*u.call)();
		}
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
};

// Retail reaches the bit test three times through ILT thunk 0x000225F7.
static __forceinline Bool bfmeHasBitThunk(Gen_001C4990 *self, Int bit)
{
	typedef Bool (Gen_001C4990::*Call)(Int) const;
	union { void (*fn)(); Call call; } u = { j_000225f7 };
	return (self->*u.call)(bit);
}

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

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory`; this
// TU keeps its own BfmeThingFactory ABI view and casts at the use.
class ThingFactory;

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;

// ?evaluateUnitHasToggledWeapon@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateUnitHasToggledWeapon(
	Parameter *playerParameter, Parameter *templateParameter)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	typedef const ThingTemplate *(BfmeThingFactory::*FindTemplate)(
		const AsciiString &);
	union { void (*fn)(); FindTemplate call; } find = { j_00028560 };
	const ThingTemplate *wanted =
		(((BfmeThingFactory *)TheThingFactory)->*find.call)(
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

				typedef Bool (ThingTemplate::*IsEquivalentTo)(
					const ThingTemplate *) const;
				union { void (*fn)(); IsEquivalentTo call; } equiv =
					{ j_0003e80b };
				if ((*(object->getTemplate()).*equiv.call)(wanted))
				{
					Gen_001C4990 *flags = (Gen_001C4990 *)object;
					if (bfmeHasBitThunk(flags, 0x18) ||
						bfmeHasBitThunk(flags, 0x19) ||
						bfmeHasBitThunk(flags, 0x1a) ||
						(((BfmeObjectStatusView *)object)->m_status & 0x10000) != 0)
						return true;
				}
			}
		}
	}

	return false;
}
