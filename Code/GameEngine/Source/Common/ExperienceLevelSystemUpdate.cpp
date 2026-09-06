// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc
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

class Object
{
public:
	char m_pad[ 0x344 ];
	unsigned char m_flags344;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID( ObjectID id )
	{
		if ( id == 0 )
			return 0;
		ObjectPtrHash::iterator it = m_objectHash.find( id );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_pad[ 0xB0 ];
	ObjectPtrHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

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
		Object *object = TheBfmeGameLogic->findObjectByID( (*it).m_objectID );
		if ( object && !(object->m_flags344 & 1) )
			((Gen0002B7F6 *)this)->call(
				(*it).m_level, object, (*it).m_showEffect );
	}

	m_pending.clear();
}
