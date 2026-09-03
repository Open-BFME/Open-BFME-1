// ?bfmeAllMembersReady@BfmeHordeContainPoll@@QAE_NXZ
// partial score=0.94 date=2026-09-03
// ?bfmeAllMembersReady@BfmeHordeContainPoll@@QAE_NXZ
// partial score=0.94 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Open-BFME5: the horde-container readiness poll over its id set, retail
// 0x0023C4D0.
//
// The set at this+0x30 is retail's STLport red-black tree, walked through the
// shared _Rb_global<bool>::_M_increment at 0x0082B870; the sentinel is re-read
// from the member every iteration because the increment call can move it, which
// is why `this` is spilled to the frame before the loop.
//
// Each id is resolved through TheGameLogic's object hash, inlined: the bucket
// vector runs from +0xB4 to +0xB8, the index is the id modulo the bucket count
// -- an unsigned `div`, so the count is a pointer difference divided by four --
// and the chain is walked comparing the key at node+4 until it matches. The
// value lives at node+8. Retail reloads the bucket base after the divide
// because `div` clobbers it.
//
// A resolved object marks the poll as non-empty and then runs the two-stage
// test. The reload of the queue pointer at +0x1c after the first stage is not a
// missed CSE: the null branch reaches that point with the register already
// zero, so the merged block has to read it again.
//
// The result is `not blocked`, and an empty poll is false rather than true --
// the two exits are distinct in retail.

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
	UnsignedInt m_bfmeId;								///< retail node+0x10
};

class Object;

struct BfmeObjectHashNode
{
	BfmeObjectHashNode *m_bfmeNext;						///< +0x00
	UnsignedInt m_bfmeId;								///< +0x04
	Object *m_bfmeObject;								///< +0x08
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

extern GameLogic *TheGameLogic;							///< retail [0x012F0898]

class BfmeMemberQueue
{
public:
	int m_bfmeUnknown00;
	int m_bfmeCount;									///< retail this+0x04
};

class BfmeMemberSlotState
{
public:
	char m_bfmeHead[ 0x1c ];
	BfmeMemberQueue *m_bfmeQueue;						///< retail this+0x1c
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
	BfmeMemberSlotState *m_bfmeSlotState;				///< retail this+0x30
};

// upstream layout: reference/shims/bfmeobject/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[ 0x114 ];
	UnsignedInt m_bfmeStatus;							///< retail this+0x114
	char m_bfmeGap[ 0x204 - 0x118 ];
	BfmeMemberAI *m_bfmeAI;								///< retail this+0x204
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
	_STL::_Rb_tree_node_base *m_bfmeIdSet;				///< retail this+0x30
};

// ?bfmeAllMembersReady@BfmeHordeContainPoll@@QAE_NXZ
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
