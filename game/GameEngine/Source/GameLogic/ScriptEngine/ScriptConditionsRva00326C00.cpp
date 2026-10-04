// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00326C00 (carved). Twin of the landed
// ScriptConditionsEvaluateUnitHasToggledWeapon.cpp and of
// ScriptConditionsRva00326DA0.cpp: same player-mask -> player ->
// ThingTemplate resolution and the same three-level team walk (player
// team-list node -> BfmePlayerTeamInstanceIterator via
// _bfme_nextInInstanceList -> BfmePlayerDlinkIterator via
// dlink_next_TeamMemberList), but the per-object test calls
// Object::unidentified_001BFE20() (ObjectTeamAndPlayer.cpp, an opaque
// pointer forwarded from the contain module) and checks a virtual slot
// (vtable+0xD8) on the result instead of findSpecialAbilityUpdate.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

#include "ascii_string.h"

// Retail reaches each of the six callees below through its incremental-link
// thunk; every use spells the call as a code-address/member-pointer union so
// no linker alias stand-in is needed.
extern void j_00001140();
extern void j_00022a70();
extern void j_000022bb();
extern void j_0003e80b();
extern void j_00028560();
extern void j_0000d3b9();

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
public:
};

// Retail's BfmeThingFactory::findTemplate is reached through the
// incremental-link thunk at 0x00028560.
static __forceinline const ThingTemplate *findTemplate_thunk(
	BfmeThingFactory *self, const AsciiString &name )
{
	typedef const ThingTemplate *( BfmeThingFactory::*Fn )( const AsciiString & );
	union { void ( *fn )(); Fn call; } u = { j_00028560 };
	return ( self->*u.call )( name );
}

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
};

// Retail's Overridable::getFinalOverride inlines one level of the override
// walk at every use and reaches the rest through the incremental-link thunk
// at 0x000022bb.
static __forceinline const Overridable *getFinalOverride_thunk(
	const Overridable *self )
{
	if( self->m_nextOverride )
	{
		typedef const Overridable *( Overridable::*Fn )() const;
		union { void ( *fn )(); Fn call; } u = { j_000022bb };
		return ( self->m_nextOverride->*u.call )();
	}
	return self;
}

class ThingTemplate : public Overridable
{
public:
};

// Retail's ThingTemplate::isEquivalentTo is reached through the
// incremental-link thunk at 0x0003e80b.
static __forceinline Bool isEquivalentTo_thunk(
	const ThingTemplate *self, const ThingTemplate *other )
{
	typedef Bool ( ThingTemplate::*Fn )( const ThingTemplate * ) const;
	union { void ( *fn )(); Fn call; } u = { j_0003e80b };
	return ( self->*u.call )( other );
}

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		if( !m_overridable )
			return 0;
		return ( const T * )getFinalOverride_thunk( m_overridable );
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

// Retail's BfmeObjectDlinkBase::dlink_next_TeamMemberList is reached through
// the incremental-link thunk at 0x00001140; the iterator below keeps that
// code address as its member pointer and calls it indirectly.
typedef BfmePlayerObjectDlinkObject *(
	BfmeObjectDlinkBase::*BfmeTeamMemberNextFn )() const;

static __forceinline BfmeTeamMemberNextFn nextTeamMemberList_thunk()
{
	union { void ( *fn )(); BfmeTeamMemberNextFn call; } u = { j_00001140 };
	return u.call;
}

class BfmeObjectDlinkPad
{
public:
	UnsignedByte m_pad[ 0x60 ];
};

// unidentified_001BFE20 (ObjectTeamAndPlayer.cpp) returns an opaque pointer
// whose own vtable slot 0x36 (0xD8/4) this body probes; identity of both
// the pointee and the checked slot are unrecovered (address-derived).
class Rva00326C00FoundSlot36
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09(); virtual void _pad0a(); virtual void _pad0b();
	virtual void _pad0c(); virtual void _pad0d(); virtual void _pad0e();
	virtual void _pad0f(); virtual void _pad10(); virtual void _pad11();
	virtual void _pad12(); virtual void _pad13(); virtual void _pad14();
	virtual void _pad15(); virtual void _pad16(); virtual void _pad17();
	virtual void _pad18(); virtual void _pad19(); virtual void _pad1a();
	virtual void _pad1b(); virtual void _pad1c(); virtual void _pad1d();
	virtual void _pad1e(); virtual void _pad1f(); virtual void _pad20();
	virtual void _pad21(); virtual void _pad22(); virtual void _pad23();
	virtual void _pad24(); virtual void _pad25(); virtual void _pad26();
	virtual void _pad27(); virtual void _pad28(); virtual void _pad29();
	virtual void _pad2a(); virtual void _pad2b(); virtual void _pad2c();
	virtual void _pad2d(); virtual void _pad2e(); virtual void _pad2f();
	virtual void _pad30(); virtual void _pad31(); virtual void _pad32();
	virtual void _pad33(); virtual void _pad34(); virtual void _pad35();
	virtual Bool slot36();
};

// unidentified_001BFE20 (ObjectTeamAndPlayer.cpp) is reached through the
// incremental-link thunk at 0x0000d3b9. The object class has a virtual base,
// so cl cannot fold a member pointer onto a plain code address for it; the
// call is spelled on this ABI-neutral carrier (no bases, no vtable) instead,
// which folds to the same `mov ecx,object; call j_0000d3b9`.
class Rva00326C00ThunkCarrier
{
public:
};

static __forceinline Rva00326C00FoundSlot36 *unidentified_001BFE20_thunk(
	BfmePlayerObjectDlinkObject *self )
{
	typedef Rva00326C00FoundSlot36 *( Rva00326C00ThunkCarrier::*Fn )() const;
	union { void ( *fn )(); Fn call; } u = { j_0000d3b9 };
	return ( ( ( Rva00326C00ThunkCarrier * )self )->*u.call )();
}

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

class BfmePlayerTeamView
{
public:
	UnsignedByte m_unmodelled_000[ 0x0c ];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>
	iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>( m_head,
			nextTeamMemberList_thunk() );
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[ 0x274 ];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmeTeamInstanceLink
{
public:
};

// Retail's BfmeTeamInstanceLink::_bfme_nextInInstanceList is reached through
// the incremental-link thunk at 0x00022a70.
static __forceinline BfmeTeamInstanceLink *nextInInstanceList_thunk(
	BfmeTeamInstanceLink *self )
{
	typedef BfmeTeamInstanceLink *( BfmeTeamInstanceLink::*Fn )();
	union { void ( *fn )(); Fn call; } u = { j_00022a70 };
	return ( self->*u.call )();
}

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator( BfmePlayerTeamView *head ) : m_cur( head ) { }

	Bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if( m_cur )
			m_cur = ( BfmePlayerTeamView * )
				nextInInstanceList_thunk( ( BfmeTeamInstanceLink * )m_cur );
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
	Bool rva00326c00( Parameter *playerParameter, Parameter *templateParameter );
};

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory`; this
// TU keeps its own BfmeThingFactory ABI view and casts at the use.
class ThingFactory;

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;

Bool ScriptConditions::rva00326c00(
	Parameter *playerParameter, Parameter *templateParameter )
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40( playerParameter );
	Player *player = ThePlayerList->getPlayerFromMask( mask );
	if( !player )
		return false;

	const ThingTemplate *wanted = findTemplate_thunk(
		( BfmeThingFactory * )TheThingFactory,
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

				if( isEquivalentTo_thunk( object->getTemplate(), wanted ) )
				{
					Rva00326C00FoundSlot36 *found =
						unidentified_001BFE20_thunk( object );
					if( found && !found->slot36() )
						return true;
				}
			}
		}
	}

	return false;
}

