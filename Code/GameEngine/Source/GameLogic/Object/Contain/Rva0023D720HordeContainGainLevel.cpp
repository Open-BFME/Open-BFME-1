// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Open-BFME5: HordeContain member experience refresh, retail 0x0023D720.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object
{
};

class ExperienceLevelSystem
{
public:
	void gainLevel( Object *, Bool );
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The first container is the STLport list embedded immediately before this
// interface subobject.  Its sentinel is the node itself and its value is at
// +8.
struct BfmeMemberNode
{
	BfmeMemberNode *m_next;
	BfmeMemberNode *m_previous;
	Object *m_object;
};

struct BfmeMemberScanNode
{
	BfmeMemberScanNode *m_next;
};

// The second container is an ordered tree.  The sentinel/ordered node uses
// the standard STLport node links at +8 and stores its key at +0x10.
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

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;
typedef _STL::list<Object *> BfmeMemberList;

class BfmeGameLogic
{
public:
	__forceinline Object *findObjectByID( UnsignedInt key )
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find( key );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_head[ 0xb0 ];
	BfmeObjectPtrHash m_objectHash;
};

extern BfmeGameLogic *TheGameLogic;

class BfmeHordeContainOwner
{
public:
	void bfmeRefreshMemberExperience( void );
	void bfmeRefreshFormation( void );

	char m_head[ 0x30 ];
	BfmeMemberIndexNode *m_memberIndex;
	UnsignedInt m_memberCount;
	char m_gap[ 0xa0 ];
	void *m_pendingRefresh;
	char m_gap2[ 0x4c ];
	UnsignedInt m_refreshCount;

private:
	BfmeMemberList &bfmeMemberList( void ) const
	{
		return *(BfmeMemberList *)( (char *)this - 0xac );
	}

	BfmeHordeContainOwner *bfmeRefreshView( void )
	{
		return (BfmeHordeContainOwner *)( (char *)this - 0xe4 );
	}
};

// ?bfmeRefreshMemberExperience@BfmeHordeContainOwner@@QAEXXZ
void BfmeHordeContainOwner::bfmeRefreshMemberExperience( void )
{
	BfmeMemberList &members = bfmeMemberList();
	BfmeMemberList::iterator node = members.begin();

	if ( m_memberCount == 0 )
	{
		if ( members.size() == 0 )
			return;
	}

	while ( node != members.end() )
	{
		Object *object = *node;
		if ( object != 0 )
		{
			TheExperienceLevelSystem->gainLevel( object, true );
			++node;
		}
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while ( entry != m_memberIndex )
	{
		UnsignedInt key = entry->m_key;
		if ( key != 0 )
		{
			Object *object = TheGameLogic->findObjectByID( key );
			if ( object != 0 )
				TheExperienceLevelSystem->gainLevel( object, true );
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry );
	}

	++m_refreshCount;
	if ( m_pendingRefresh == 0 )
		bfmeRefreshView()->bfmeRefreshFormation();
}
