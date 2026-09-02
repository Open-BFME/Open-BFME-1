// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: the horde-container member release hook, retail 0x002429C0.
//
// Three calls and nothing else. The member's id at Object+0x74 is dropped from
// the container's own index map at this+0x114 -- retail's shared STLport
// _Rb_tree<int, pair<const int, twelve-byte>> erase body at 0x0023DC00, reached
// through the ILT at 0x0001EB1E -- then the base subobject at this+0x20 is told
// about the member, and finally the interface view at this+0xE4 is handed the
// six-word block at owner+0x224 with a false flag.
//
// The function has no frame at all: the reference temp the erase takes lives in
// the incoming parameter's own stack slot, which is free because the member
// pointer has already been copied into edi.
//
// The two vtable slots are 0x88 on the base at +0x20 and 0xB0 on the view at
// +0xE4; both interfaces are otherwise opaque, so their earlier slots are
// placeholders and only the two used ones carry a name.

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	int bfmeGetId( void ) const { return m_bfmeId; }

	char m_bfmeHead[ 0x74 ];
	int m_bfmeId;										///< retail this+0x74
	char m_bfmeTail[ 0x224 - 0x78 ];
	UnsignedInt m_bfmeUpgradesCompleted[ 6 ];			///< retail this+0x224
};

// retail's shared twelve-byte map payload, the tree body at 0x0023DC00
struct Gen_t_0023dc00_p12cd
{
	int a[ 3 ];
};

namespace _STL
{
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};

template <class Pair>
struct _Select1st
{
};

template <class Key>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	UnsignedInt erase( const Key &key );

	char m_bfmeBody[ 12 ];
};
}

typedef _STL::pair<const int, Gen_t_0023dc00_p12cd> BfmeMemberPair;
typedef _STL::_Rb_tree<int, BfmeMemberPair, _STL::_Select1st<BfmeMemberPair>,
	_STL::less<int>, _STL::allocator<BfmeMemberPair> > BfmeMemberTree;

#define BFME_SLOT( N ) virtual int bfmeSlot##N( void ) = 0

class BfmeHordeContainBase
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 );
	virtual void bfmeOnMemberReleased( Object *member ) = 0;		///< slot 34
};

class BfmeHordeContainView
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 );
	BFME_SLOT( 36 ); BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 );
	BFME_SLOT( 40 ); BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 );
	virtual void bfmeApplyUpgrades( UnsignedInt *upgrades, Bool force ) = 0;	///< slot 44
};

#undef BFME_SLOT

class BfmeHordeContainOwner
{
public:
	void bfmeReleaseMember( Object *member );

private:
	BfmeHordeContainBase *bfmeBase( void )
	{
		return (BfmeHordeContainBase *)( (char *)this + 0x20 );
	}

	BfmeHordeContainView *bfmeView( void )
	{
		return (BfmeHordeContainView *)( (char *)this + 0xe4 );
	}

	char m_bfmeHead[ 8 ];
	Object *m_bfmeOwner;								///< retail this+0x08
	char m_bfmeGap[ 0x114 - 0x0c ];
	BfmeMemberTree m_bfmeMemberIndices;					///< retail this+0x114
};

// ?bfmeReleaseMember@BfmeHordeContainOwner@@QAEXPAVObject@@@Z
void BfmeHordeContainOwner::bfmeReleaseMember( Object *member )
{
	m_bfmeMemberIndices.erase( member->bfmeGetId() );

	bfmeBase()->bfmeOnMemberReleased( member );

	bfmeView()->bfmeApplyUpgrades( m_bfmeOwner->m_bfmeUpgradesCompleted, false );
}
