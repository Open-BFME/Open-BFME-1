// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?addObjectToLookupTable@GameLogic@@QAEXPAVObject@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// readable body of ?removeObjectFromLookupTable@GameLogic@@QAEXPAVObject@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// Open-BFME: the two halves of GameLogic's object lookup table,
//
//   0x0038E490  addObjectToLookupTable       38 bytes
//   0x00388A90  removeObjectFromLookupTable  34 bytes
//
// which are the hash_map bodies Zero Hour left behind as comments when it
// moved the table to a flat vector -- `m_objHash[ obj->getID() ] = obj;` and
// `m_objHash.erase( obj->getID() );`, both still sitting above the vector code
// in GeneralsMD's GameLogic.cpp.  GameLogicFindObjectByID.cpp already showed
// BFME1 kept the hash_map; these two show it kept the writers as well.
//
// Same TU-scoped ABI slice as that file: the map at this+0xB0 is fixed by the
// retail `add ecx, 0xB0` both bodies do before the call, and the object's ID
// at +0x74 by the load feeding it.
//
// Both calls take the key by const reference, and retail builds that key in
// the incoming argument's own stack slot -- `obj` is dead by then, so MSVC
// reuses the four bytes rather than growing the frame.  Neither body has a
// frame of its own because of it.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }

private:
	char m_slice_pad[0x74];		// retail this+0x00 .. +0x73, untouched
	ObjectID m_id;			// this+0x74
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void addObjectToLookupTable(Object *obj);
	void removeObjectFromLookupTable(Object *obj);

private:
	char m_slice_pad[0xB0];		// retail this+0x00 .. +0xAF, untouched
	ObjectPtrHash m_objHash;	// this+0xB0
};

void GameLogic::addObjectToLookupTable(Object *obj)
{
	// sanity
	if (obj == NULL)
		return;

	// add to lookup
	m_objHash[ obj->getID() ] = obj;
}

void GameLogic::removeObjectFromLookupTable(Object *obj)
{
	// sanity
	if (obj == NULL)
		return;

	// remove from lookup table
	m_objHash.erase( obj->getID() );
}
