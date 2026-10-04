// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
// BFME ExperienceLevelSystem::update, retail 0x0037F4C0.  The pending list at
// +0x1C holds ObjectID, level-data pointer and effect flag records.  Phase 5
// resolves each live object, applies the record, then clears the list.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef unsigned int ObjectID;

class ExperienceLevelData;

#pragma comment(linker, "/alternatename:?call@Gen0002B7F6@@QAEXPAVExperienceLevelData@@PAVObject@@_N@Z=?j_0002b7f6@@YAXXZ")

#include "../GameLogic/Object/object.h"

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	char m_pad[ 0xB0 ];
	ObjectPtrHash m_objectHash;
};

// Retail inlines the lookup here and has no out-of-line copy for this TU, so
// the helper is a TU-local static rather than a GameLogic member whose COMDAT
// copy would compete with the other TUs' findObjectByID emitters.
static __forceinline Object *findObjectByID( GameLogic *logic, ObjectID id )
{
	if ( id == 0 )
		return 0;
	ObjectPtrHash::iterator it = logic->m_objectHash.find( id );
	if ( it == logic->m_objectHash.end() )
		return 0;
	return (*it).second;
}

extern GameLogic *TheGameLogic;

struct PendingExperienceLevel
{
	ObjectID m_objectID;
	ExperienceLevelData *m_level;
	Bool m_showEffect;
};

class Gen0002B7F6
{
public:
	void call( ExperienceLevelData *level, Object *object, Bool showEffect );
};

class ExperienceLevelSystem
{
public:
	virtual void update();

	char m_pad[ 0x18 ];
	_STL::list<PendingExperienceLevel> m_pending;
};

void ExperienceLevelSystem::update()
{
	for ( _STL::list<PendingExperienceLevel>::iterator it = m_pending.begin();
		it != m_pending.end(); ++it )
	{
		Object *object = findObjectByID( TheGameLogic, (*it).m_objectID );
		if ( object && !(object->m_privateStatus & 1) )
			((Gen0002B7F6 *)this)->call(
				(*it).m_level, object, (*it).m_showEffect );
	}

	m_pending.clear();
}
