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

// Retail ILT thunk reached in place of the Overridable::getFinalOverride call.
extern void j_000022bb();

class ThingTemplate;

class Overridable
{
public:
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

extern GameLogic *TheGameLogic;

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

static __forceinline const Overridable *getFinalOverride0022bb(
	Overridable *overridable)
{
	typedef const Overridable *(Overridable::*FinalOverrideFn)() const;
	union { void (*fn)(); FinalOverrideFn call; } u = { j_000022bb };
	return (overridable->*u.call)();
}

// Retail increments the tree cursor through _Rb_global::_M_increment
// directly. Spell that operation here without emitting another const-iterator
// operator++ copy (the earlier lobby TU owns that COMDAT).
Bool CastleBehavior::rva00370340(ObjectTypes *filter)
{
	for (_STL::set<ObjectID>::iterator it = m_ownedObjectSetF4.begin();
		it != m_ownedObjectSetF4.end();
        it._M_node = _STL::_Rb_global<bool>::_M_increment(it._M_node)) {
		ObjectID id = *it;
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheGameLogic->m_objects.find(id);
			if (objectIt != TheGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							getFinalOverride0022bb(objectTemplate->m_nextOverride);
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
				TheGameLogic->m_objects.find(id);
			if (objectIt != TheGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							getFinalOverride0022bb(objectTemplate->m_nextOverride);
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
				TheGameLogic->m_objects.find(id);
			if (objectIt != TheGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							getFinalOverride0022bb(objectTemplate->m_nextOverride);
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	ObjectID id = m_objectID;
	if (id != 0) {
		CastleObjectMap::iterator objectIt =
			TheGameLogic->m_objects.find(id);
		if (objectIt != TheGameLogic->m_objects.end()) {
			Object *object = (*objectIt).second;
			if (object != 0) {
				ThingTemplate *objectTemplate = object->m_template;
				if (objectTemplate != 0 &&
					objectTemplate->m_nextOverride != 0)
					objectTemplate = (ThingTemplate *)
						getFinalOverride0022bb(objectTemplate->m_nextOverride);
				if (filter->isInSet(objectTemplate))
					return true;
			}
		}
	}

	for (unsigned int i = 0; i < m_ownedObjectsB8.size(); ++i) {
		ObjectID id = m_ownedObjectsB8[i];
		if (id != 0) {
			CastleObjectMap::iterator objectIt =
				TheGameLogic->m_objects.find(id);
			if (objectIt != TheGameLogic->m_objects.end()) {
				Object *object = (*objectIt).second;
				if (object != 0) {
					ThingTemplate *objectTemplate = object->m_template;
					if (objectTemplate != 0 &&
						objectTemplate->m_nextOverride != 0)
						objectTemplate = (ThingTemplate *)
							getFinalOverride0022bb(objectTemplate->m_nextOverride);
					if (filter->isInSet(objectTemplate))
						return true;
				}
			}
		}
	}

	return false;
}


