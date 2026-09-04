// ?bfmeAllMembersReady@BfmeHordeContainPoll@@QAE_NXZ
// partial score=0.94 date=2026-09-04
// ?bfmeAllMembersReady@BfmeHordeContainPoll@@QAE_NXZ
// Started from reverse/attempts/0x0023c4d0.cpp (score 0.94).
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

namespace _STL
{
struct _Rb_tree_node_base
{
	int m_bfmeColor;
	_Rb_tree_node_base *m_bfmeParent;
	_Rb_tree_node_base *m_bfmeLeft;
	_Rb_tree_node_base *m_bfmeRight;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base *node );
};
}

struct BfmeIdNode
{
	_STL::_Rb_tree_node_base m_bfmeBase;
	UnsignedInt m_bfmeId;
};

class Object;

struct BfmeObjectHashNode
{
	BfmeObjectHashNode *m_bfmeNext;
	UnsignedInt m_bfmeId;
	Object *m_bfmeObject;
};

typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID( ObjectID id )
	{
		if ( id == 0 )
			return 0;
		ObjectPtrHash::iterator it = m_objects.find( id );
		if ( it == m_objects.end() )
			return 0;
		Object *object = (*it).second;
		return object;
	}

	char m_bfmeHead[ 0xb0 ];
	ObjectPtrHash m_objects;
};

extern GameLogic *TheGameLogic;

class BfmeMemberQueue
{
public:
	int m_bfmeUnknown00;
	int m_bfmeCount;
};

class BfmeMemberSlotState
{
public:
	char m_bfmeHead[ 0x1c ];
	BfmeMemberQueue *m_bfmeQueue;
};

struct BfmeMemberSlotStateVolatile
{
	char m_bfmeHead[ 0x1c ];
	BfmeMemberQueue * volatile m_bfmeQueue;
};

class BfmeMemberAI
{
public:
	char m_bfmeHead[ 0x30 ];
	BfmeMemberSlotState *m_bfmeSlotState;
};

class Object
{
public:
	char m_bfmeHead[ 0x114 ];
	UnsignedInt m_bfmeStatus;
	char m_bfmeGap[ 0x204 - 0x118 ];
	BfmeMemberAI *m_bfmeAI;
};

__forceinline BfmeMemberSlotState *bfmeGetSlotState( const Object *member )
{
	return member->m_bfmeAI->m_bfmeSlotState;
}

class BfmeHordeContainPoll
{
public:
	Bool bfmeAllMembersReady( void );

private:
	char m_bfmeHead[ 0x30 ];
	_STL::_Rb_tree_node_base *m_bfmeIdSet;
};

Bool BfmeHordeContainPoll::bfmeAllMembersReady( void )
{
	Bool blocked = false;
	Bool anyResolved = false;

	for ( _STL::_Rb_tree_node_base *node = m_bfmeIdSet->m_bfmeLeft; node != m_bfmeIdSet;
		node = _STL::_Rb_global<bool>::_M_increment( node ) )
	{
		Object *member;
		ObjectID id = ( (BfmeIdNode *)node )->m_bfmeId;

		if ( id == 0 )
			continue;

		member = TheGameLogic->findObjectByID( id );
		if ( member != 0 )
		{
			BfmeMemberSlotState *state = bfmeGetSlotState( member );
			BfmeMemberQueue *queue = member->m_bfmeAI->m_bfmeSlotState->m_bfmeQueue;

			anyResolved = true;

			if ( queue != 0 )
			{
				if ( queue->m_bfmeCount == 0 )
					continue;
			}

			queue = ((BfmeMemberSlotStateVolatile *)state)->m_bfmeQueue;

			if ( queue == 0 || queue->m_bfmeCount != 1 ||
				( member->m_bfmeStatus & 0x10000000 ) )
				blocked = true;
		}
	}

	if ( !anyResolved )
		return false;

	return blocked == 0;
}
