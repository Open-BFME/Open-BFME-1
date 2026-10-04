// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?rva00326f40@ScriptConditions@@IAE_NPAVParameter@@000@Z
// Retail 0x00326F40: typed team walk and six-way integer comparison.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

#include "ascii_string.h"

// Retail reaches these bodies through incremental-link thunks; the call sites
// below name the thunk directly instead of a stand-in mangled name.
extern void j_00022a70();
extern void j_0003e80b();
extern void j_00028560();
extern void j_0003df4b();
extern void j_000239f2();

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	Int getInt() const { return m_int; }

private:
	UnsignedByte m_beforeInt[ 8 ];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class Player;
class ObjectTypes;

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString : public ScriptEngine
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
};

class PlayerList
{
public:
	Player *getPlayerFromMask( PlayerMaskType mask );
};

class BfmeThingFactory;
class ThingTemplate;



// findTemplate is reached through the ILT at 0x00028560; the call site below
// routes to that thunk through a pointer-to-member union.
class BfmeThingFactory
{
public:
};

class Overridable
{
public:
	virtual ~Overridable();
	// Retail calls the override walk through the ILT at 0x000022BB.  Routing
	// it through a thunk-typed pointer-to-member makes MSVC 7.1 materialise the
	// union and re-allocate this inlined getTemplate() chain, so the stand-in
	// name stays and the pragma at the foot of the file still supplies the
	// address.
	const Overridable *getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

// isEquivalentTo is reached through the ILT at 0x0003E80B.
class ThingTemplate : public Overridable
{
public:
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
	// Retail's DLINK iterator stores this as a link-time constant pointer to
	// member; no MSVC 7.1 cast can build that constant from a cdecl thunk, so
	// the stand-in name stays and the pragma below still supplies the address.
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	UnsignedByte m_pad[ 0x60 ];
};

// isInSet is reached through the ILT at 0x000239F2.
class ObjectTypes
{
public:
	virtual ~ObjectTypes();
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { if (m_types) delete m_types; }
	ObjectTypes *m_types;
};

class Rva00326F40Field210
{
public:
	UnsignedByte m_beforeValue[0x28];
	Int m_value;
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

	Rva00326F40Field210 *getField210() const
	{
		return *(Rva00326F40Field210 **)((const char *)this + 0x210);
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
			BfmeObjectDlinkBase::dlink_next_TeamMemberList );
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[ 0x274 ];
	BfmePlayerTeamView *m_teamInstanceList;
};

// _bfme_nextInInstanceList is reached through the ILT at 0x00022A70.
class BfmeTeamInstanceLink
{
public:
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
			typedef BfmeTeamInstanceLink *( BfmeTeamInstanceLink::*NextInstanceFn )();
			union { void (*fn)(); NextInstanceFn call; } nextInstance = { j_00022a70 };
			m_cur = ( BfmePlayerTeamView * )
				( ( ( BfmeTeamInstanceLink * )m_cur )->*nextInstance.call )();
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
	// objectTypesFromParam is reached through the ILT at 0x0003DF4B; the call
	// site below casts that thunk to the cdecl two-pointer prototype.
	Bool rva00326f40(Parameter *playerParameter, Parameter *typeParameter,
		Parameter *comparisonParameter, Parameter *countParameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
class ThingFactory;
extern ThingFactory *TheThingFactory;
static inline BfmeThingFactory *localThingFactory() { return (BfmeThingFactory *)TheThingFactory; }

Bool ScriptConditions::rva00326f40(
	Parameter *playerParameter, Parameter *typeParameter,
	Parameter *comparisonParameter, Parameter *countParameter)
{
	PlayerMaskType mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerParameter->getString(), 0);
	Player *player = ThePlayerList->getPlayerFromMask( mask );
	if( !player )
		return false;

	const ThingTemplate *wanted = 0;
	ObjectTypes *knownTypes = TheScriptEngine->getObjectTypes(typeParameter->getString());
	ObjectTypesTemp temporaryTypes;
	if (knownTypes)
	{
		typedef void ( __cdecl *ObjectTypesFromParamFn )( Parameter *, ObjectTypes * );
		( ( ObjectTypesFromParamFn )( void * )j_0003df4b )(
			typeParameter, temporaryTypes.m_types );
	}
	else
	{
		typedef const ThingTemplate *(
			BfmeThingFactory::*FindTemplateFn )( const AsciiString & );
		union { void (*fn)(); FindTemplateFn call; } findTemplate = { j_00028560 };
		wanted = ( localThingFactory()->*findTemplate.call )(
			typeParameter->getString() );
	}

	for( BfmePlayerTeamListNode *it =
			( ( BfmePlayerTeamListField * )player )->m_head->m_next;
		it != ( ( BfmePlayerTeamListField * )player )->m_head; it = it->m_next )
	{
		BfmePlayerTeamPrototypeInstances *prototype = it->m_prototype;
		BfmePlayerTeamInstanceIterator teams(
			prototype->m_teamInstanceList );
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

				Bool typeMatches;
				if (knownTypes)
				{
					typedef Bool (
						ObjectTypes::*IsInSetFn )( const ThingTemplate * ) const;
					union { void (*fn)(); IsInSetFn call; } isInSet = { j_000239f2 };
					typeMatches = (
						temporaryTypes.m_types->*isInSet.call )(object->getTemplate());
				}
				else
				{
					typedef Bool (
						ThingTemplate::*IsEquivalentToFn )( const ThingTemplate * ) const;
					union { void (*fn)(); IsEquivalentToFn call; } isEquivalentTo = { j_0003e80b };
					typeMatches = (
						object->getTemplate()->*isEquivalentTo.call )(wanted);
				}
				if (typeMatches)
				{
					Rva00326F40Field210 *field = object->getField210();
					if (field) {
						Int value = field->m_value;
						Bool matches = false;
						switch (comparisonParameter->getInt()) {
						case 0: matches = value < countParameter->getInt(); break;
						case 1: matches = value <= countParameter->getInt(); break;
						case 2: matches = value == countParameter->getInt(); break;
						case 3: matches = value >= countParameter->getInt(); break;
						case 4: matches = value > countParameter->getInt(); break;
						case 5: matches = value != countParameter->getInt(); break;
						}
						if (matches == 1) return true;
					}
				}
			}
		}
	}

	return false;
}

#pragma comment( linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVBfmePlayerObjectDlinkObject@@XZ=?j_00001140@@YAXXZ" )
#pragma comment( linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ" )
// The ObjectTypesTemp constructor stays stand-in-named too: dropping the
// declaration makes the local trivially constructed, and MSVC 7.1 then widens
// the frame by 0x10 and adds a redundant zero store before the constructor
// call, so the 0x00326F40 bytes no longer match.
#pragma comment( linker, "/alternatename:??0ObjectTypesTemp@@QAE@XZ=?j_0003e306@@YAXXZ" )
