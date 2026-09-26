// Retail 0x0023A100, complete boundary 167 bytes.
//
// Retail walks the ordered Horde member index when flag 0x10 is set.  It
// resolves each nonzero member ID through GameLogic, calls the visitor, and
// otherwise delegates to the shared contained-list walk at 0x002234A0.
// stlport

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object
{
};

typedef void (__cdecl *Rva0023A100Callback)(void *, void *);

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

class Rva0021B200ListOwner
{
public:
	void call_002234A0( Rva0023A100Callback callback, void *context,
		UnsignedInt flags );
};

class Rva0023A100HordeContain
{
public:
	void visit( Rva0023A100Callback callback, void *context, UnsignedInt flags );

private:
	unsigned char m_unreconstructed_000[ 0xf4 ];
	BfmeMemberIndexNode *m_memberIndex;
};

// ?visit@Rva0023A100HordeContain@@QAEXP6AXPAX0@Z0I@Z
void Rva0023A100HordeContain::visit( Rva0023A100Callback callback,
	void *context, UnsignedInt flags )
{
	if ( (flags & 0x10) != 0 )
	{
		BfmeMemberIndexNode *entry = m_memberIndex->m_next;
		if ( entry != m_memberIndex )
		{
			do
			{
				UnsignedInt key = entry->m_key;
				Object *object = (Object *)key;
				if ( key != 0 )
					object = TheGameLogic->findObjectByID( key );

				entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
					(_STL::_Rb_tree_node_base *)entry );
				callback( object, context );
			} while ( entry != m_memberIndex );
		}
	}
	else
	{
		((Rva0021B200ListOwner *)this)->call_002234A0(
			callback, context, flags );
	}
}
