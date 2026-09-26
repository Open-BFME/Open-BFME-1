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

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	Bool isInSet(const ThingTemplate *thing) const;
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
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
	Bool rva00326f40(Parameter *playerParameter, Parameter *typeParameter,
		Parameter *comparisonParameter, Parameter *countParameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeThingFactory *TheThingFactory;

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
		objectTypesFromParam(typeParameter, temporaryTypes.m_types);
	else
		wanted = TheThingFactory->findTemplate(typeParameter->getString());

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
					typeMatches = temporaryTypes.m_types->isInSet(object->getTemplate());
				else
					typeMatches = object->getTemplate()->isEquivalentTo(wanted);
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
#pragma comment( linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ" )
#pragma comment( linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ" )
#pragma comment( linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ" )
#pragma comment( linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ" )
#pragma comment( linker, "/alternatename:??0ObjectTypesTemp@@QAE@XZ=?j_0003e306@@YAXXZ" )
#pragma comment( linker, "/alternatename:?objectTypesFromParam@ScriptConditions@@KAXPAVParameter@@PAVObjectTypes@@@Z=?j_0003df4b@@YAXXZ" )
#pragma comment( linker, "/alternatename:?isInSet@ObjectTypes@@QBE_NPBVThingTemplate@@@Z=?j_000239f2@@YAXXZ" )
