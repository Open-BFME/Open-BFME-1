#pragma once
#include <hash_map>

class Object;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// BFME object lookup: retail 0x0009A510, buckets at this+0xB4.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

#ifdef BFME_GAMELOGIC_LOOKUP_VISIBLE
// ?findObjectByID@GameLogic@@QAEPAVObject@@H@Z present-unmatched
// The authoritative row remains GameLogicFindObjectByID.cpp. This inline
// definition exposes its read-only effects to callers, not another claim.
inline __declspec(noinline) Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;
	return (*it).second;
}
#endif
