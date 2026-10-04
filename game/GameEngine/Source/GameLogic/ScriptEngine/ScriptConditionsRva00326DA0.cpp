// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00326DA0 (carved). Twin of the landed
// ScriptConditionsEvaluateUnitHasToggledWeapon.cpp: same player-mask ->
// player -> ThingTemplate resolution and the same three-level team walk
// (player team-list node -> BfmePlayerTeamInstanceIterator via
// _bfme_nextInInstanceList -> BfmePlayerDlinkIterator via
// dlink_next_TeamMemberList), but the per-object test calls
// Object::findSpecialAbilityUpdate(0x27) and checks a virtual slot on the
// result instead of the status-bit family.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

#include "ascii_string.h"

// Retail's callers reach these bodies through incremental-link thunks, so this
// TU names the thunk addresses directly instead of the owning member.
extern void j_00001140();
extern void j_00022a70();
extern void j_000022bb();
extern void j_0003e80b();
extern void j_00028560();
extern void j_0004b4fc();

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	UnsignedByte m_beforeString[ 0x10 ];
	AsciiString m_string;
};

class Player;

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40( Parameter *parameter );
};

class PlayerList
{
public:
	Player *getPlayerFromMask( PlayerMaskType mask );
};

class BfmeThingFactory;
class ThingTemplate;



class BfmeThingFactory
{
};

// Retail's TU inlines one recursion frame of getFinalOverride (the
// m_nextOverride test stays at the call site) and reaches the recursive step
// through the ILT thunk at 0x000022BB, so the thunk is a separate name here.
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverrideThunk();
		return this;
	}

	const Overridable *getFinalOverrideThunk() const
	{
		typedef const Overridable *( Overridable::*GetFinalOverride )() const;
		union { void ( *fn )(); GetFinalOverride call; } getFinalOverride =
			{ j_000022bb };
		return ( this->*getFinalOverride.call )();
	}

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		if( !m_overridable )
			return 0;
		return ( const T * )m_overridable->getFinalOverride();
	}

	const T *m_overridable;
};

class BfmeObjectVirtualTail
{
public:
	UnsignedByte m_vt[ 4 ];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	UnsignedByte m_carrier[ 4 ];
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
	UnsignedByte m_pad[ 0x60 ];
};

class SpecialAbilityUpdateSlot20
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Bool slot08();
};

class SpecialAbilityUpdateView
{
public:
	SpecialAbilityUpdateSlot20 *asSlot20()
	{
		return ( SpecialAbilityUpdateSlot20 * )( ( char * )this + 0x20 );
	}
};

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
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

#define callMemberFunction( object, ptrToMember ) ( ( object ).*( ptrToMember ) )

template <class ObjectType>
class BfmePlayerDlinkIterator
{
public:
	typedef ObjectType *( ObjectType::*GetNextFunc )() const;

	BfmePlayerDlinkIterator( ObjectType *cur, GetNextFunc getNext )
		: m_cur( cur ), m_getNext( getNext )
	{
	}

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if( m_cur )
			m_cur = callMemberFunction( *m_cur, m_getNext )();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

// Retail's TeamMemberList step goes through the ILT at 0x00001140, so the
// iterator's getNext member pointer is that address in a derived-base
// adjustment pair rather than a real BfmeObjectDlinkBase member.
typedef BfmePlayerObjectDlinkObject *( BfmeObjectDlinkBase::*GetNext0026DA0 )()
	const;

static __forceinline GetNext0026DA0 getNext0026DA0()
{
	union { void ( *fn )(); GetNext0026DA0 call; } u = { j_00001140 };
	return u.call;
}

// Retail calls the ThingTemplate comparison and the special-ability lookup
// straight through their ILT thunks; each thunk lives in its own helper so
// MSVC 7.1 folds it into a plain call instead of an indirect one.
static __forceinline Bool isEquivalentTo0026DA0(
	const ThingTemplate *self, const ThingTemplate *other )
{
	typedef Bool ( ThingTemplate::*IsEquivalentTo )(
		const ThingTemplate * ) const;
	union { void ( *fn )(); IsEquivalentTo call; } u = { j_0003e80b };
	return ( self->*u.call )( other );
}

// A non-virtually-derived carrier keeps MSVC 7.1 from emitting a vbase-offset
// lookup at the call; retail passes `object` straight in ecx.
struct SpecialAbilityLookup0026DA0
{
	typedef SpecialAbilityUpdateView *( SpecialAbilityLookup0026DA0::*Lookup )(
		int ) const;
};

static __forceinline SpecialAbilityUpdateView *findSpecialAbilityUpdate0026DA0(
	const BfmePlayerObjectDlinkObject *self, int type )
{
	union { void ( *fn )(); SpecialAbilityLookup0026DA0::Lookup call; } u =
		{ j_0004b4fc };
	return ( ( ( SpecialAbilityLookup0026DA0 * )self )->*u.call )( type );
}

class BfmePlayerTeamView
{
public:
	UnsignedByte m_unmodelled_000[ 0x0c ];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>
	iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>( m_head,
			getNext0026DA0() );
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[ 0x274 ];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmeTeamInstanceLink
{
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator( BfmePlayerTeamView *head ) : m_cur( head ) { }

	Bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if( m_cur )
		{
			typedef BfmeTeamInstanceLink *( BfmeTeamInstanceLink::*Next )();
			union { void ( *fn )(); Next call; } nextInInstanceList =
				{ j_00022a70 };
			m_cur = ( BfmePlayerTeamView * )
				( ( ( BfmeTeamInstanceLink * )m_cur )->*nextInInstanceList.call )();
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
	UnsignedByte m_unmodelled_000[ 0x288 ];
	BfmePlayerTeamListNode *m_head;
};

class ScriptConditions
{
protected:
	Bool rva00326da0( Parameter *playerParameter, Parameter *templateParameter );
};

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory`; this
// TU keeps its own BfmeThingFactory ABI view and casts at the use.
class ThingFactory;

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;

Bool ScriptConditions::rva00326da0(
	Parameter *playerParameter, Parameter *templateParameter )
{
	typedef const ThingTemplate *( BfmeThingFactory::*FindTemplate )(
		const AsciiString & );
	union { void ( *fn )(); FindTemplate call; } findTemplate =
		{ j_00028560 };

	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40( playerParameter );
	Player *player = ThePlayerList->getPlayerFromMask( mask );
	if( !player )
		return false;

	const ThingTemplate *wanted =
		( ( ( BfmeThingFactory * )TheThingFactory )->*findTemplate.call )(
		templateParameter->getString() );
	if( !wanted )
		return false;

	for( BfmePlayerTeamListNode *it =
			( ( BfmePlayerTeamListField * )player )->m_head->m_next;
		it != ( ( BfmePlayerTeamListField * )player )->m_head; it = it->m_next )
	{
		BfmePlayerTeamInstanceIterator teams(
			it->m_prototype->m_teamInstanceList );
		for( ; !teams.done(); teams.advance() )
		{
			BfmePlayerTeamView *team = teams.cur();
			if( !team )
				continue;

			BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> objects =
				team->iterate_TeamMemberList();
			for( ; !objects.done(); objects.advance() )
			{
				BfmePlayerObjectDlinkObject *object = objects.cur();
				if( !object )
					continue;

				if( isEquivalentTo0026DA0( object->getTemplate(), wanted ) )
				{
					SpecialAbilityUpdateView *ability =
						findSpecialAbilityUpdate0026DA0( object, 0x27 );
					if( ability && ability->asSlot20()->slot08() )
						return true;
				}
			}
		}
	}

	return false;
}


