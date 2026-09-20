// ?rva00371ee0@CastleBehavior@@QAEXI_N@Z
// partial score=0.13 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00371EE0. Same CastleBehavior class as the landed
// CastleBehaviorRva00370340.cpp: m_objectID at +0xA0, m_ownedObjectsC4 (one
// of the five owned-object vectors) at +0xC4/+0xC8, and the same
// TheBfmeGameLogic->m_objects hash_map<ObjectID,Object*>. Sets or clears a
// single status bit on the pending object directly (setStatusBit/
// clearStatus), then does the same on every object owned via
// m_ownedObjectsC4 by manually building a BitFlags<86> mask and calling
// setStatus (ObjectStatusBits.cpp / ObjectClearStatusType.cpp), finally
// notifying ScriptEngine of the change (PlayerAIDispatch.cpp).

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <string.h>

typedef int ObjectID;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_DESTROYED = 0
};

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags() { memset( m_bits, 0, sizeof( m_bits ) ); }

	void set( ObjectStatusTypes bit )
	{
		m_bits[ ( unsigned int )bit >> 5 ] |= 1U << ( ( unsigned int )bit & 31 );
	}

private:
	unsigned int m_bits[ ( NUM_BITS + 31 ) / 32 ];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus( const ObjectStatusMaskType &status, Bool set );
	void setStatusBit( int bit, Bool set );
	void clearStatus( ObjectStatusTypes status );
};

// Manual bucket walk matching the retail inlined hash_map<ObjectID,Object*>
// lookup exactly: division-based modulo into the bucket array, then a
// singly-linked chain compared by key (node+4) returning the value
// (node+8).
struct Rva00371EE0HashNode
{
	Rva00371EE0HashNode *m_next;
	ObjectID m_key;
	Object *m_value;
};

class Rva00371EE0Hash
{
public:
	Object *bfmeFind( ObjectID id ) const
	{
		unsigned int bucketCount = static_cast<unsigned int>(
			m_bucketsFinish - m_bucketsStart );
		unsigned int index = static_cast<unsigned int>( id ) % bucketCount;
		Rva00371EE0HashNode *node = m_bucketsStart[ index ];
		while( node != 0 )
		{
			if( node->m_key == id )
				return node->m_value;
			node = node->m_next;
		}
		return 0;
	}

private:
	char m_unmodelled00[ 4 ];
	Rva00371EE0HashNode **m_bucketsStart;
	Rva00371EE0HashNode **m_bucketsFinish;
};

class GameLogic
{
public:
	char m_pad00[ 0xb0 ];
	Rva00371EE0Hash m_objects;

	Object *findObjectByID( ObjectID id );
};

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

extern GameLogic *TheBfmeGameLogic;
extern ScriptEngine *TheScriptEngine;

class CastleBehavior
{
public:
	void rva00371ee0( unsigned int bit, Bool set );

private:
	unsigned char m_pad00[ 0x9c ];
	int m_state;
	ObjectID m_objectID;
	unsigned char m_padA4[ 0x14 ];
	ObjectID *m_ownedObjectsB8Start;
	ObjectID *m_ownedObjectsB8Finish;
	ObjectID *m_ownedObjectsB8End;
	ObjectID *m_ownedObjectsC4Start;
	ObjectID *m_ownedObjectsC4Finish;

	unsigned int bfmeOwnedC4Size() const
	{
		return static_cast<unsigned int>( m_ownedObjectsC4Finish - m_ownedObjectsC4Start );
	}

	ObjectID bfmeOwnedC4At( unsigned int index ) const
	{
		return m_ownedObjectsC4Start[ index ];
	}
};

void CastleBehavior::rva00371ee0( unsigned int bit, Bool set )
{
	Object *pending = TheBfmeGameLogic->findObjectByID( m_objectID );
	if( pending )
	{
		if( set )
			pending->setStatusBit( ( int )bit, true );
		else
			pending->clearStatus( ( ObjectStatusTypes )bit );
	}

	for( unsigned int i = 0; i < bfmeOwnedC4Size(); ++i )
	{
		ObjectID id = bfmeOwnedC4At( i );
		if( id != 0 )
		{
			Object *object = TheBfmeGameLogic->m_objects.bfmeFind( id );
			if( object != 0 )
			{
				if( set )
				{
					ObjectStatusMaskType mask;
					mask.set( ( ObjectStatusTypes )bit );
					object->setStatus( mask, true );
				}
				else
				{
					ObjectStatusMaskType mask;
					mask.set( ( ObjectStatusTypes )bit );
					object->setStatus( mask, false );
				}
			}
		}
	}

	TheScriptEngine->notifyOfObjectCreationOrDestruction();
}

#pragma comment( linker, "/alternatename:?setStatusBit@Object@@QAEXH_N@Z=?j_00032dee@@YAXXZ" )
#pragma comment( linker, "/alternatename:?clearStatus@Object@@QAEXW4ObjectStatusTypes@@@Z=?j_00031f7a@@YAXXZ" )
#pragma comment( linker, "/alternatename:?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307e7@@YAXXZ" )
#pragma comment( linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ" )
#pragma comment( linker, "/alternatename:?notifyOfObjectCreationOrDestruction@ScriptEngine@@QAEXXZ=?j_0003b15b@@YAXXZ" )
