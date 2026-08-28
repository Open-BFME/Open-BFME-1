// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: GameLogic::findObjectByID, retail 0x0009A510, 82 bytes.
//
// BFME1 kept the hash_map lookup that Zero Hour later replaced with a flat
// vector -- the ZH header still carries the old body commented out in
// GameEngine/Include/GameLogic/GameLogic.h, and that commented block is this
// function verbatim.
//
// An earlier attempt walked the buckets with raw pointers and recorded the
// residue as three unreachable differences (id in the wrong register, a
// redundant reload of the bucket base after the div, two separate null exits).
// All three were artefacts of the hand-rolled replica.  Compiled against the
// real STLport <hash_map> the body is byte-exact on the first try: the reload
// is _M_buckets.size() and _M_buckets[__n] being two separate inlined vector
// accessors, and the duplicated exit is the branch structure of _M_find.
//
// The class is a TU-scoped ABI slice: only the bucket vector's placement
// matters, and it is fixed by the retail loads at this+0xB4 (_M_start) and
// this+0xB8 (_M_finish).  Node layout is _M_next+0, key+4, value+8.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Object;
typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

private:
	char m_slice_pad[0xB0];		// retail this+0x00 .. +0xAF, untouched
	ObjectPtrHash m_objHash;	// bucket vector _M_start lands at this+0xB4
};

Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;

	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;

	return (*it).second;
}
