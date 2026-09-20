// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
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
	const ThingTemplate *findTemplate( const AsciiString &name );
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo( const ThingTemplate *other ) const;
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
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

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

	Rva00326C00FoundSlot36 *unidentified_001BFE20() const;
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
			BfmeObjectDlinkBase::dlink_next_TeamMemberList );
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
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
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
			m_cur = ( BfmePlayerTeamView * )
				( ( BfmeTeamInstanceLink * )m_cur )->_bfme_nextInInstanceList();
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

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeThingFactory *TheThingFactory;

Bool ScriptConditions::rva00326c00(
	Parameter *playerParameter, Parameter *templateParameter )
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40( playerParameter );
	Player *player = ThePlayerList->getPlayerFromMask( mask );
	if( !player )
		return false;

	const ThingTemplate *wanted = TheThingFactory->findTemplate(
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

				if( object->getTemplate()->isEquivalentTo( wanted ) )
				{
					Rva00326C00FoundSlot36 *found = object->unidentified_001BFE20();
					if( found && !found->slot36() )
						return true;
				}
			}
		}
	}

	return false;
}

#pragma comment( linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVBfmePlayerObjectDlinkObject@@XZ=?j_00001140@@YAXXZ" )
#pragma comment( linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ" )
#pragma comment( linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ" )
#pragma comment( linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ" )
#pragma comment( linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ" )
#pragma comment( linker, "/alternatename:?unidentified_001BFE20@BfmePlayerObjectDlinkObject@@QBEPAVRva00326C00FoundSlot36@@XZ=?j_0000d3b9@@YAXXZ" )
