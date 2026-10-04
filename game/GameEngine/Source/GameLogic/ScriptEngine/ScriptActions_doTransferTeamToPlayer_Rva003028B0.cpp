// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
//
// ScriptActions::doTransferTeamToPlayer, retail RVA 0x003028B0 (303 bytes).
// The executeAction TEAM_TRANSFER_TO_PLAYER arm at 0x00303BF0 supplies the
// team and player names.  The retail action changes the team's controller,
// refreshes each member through the existing bfmeHelper760 visitor, then
// stops transport members and idles their AI after the ownership change.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

class Player;
class Object;

// Retail reaches each of the operations below through the already-emitted
// image thunks (ILT stubs), so the callsites name the thunk directly through
// a local pointer/member-pointer view instead of a neutral ledger identity
// for the generated callee.
extern void j_00001140();
extern void j_000022bb();
extern void j_00024d70();
extern void j_00025806();
extern void j_0002ae5f();
extern void j_0002dc1d();
extern void j_00030a21();
extern void j_0003b15b();

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xcc];
	UnsignedInt m_kindOf; // retail ThingTemplate+0xd4
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
		{
			// Retail calls this through the ILT thunk at 0x000022bb.
			union
			{
				void (*fn)();
				const Overridable *(Overridable::*call)() const;
			} u;
			u.fn = j_000022bb;
			value = (const T *)((value->m_nextOverride->*u.call)());
		}
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	BfmeOverride<ThingTemplate> m_template; // retail Object+0x04
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0() = 0;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60]; // retail Object+0x08 through +0x67
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

// The inherited vbptr at Object+0x68 is part of the retail DLINK
// pointer-to-member representation: {0x00401140, -100, 0}.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

#include "../command_source_type.h"

class AICommandInterface
{
public:
};

class BfmeAIUpdateView
{
public:
	unsigned char m_unmodelled_00[0x20];
	AICommandInterface m_command;
};

class BfmeThingXV
{
public:
};

// Flat receiver view for the address-named Object operation retail reaches
// through the image thunk at 0x0002AE5F.  Object itself carries a virtual
// base, and a member pointer taken on it makes the compiler emit a vbtable
// adjustment that retail's direct thiscall does not have.
class BfmeRva001CA2E0Receiver
{
public:
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	unsigned char m_unmodelled_70[0x194];
	BfmeAIUpdateView *m_ai; // retail Object+0x204
	unsigned char m_unmodelled_208[0x0c];
	Object *m_containedBy; // retail Object+0x214
};

typedef int (__cdecl *BfmeObjectVisitor)(void *, int);

class Rva000EDAB0VisitOwner {};
typedef int (Rva000EDAB0VisitOwner::*Rva000EDAB0Visit)(BfmeObjectVisitor, int);

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

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
	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		// Retail walks the list through the image thunk at 0x00001140.  The
		// pointer-to-member is folded to retail's {0x00401140, -100, 0}: the
		// -100 is the virtual-base adjustment the compiler derives from
		// Object's geometry, and the code slot takes the thunk's address.
		union
		{
			void (*fn)();
			Object *(BfmeObjectDlinkBase::*next)() const;
		} u;
		u.fn = j_00001140;
		return BfmeDlinkIterator<Object>(m_head, u.next);
	}

private:
	unsigned char m_unmodelled_000[0x0c];
	Object *m_head; // retail Team+0x0c
};

class ScriptEngine
{
public:
	virtual void _0() = 0; virtual void _1() = 0;
	virtual void _2() = 0; virtual void _3() = 0;
	virtual void _4() = 0; virtual void _5() = 0;
	virtual void _6() = 0; virtual void _7() = 0;
	virtual void _8() = 0; virtual void _9() = 0;
	virtual void _10() = 0; virtual void _11() = 0;
	virtual void _12() = 0; virtual void _13() = 0;
	virtual void _14() = 0; virtual void _15() = 0;
	virtual void _16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *outSpecialName);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern int __cdecl bfmeHelper760(void *object, int userData);


// The named Team::setControllingPlayer implementation is present-unmatched
// at body 0x000F44C0.  Retail reaches it through the existing ILT/thunk at
// 0x00030A21; this local member-pointer type preserves its thiscall ABI
// without claiming a new symbol pin for the ILT.
typedef void (Team::*SetControllingPlayerThunk)(Player *);

class ScriptActions
{
protected:
	void doTransferTeamToPlayer(const AsciiString &teamName,
		const AsciiString &playerName);
};

void ScriptActions::doTransferTeamToPlayer(const AsciiString &teamName,
	const AsciiString &playerName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	PlayerMaskType playerMask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerName, 0);
	Player *playerDest = ThePlayerList->getEachPlayerFromMask(playerMask);
	if (!(theTeam && playerDest))
		return;

	union
	{
		void *asVoid;
		SetControllingPlayerThunk asMember;
	} setController;
	setController.asVoid = (void *)j_00030a21;
	(theTeam->*setController.asMember)(playerDest);
	// The inner walker tests the callback's integer status.  Keep the
	// existing callback's real cdecl signature through this raw ABI view.
	union
	{
		void *asVoid;
		Rva000EDAB0Visit asMember;
	} visit;
	visit.asVoid = (void *)j_0002dc1d;
	(((Rva000EDAB0VisitOwner *)theTeam)->*visit.asMember)(bfmeHelper760, 0);

	// Retail dispatches the three per-member commands through the image
	// thunks at 0x00025806, 0x0002ae5f and 0x00024d70; each view keeps the
	// thunk's real thiscall shape while naming the thunk directly.
	union
	{
		void (*fn)();
		void (BfmeThingXV::*stopXV)();
	} stopXV;
	stopXV.fn = j_00025806;
	typedef void (BfmeRva001CA2E0Receiver::*StopPath)();
	union
	{
		void (*fn)();
		StopPath stopPath;
	} stopPath;
	stopPath.fn = j_0002ae5f;
	union
	{
		void (*fn)();
		void (AICommandInterface::*idle)(CommandSourceType);
	} idle;
	idle.fn = j_00024d70;

	BfmeDlinkIterator<Object> iter = theTeam->iterate_TeamMemberList();
	while (!iter.done())
	{
		Object *object = iter.cur();
		Object *containedBy = object->m_containedBy;
		if (containedBy)
		{
			const ThingTemplate *tmpl = containedBy->getTemplate();
			if (tmpl->m_kindOf & 0x1000)
			{
				(((BfmeThingXV *)containedBy)->*stopXV.stopXV)();
				(((BfmeRva001CA2E0Receiver *)containedBy)->*stopPath.stopPath)();
				BfmeAIUpdateView *ai = containedBy->m_ai;
				if (ai)
					(ai->m_command.*idle.idle)(CMD_FROM_AI);
			}
		}

		(((BfmeThingXV *)object)->*stopXV.stopXV)();
		(((BfmeRva001CA2E0Receiver *)object)->*stopPath.stopPath)();
		BfmeAIUpdateView *ai = object->m_ai;
		if (ai)
			(ai->m_command.*idle.idle)(CMD_FROM_AI);

		iter.advance();
	}

	// Retail calls this through the image thunk at 0x0003b15b.
	union
	{
		void (*fn)();
		void (ScriptEngine::*notify)();
	} notify;
	notify.fn = j_0003b15b;
	(TheScriptEngine->*notify.notify)();
}
