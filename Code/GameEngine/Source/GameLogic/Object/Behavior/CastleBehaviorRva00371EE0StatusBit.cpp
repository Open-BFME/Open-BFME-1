// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00371EE0, 342 bytes: CastleBehavior sets or clears one object
// status bit on its pending object and on every object in m_ownedObjectsC4,
// then tells the ScriptEngine.  Same class slice as the landed
// CastleBehaviorRva00370340.cpp (m_objectID +0xA0, owned-object vector
// +0xC4/+0xC8, TheBfmeGameLogic's hash_map at +0xB0).  Callers 0x00372BD0,
// 0x00376C70 and 0x00377550 reach it through ILT 0x00026094.
//
// GameLogic::findObjectByID is the header inline (body = landed
// GameLogicFindObjectByID.cpp, 0x0009A510): VC7.1 leaves the first call
// out of line and expands the one in the loop, which is what keeps the
// global unpromoted and the loop index in ebp.  The loop's two masks are
// the BitFlags<86> set(Int) over bitset::_Unchecked_set that
// ObjectStatusBits.cpp documents (no range check in retail).

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>
#include <bitset>

typedef int Int;
typedef int ObjectID;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_DESTROYED = 0
};

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	BitFlags() { }

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
	void setStatusBit(Int bit, Bool set);
	void clearStatus(ObjectStatusTypes status);
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > CastleObjectMap;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		CastleObjectMap::iterator it = m_objects.find(id);
		if (it == m_objects.end())
			return 0;

		return (*it).second;
	}

	char m_pad00[0xb0];
	CastleObjectMap m_objects;
};

extern GameLogic *TheBfmeGameLogic;

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

extern ScriptEngine *TheScriptEngine;

class CastleBehavior
{
public:
	void rva00371ee0(ObjectStatusTypes status, Bool set);

private:
	unsigned char m_pad00[0x9c];
	int m_state;
	ObjectID m_objectID;
	unsigned char m_padA4[0x14];
	_STL::vector<ObjectID> m_ownedObjectsB8;
	_STL::vector<ObjectID> m_ownedObjectsC4;
};

void CastleBehavior::rva00371ee0(ObjectStatusTypes status, Bool set)
{
	Object *pending = TheBfmeGameLogic->findObjectByID(m_objectID);
	if (pending) {
		if (set)
			pending->setStatusBit(status, true);
		else
			pending->clearStatus(status);
	}

	for (unsigned int i = 0; i < m_ownedObjectsC4.size(); ++i) {
		Object *object = TheBfmeGameLogic->findObjectByID(m_ownedObjectsC4[i]);
		if (object != 0) {
			if (set) {
				ObjectStatusMaskType mask;
				mask.set(status);
				object->setStatus(mask, true);
			} else {
				ObjectStatusMaskType mask;
				mask.set(status);
				object->setStatus(mask, false);
			}
		}
	}

	TheScriptEngine->notifyOfObjectCreationOrDestruction();
}
