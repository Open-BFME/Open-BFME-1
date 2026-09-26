// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: HordeContain filtered member count, retail 0x00238BC0.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;

class BfmeRvaA760Object
{
};

class BfmeRvaA760CountOwner
{
public:
	int getCount( void );
};

class BfmeRvaA760ProbeInterface
{
public:
	bool accepts( BfmeRvaA760Object *object, int count );
};

#pragma comment(linker, "/alternatename:?getCount@BfmeRvaA760CountOwner@@QAEHXZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?accepts@BfmeRvaA760ProbeInterface@@QAE_NPAVBfmeRvaA760Object@@H@Z=?j_0001da34@@YAXXZ")

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base * );
};
}

typedef _STL::hash_map<UnsignedInt, BfmeRvaA760Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;
typedef _STL::list<BfmeRvaA760Object *> BfmeMemberList;

class GameLogic
{
public:
	__forceinline BfmeRvaA760Object *findObjectByID( UnsignedInt key )
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find( key );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_head[ 0xb0 ];
	BfmeObjectPtrHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

class Rva00238BC0HordeContainInterface
{
public:
	#define SLOT( N ) virtual Int slot##N() = 0
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58); SLOT(59); SLOT(60); SLOT(61); SLOT(62); SLOT(63);
	SLOT(64); SLOT(65); SLOT(66); SLOT(67); SLOT(68); SLOT(69); SLOT(70); SLOT(71);
	SLOT(72); SLOT(73); SLOT(74); SLOT(75); SLOT(76); SLOT(77); SLOT(78); SLOT(79);
	SLOT(80); SLOT(81); SLOT(82); SLOT(83);
	Int getHordeMemberCount( BfmeRvaA760ProbeInterface *filter ) const;
	#undef SLOT

	char m_head[ 0x2c ];
	BfmeMemberIndexNode *m_memberIndex;
	Int m_memberCount;
};

// ?getHordeMemberCount@Rva00238BC0HordeContainInterface@@QBEHPAVBfmeRvaA760ProbeInterface@@@Z
Int Rva00238BC0HordeContainInterface::getHordeMemberCount(
BfmeRvaA760ProbeInterface *filter ) const
{
	BfmeRvaA760ProbeInterface *probe = filter;
	if ( probe == 0 )
	{
		BfmeMemberList &members = *(BfmeMemberList *)((char *)this - 0xac);
		return m_memberCount + members.size();
	}

	Int count = 0;
	BfmeRvaA760CountOwner *countOwner =
		*(BfmeRvaA760CountOwner **)((char *)this - 0xdc);
	BfmeMemberList &members = *(BfmeMemberList *)((char *)this - 0xac);
	BfmeMemberList::iterator node = members.begin();
	while ( node != members.end() )
	{
		if ( probe->accepts( *node, countOwner->getCount() ) )
			++count;
		++node;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while ( entry != m_memberIndex )
	{
		UnsignedInt key = entry->m_key;
		if ( key != 0 )
		{
			BfmeRvaA760Object *object =
				TheBfmeGameLogic->findObjectByID( key );
			if ( object != 0
				&& probe->accepts( object, countOwner->getCount() ) )
				++count;
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry );
	}

	return count;
}
