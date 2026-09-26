// Retail 0x002377A0 is slot 52 (+0xD0) in the HordeContain interface
// tables. The matched HordeContain constructor installs table 0x010AED58 at
// its +0xE4 interface; this slot is shared by the AOD and Horse variants.
// The method name and the meanings of slots 84/89 remain unproven, so keep
// the member address-derived. The member list and index layouts match the
// landed HordeContain methods at 0x002371C0 and 0x002388F0.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Player;
class Object;
class Rva002377A0DrawableView;

class Object
{
public:
	Player *getControllingPlayer( void ) const;

#define OBJECT_SLOT(N) virtual Int slot##N( void ) = 0
	OBJECT_SLOT(00); OBJECT_SLOT(01); OBJECT_SLOT(02); OBJECT_SLOT(03);
	OBJECT_SLOT(04); OBJECT_SLOT(05); OBJECT_SLOT(06); OBJECT_SLOT(07);
	OBJECT_SLOT(08); OBJECT_SLOT(09);
	virtual Rva002377A0DrawableView *getDrawable( void ) const = 0;
#undef OBJECT_SLOT
};

class PlayerListView
{
public:
	char m_head[0x0c];
	Player *m_localPlayer;
};

extern PlayerListView *ThePlayerList;

class Rva002377A0GlobalDataView
{
public:
	char m_head[0xA76];
	Bool m_fieldA76;
};

extern Rva002377A0GlobalDataView *TheWritableGlobalData;

class Rva004141A0GuardedVCall
{
public:
	void forward( Int a0, Int a1 );
};

#pragma comment(linker, "/alternatename:?forward@Rva004141A0GuardedVCall@@QAEXHH@Z=?j_0003e7f7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

struct Rva002377A0MemberIndexNode
{
	UnsignedInt m_color;
	Rva002377A0MemberIndexNode *m_parent;
	Rva002377A0MemberIndexNode *m_next;
	Rva002377A0MemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base * );
};
}

typedef _STL::list<Object *> Rva002377A0MemberList;
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > Rva002377A0ObjectHash;

class Rva002377A0GameLogicView
{
public:
	__forceinline Object *findObjectByID( UnsignedInt key )
	{
		Rva002377A0ObjectHash::iterator it = m_objectHash.find( key );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_head[0xB0];
	Rva002377A0ObjectHash m_objectHash;
};

extern Rva002377A0GameLogicView *TheGameLogic;

class Rva002377A0HordeContain
{
public:
#define HORDE_SLOT(N) virtual Int slot##N( void ) = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	virtual void rva002377a0( void );
	HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55); HORDE_SLOT(56);
	HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59); HORDE_SLOT(60);
	HORDE_SLOT(61); HORDE_SLOT(62); HORDE_SLOT(63); HORDE_SLOT(64);
	HORDE_SLOT(65); HORDE_SLOT(66); HORDE_SLOT(67); HORDE_SLOT(68);
	HORDE_SLOT(69); HORDE_SLOT(70); HORDE_SLOT(71); HORDE_SLOT(72);
	HORDE_SLOT(73); HORDE_SLOT(74); HORDE_SLOT(75); HORDE_SLOT(76);
	HORDE_SLOT(77); HORDE_SLOT(78); HORDE_SLOT(79); HORDE_SLOT(80);
	HORDE_SLOT(81); HORDE_SLOT(82); HORDE_SLOT(83);
	virtual Int slot84( Int ) = 0;
	HORDE_SLOT(85); HORDE_SLOT(86); HORDE_SLOT(87); HORDE_SLOT(88);
	virtual Int slot89( Object * ) = 0;
#undef HORDE_SLOT

private:
	char m_head[0x2C];
	Rva002377A0MemberIndexNode *m_memberIndex;

	Rva002377A0MemberList &memberList( void ) const
	{
		return *(Rva002377A0MemberList *)((char *)this - 0xAC);
	}
};

// The target reads PlayerList::m_local at +0x0C, the writable global-data
// byte at +0xA76, its containing list at this-0xAC, and the member-index
// sentinel pointer at this+0x30. Those offsets are independently witnessed
// by matched PlayerList/HordeContain siblings. The forwarding arguments keep
// their observed integer widths; their meanings are not asserted here.
void Rva002377A0HordeContain::rva002377a0( void )
{
	Player *localPlayer = ThePlayerList->m_localPlayer;
	Bool forwardMembers = false;
	Object *owner = *(Object **)((char *)this - 0xDC);

	if ( owner != 0 )
	{
		if ( owner->getControllingPlayer() == localPlayer )
		{
			Rva002377A0DrawableView *drawable = owner->getDrawable();
			if ( TheWritableGlobalData->m_fieldA76 )
			{
				if ( drawable != 0 )
				{
					((Rva004141A0GuardedVCall *)drawable)->forward(
						slot84( 0 ), slot89( owner ) );
				}
			}
			else
			{
				forwardMembers = true;
			}
		}
	}

	Rva002377A0MemberList &members = memberList();
	Rva002377A0MemberList::const_iterator it = members.begin();
	while ( it != members.end() )
	{
		Object *member = *it;
		if ( member != 0 )
		{
			Rva002377A0DrawableView *drawable = member->getDrawable();
			if ( drawable != 0 && forwardMembers )
			{
				((Rva004141A0GuardedVCall *)drawable)->forward(
					1, slot89( member ) );
			}
		}
		++it;
	}

	Rva002377A0MemberIndexNode *entry = m_memberIndex->m_next;
	while ( entry != m_memberIndex )
	{
		UnsignedInt key = entry->m_key;
		if ( key != 0 )
		{
			Object *member = TheGameLogic->findObjectByID( key );
			if ( member != 0 )
			{
				Rva002377A0DrawableView *drawable = member->getDrawable();
				if ( drawable != 0 && forwardMembers )
				{
					((Rva004141A0GuardedVCall *)drawable)->forward(
						1, slot89( member ) );
				}
			}
		}
		entry = (Rva002377A0MemberIndexNode *)
			_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)entry );
	}
}
