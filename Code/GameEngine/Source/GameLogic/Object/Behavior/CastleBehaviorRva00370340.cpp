// ?rva00370340@CastleBehavior@@QAE_NPAVObjectTypes@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <set>
#include <vector>

typedef int ObjectID;
typedef bool Bool;

class ThingTemplate;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xd8 - 8];
	unsigned int m_kindOf;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
};

class ObjectTypes
{
public:
	Bool isInSet(const ThingTemplate *objectType) const;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > CastleObjectMap;

class GameLogic
{
public:
	char m_pad00[0xb0];
	CastleObjectMap m_objects;
};

extern GameLogic *TheBfmeGameLogic;

class CastleBehavior
{
public:
	Bool rva00370340(ObjectTypes *filter);

private:
	unsigned char m_pad00[0x9c];
	int m_state;
	ObjectID m_objectID;
	unsigned char m_padA4[0x14];
	_STL::vector<ObjectID> m_ownedObjectsB8;
	_STL::vector<ObjectID> m_ownedObjectsC4;
	_STL::vector<ObjectID> m_ownedObjectsD0;
	_STL::vector<ObjectID> m_ownedObjectsDC;
	_STL::vector<ObjectID> m_ownedObjectsE8;
	_STL::set<ObjectID> m_ownedObjectSetF4;
};

Bool CastleBehavior::rva00370340(ObjectTypes *filter)
{
	for (_STL::set<ObjectID>::iterator it = m_ownedObjectSetF4.begin();
		it != m_ownedObjectSetF4.end(); ++it) {
		ObjectID id = *it;
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheBfmeGameLogic->m_objects.find(id);
			if (objectIt != TheBfmeGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							objectTemplate->m_nextOverride->getFinalOverride();
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_ownedObjectsC4.size(); ++i) {
		ObjectID id = m_ownedObjectsC4[i];
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheBfmeGameLogic->m_objects.find(id);
			if (objectIt != TheBfmeGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							objectTemplate->m_nextOverride->getFinalOverride();
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_ownedObjectsD0.size(); ++i) {
		ObjectID id = m_ownedObjectsD0[i];
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheBfmeGameLogic->m_objects.find(id);
			if (objectIt != TheBfmeGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							objectTemplate->m_nextOverride->getFinalOverride();
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	ObjectID id = m_objectID;
	if (id != 0) {
		CastleObjectMap::iterator objectIt =
			TheBfmeGameLogic->m_objects.find(id);
		if (objectIt != TheBfmeGameLogic->m_objects.end()) {
			Object *object = (*objectIt).second;
			if (object != 0) {
				ThingTemplate *objectTemplate = object->m_template;
				if (objectTemplate != 0 &&
					objectTemplate->m_nextOverride != 0)
					objectTemplate = (ThingTemplate *)
						objectTemplate->m_nextOverride->getFinalOverride();
				if (filter->isInSet(objectTemplate))
					return true;
			}
		}
	}

	for (unsigned int i = 0; i < m_ownedObjectsB8.size(); ++i) {
		ObjectID id = m_ownedObjectsB8[i];
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheBfmeGameLogic->m_objects.find(id);
			if (objectIt != TheBfmeGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							objectTemplate->m_nextOverride->getFinalOverride();
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	return false;
}

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
