// ?bfmeGo00371D10@Rva00371D10Owner@@QAEXXZ
// partial score=0.923288 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived: no named caller and no vtable/string proves the owning
// class, so identity stays opaque (docs/naming_evidence.md). The shape --
// two int-id vectors scanned via TheBfmeGameLogic's real STLport hash_map
// object lookup (same pattern as the byte-exact GameLogicFindObjectByID.cpp),
// then a KindOf-style bit test on the found object's template override,
// registering matches with TheAI's pathfinder -- matches the brief's
// "BfmeSpawnPointPathfinder::addObjectToPathfindMap" callee pin.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

class Object;
typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// findObjectByID is written inline (as GameLogicFindObjectByID.cpp's real
// findObjectByID body already proves byte-exact against retail 0x0009A510)
// so the compiler folds the hash_map lookup into this TU's call sites the
// same way retail's optimizer inlined it here, instead of emitting a second,
// unrelated out-of-line copy of the already-matched function.
class Rva00367E30Logic
{
public:
	__forceinline Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

extern Rva00367E30Logic *TheBfmeGameLogic;	// 0x012F0898

// getFinalOverride is a real Overridable method, already matched at
// 0x00087A80; declaring the TU-local class only for the call, no layout
// needed since we only ever go through a pointer already in hand.
class Overridable
{
public:
	void *vtable;
 Overridable *next;
 const Overridable *getFinalOverride() const { if(next)return next->getFinalOverride();return this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// +4 and the nested +4 chain are unwitnessed; kept opaque.
class Object
{
public:
	char m_unreconstructed_00[4];
	void *m_unreconstructed_04;
};

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);	// BFMEPathfinderMapShim, matched
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	char m_unreconstructed_00[0xc];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;	// 0x012EF214

static __forceinline void bfmeScanOne(ObjectID id)
{
	Object *obj = TheBfmeGameLogic->findObjectByID(id);
	if (obj == 0)
		return;

 const Overridable *ov=(const Overridable*)*(void**)((char*)obj+4);
 if(ov) ov=ov->getFinalOverride();
	unsigned int bits = *(unsigned int *)((char *)ov + 0xcc);
	if ((bits & 0x8000000) == 0)
		return;

	TheAI->pathfinder()->addObjectToPathfindMap(obj);

}

// this-relative fields (unproven owner): two int-id vectors, begin/end pairs
// at +0xc4/+0xc8 and +0xb8/+0xbc.
class Rva00371D10Owner
{
public:
	void bfmeGo00371D10();

private:
	char m_unreconstructed_00[0xb8];
 _STL::vector<ObjectID> vecB;
 _STL::vector<ObjectID> vecA;
};

void Rva00371D10Owner::bfmeGo00371D10()
{

 for(unsigned i=0;i<vecA.size();++i)
  bfmeScanOne(vecA[i]);
 for(unsigned j=0;j<vecB.size();++j)
  bfmeScanOne(vecB[j]);
}
