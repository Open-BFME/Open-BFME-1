// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// The previous bank called this BfmeHordeContainPoll::bfmeAllMembersReady.
// That semantic name is not proven.  vtable_lookup.py places the retail body
// in slot 38 (+0x98) of the HordeContainInterface subobject at complete-this
// +0xe4, and HordeAIUpdate_update.cpp independently calls that slot as slot98.
// The body is therefore kept under the witnessed slot name.  This TU models
// the interface subobject, so its set word at local +0x30 is complete-object
// +0x114.  The Object word at +0x114 is a condition/flags word, not Object's
// canonical status field at +0x90.
//
// Retail RVA 0x0023C4D0, 217 bytes.  The member test reads the +0x1c pointer
// once per comparison through a null-guarded accessor that yields 999999 for a
// null pointer (the shape of StateMachine::getCurrentStateID in the Generals
// reference); two separate expansions give retail's reload of that pointer.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <set>

class Object;
typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;
typedef _STL::set<UnsignedInt> BfmeIdSet;

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
		return (*it).second;
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
	UnsignedInt bfmeCountOrInvalid() const
	{
		return m_bfmeQueue ? m_bfmeQueue->m_bfmeCount : 999999;
	}

	char m_bfmeHead[ 0x1c ];
	BfmeMemberQueue *m_bfmeQueue;
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
	UnsignedInt m_bfmeFlags114;
	char m_bfmeGap[ 0x204 - 0x118 ];
	BfmeMemberAI *m_bfmeAI;
};

__forceinline BfmeMemberSlotState *bfmeGetSlotState( const Object *member )
{
	return member->m_bfmeAI->m_bfmeSlotState;
}

class HordeContainInterface
{
public:
	Bool slot98( void );

private:
	char m_bfmeHead[ 0x30 ];
	BfmeIdSet m_bfmeIdSet;
};

Bool HordeContainInterface::slot98( void )
{
	Bool blocked = false;
	Bool anyResolved = false;

	for ( BfmeIdSet::const_iterator it = m_bfmeIdSet.begin();
		it != m_bfmeIdSet.end(); ++it )
	{
		ObjectID id = *it;
		if ( id == 0 )
			continue;

		Object *member = TheGameLogic->findObjectByID( id );
		if ( member != 0 )
		{
			anyResolved = true;
			if ( bfmeGetSlotState( member )->bfmeCountOrInvalid() == 0 )
				continue;
			if ( bfmeGetSlotState( member )->bfmeCountOrInvalid() != 1 || ( member->m_bfmeFlags114 & 0x10000000 ) )
				blocked = true;
		}
	}

	if ( !anyResolved )
		return false;

	return blocked == 0;
}
