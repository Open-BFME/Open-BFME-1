// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/GameLogic/Object /ICode/GameEngine/Source/Common/Thing /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Condition registration names this condition PLAYER_HAS_NUM_UNITS_LOADED_WITH_OBJECT.
// Dispatcher case 179 calls retail RVA 0x003269C0 with four Parameter pointers.
// Retail reads Object::m_contain and ContainModuleInterface slot 65 to count loaded template matches.
// Local list and iterator views describe the retail walks through team prototypes and team members.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
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

#define THING_TU_MEMBERS \
	const ThingTemplate *getTemplate() const \
	{ \
		if (!m_template) return 0; \
		return static_cast<const ThingTemplate *>(m_template->getFinalOverride()); \
	}
#include "object.h"

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

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	UnsignedByte m_pad[ 0x60 ];
};

class Rva003269C0DlinkObjectView : public BfmeObjectVtbl,
	public BfmeObjectDlinkBase, public BfmeObjectDlinkPad,
	public BfmeObjectVbptrCarrier
{
};

#define callMemberFunction( object, ptrToMember ) ( ( object ).*( ptrToMember ) )

template <class ObjectType>
class BfmePlayerDlinkIterator
{
public:
	typedef Object *( ObjectType::*GetNextFunc )() const;

	BfmePlayerDlinkIterator( ObjectType *cur, GetNextFunc getNext )
		: m_cur( cur ), m_getNext( getNext )
	{
	}

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if( m_cur )
			m_cur = ( ObjectType * )callMemberFunction( *m_cur, m_getNext )();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class Rva003269C0TeamInstanceView
{
public:
	UnsignedByte m_unmodelled_000[ 0x0c ];
	Rva003269C0DlinkObjectView *m_head;

	BfmePlayerDlinkIterator<Rva003269C0DlinkObjectView>
	iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<Rva003269C0DlinkObjectView>( m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList );
	}
};

struct Rva003269C0PlayerTeamPrototypeView
{
	UnsignedByte m_unmodelled_000[ 0x274 ];
	Rva003269C0TeamInstanceView *m_teamInstanceList;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Rva003269C0TeamInstanceIterator
{
public:
	Rva003269C0TeamInstanceIterator( Rva003269C0TeamInstanceView *head ) : m_cur( head ) { }

	Bool done() const { return m_cur == 0; }
	Rva003269C0TeamInstanceView *cur() const { return m_cur; }

	void advance()
	{
		if( m_cur )
			m_cur = ( Rva003269C0TeamInstanceView * )
				( ( BfmeTeamInstanceLink * )m_cur )->_bfme_nextInInstanceList();
	}

private:
	Rva003269C0TeamInstanceView *m_cur;
	Int m_unmodelled;
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	Rva003269C0PlayerTeamPrototypeView *m_prototype;
};

struct BfmePlayerTeamListField
{
	UnsignedByte m_unmodelled_000[ 0x288 ];
	BfmePlayerTeamListNode *m_head;
};


typedef std::list<Object *> ContainedItemsList;

#define BFME_CONTAIN_SLOT(N) virtual void slot##N();
class ContainModuleInterface
{
public:
		BFME_CONTAIN_SLOT(0) BFME_CONTAIN_SLOT(1) BFME_CONTAIN_SLOT(2) BFME_CONTAIN_SLOT(3) BFME_CONTAIN_SLOT(4) BFME_CONTAIN_SLOT(5)
	BFME_CONTAIN_SLOT(6) BFME_CONTAIN_SLOT(7) BFME_CONTAIN_SLOT(8) BFME_CONTAIN_SLOT(9) BFME_CONTAIN_SLOT(10) BFME_CONTAIN_SLOT(11)
	BFME_CONTAIN_SLOT(12) BFME_CONTAIN_SLOT(13) BFME_CONTAIN_SLOT(14) BFME_CONTAIN_SLOT(15) BFME_CONTAIN_SLOT(16) BFME_CONTAIN_SLOT(17)
	BFME_CONTAIN_SLOT(18) BFME_CONTAIN_SLOT(19) BFME_CONTAIN_SLOT(20) BFME_CONTAIN_SLOT(21) BFME_CONTAIN_SLOT(22) BFME_CONTAIN_SLOT(23)
	BFME_CONTAIN_SLOT(24) BFME_CONTAIN_SLOT(25) BFME_CONTAIN_SLOT(26) BFME_CONTAIN_SLOT(27) BFME_CONTAIN_SLOT(28) BFME_CONTAIN_SLOT(29)
	BFME_CONTAIN_SLOT(30) BFME_CONTAIN_SLOT(31) BFME_CONTAIN_SLOT(32) BFME_CONTAIN_SLOT(33) BFME_CONTAIN_SLOT(34) BFME_CONTAIN_SLOT(35)
	BFME_CONTAIN_SLOT(36) BFME_CONTAIN_SLOT(37) BFME_CONTAIN_SLOT(38) BFME_CONTAIN_SLOT(39) BFME_CONTAIN_SLOT(40) BFME_CONTAIN_SLOT(41)
	BFME_CONTAIN_SLOT(42) BFME_CONTAIN_SLOT(43) BFME_CONTAIN_SLOT(44) BFME_CONTAIN_SLOT(45) BFME_CONTAIN_SLOT(46) BFME_CONTAIN_SLOT(47)
	BFME_CONTAIN_SLOT(48) BFME_CONTAIN_SLOT(49) BFME_CONTAIN_SLOT(50) BFME_CONTAIN_SLOT(51) BFME_CONTAIN_SLOT(52) BFME_CONTAIN_SLOT(53)
	BFME_CONTAIN_SLOT(54) BFME_CONTAIN_SLOT(55) BFME_CONTAIN_SLOT(56) BFME_CONTAIN_SLOT(57) BFME_CONTAIN_SLOT(58) BFME_CONTAIN_SLOT(59)
	BFME_CONTAIN_SLOT(60) BFME_CONTAIN_SLOT(61) BFME_CONTAIN_SLOT(62) BFME_CONTAIN_SLOT(63) BFME_CONTAIN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const;
};
#undef BFME_CONTAIN_SLOT

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasNumUnitsLoadedWithObject(
		Parameter *playerParameter, Parameter *minimumCountParameter,
		Parameter *loadedTemplateParameter, Parameter *transportTemplateParameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern BfmeThingFactory *TheThingFactory;

Bool ScriptConditions::evaluatePlayerHasNumUnitsLoadedWithObject(
	Parameter *playerParameter, Parameter *minimumCountParameter,
	Parameter *loadedTemplateParameter, Parameter *transportTemplateParameter)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return false;

	const ThingTemplate *loadedTemplate = TheThingFactory->findTemplate(
		loadedTemplateParameter->getString());
	const ThingTemplate *transportTemplate = TheThingFactory->findTemplate(
		transportTemplateParameter->getString());
	if (!loadedTemplate || !transportTemplate)
		return false;

	Int count = 0;
	for (BfmePlayerTeamListNode *it =
			((BfmePlayerTeamListField *)player)->m_head->m_next;
		it != ((BfmePlayerTeamListField *)player)->m_head; it = it->m_next)
	{
		Rva003269C0TeamInstanceIterator teams(
			it->m_prototype->m_teamInstanceList);
		for (; !teams.done(); teams.advance())
		{
			Rva003269C0TeamInstanceView *team = teams.cur();
			if (!team)
				continue;

			BfmePlayerDlinkIterator<Rva003269C0DlinkObjectView> objects =
				team->iterate_TeamMemberList();
			for (; !objects.done(); objects.advance())
			{
				Object *object = (Object *)objects.cur();
				if (!object)
					continue;

				if (object->getTemplate()->isEquivalentTo(transportTemplate))
				{
					ContainModuleInterface *contain =
						object->m_contain;
					if (contain)
					{
						const ContainedItemsList *items =
							contain->getContainedItemsList();
						for (ContainedItemsList::const_iterator item = items->begin();
							item != items->end(); ++item)
						{
							Object *loaded = *item;
							if (loaded && loaded->getTemplate()->isEquivalentTo(loadedTemplate))
								++count;
						}
					}
				}
			}
		}
	}

	if (count < *(const Int *)((const char *)minimumCountParameter + 8)) return false;
	return true;
}

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
