#pragma once
#include <algorithm>

class Object;
class FXList;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

struct CastleOwnedObjectVector00372BD0
{
	ObjectID *m_start;
	ObjectID *m_finish;
	ObjectID *m_capacity;

	ObjectID *begin() { return m_start; }
	ObjectID *end() { return m_finish; }
	unsigned int size() { return (unsigned int)(m_finish - m_start); }
	void clear() { m_finish = std::copy(m_finish, m_finish, m_start); }
};

struct CastleBehaviorModuleData00372BD0
{
	unsigned char m_pad00[0x50];
	FXList *m_effects;
};

// Canonical layout used by the recovery/reset bodies at 0x00373B30/0x00372BD0.
class CastleBehavior
{
public:
	void rva00372bd0(bool killOwnedObjects);
	void initiatePack();

private:
	void *m_vtable;
	CastleBehaviorModuleData00372BD0 *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0xc4];
	CastleOwnedObjectVector00372BD0 m_ownedObjectsD0;
};
