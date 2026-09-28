// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00371D10: registers the objects of two ObjectID vectors (+0xC4, then +0xB8) whose final template has bit 0x8000000 at +0xCC with the pathfinder.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

class Object;
typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// ?findObjectByID@Rva00367E30Logic@@QAEPAVObject@@H@Z absent-from-retail
class Rva00367E30Logic
{
public:
	// Same body as the landed GameLogic::findObjectByID (0x0009A510), expanded here as in retail.
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

class Overridable
{
public:
	void *vtable;
	Overridable *next;

	// Landed at 0x00087A80; retail expands the first level and calls the body for the rest.
	const Overridable *getFinalOverride() const
	{
		if (next)
			return next->getFinalOverride();
		return this;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_unreconstructed_00[4];
	const Overridable *m_unreconstructed_04;

	// ?finalOverride04@Object@@QBEPBVOverridable@@XZ absent-from-retail
	const Overridable *finalOverride04() const
	{
		if (!m_unreconstructed_04)
			return 0;
		return m_unreconstructed_04->getFinalOverride();
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
public:
	// ?pathfinder@AI@@QAEPAVPathfinder@@XZ absent-from-retail
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

	const Overridable *ov = obj->finalOverride04();
	unsigned int bits = *(unsigned int *)((char *)ov + 0xcc);
	if ((bits & 0x8000000) == 0)
		return;

	TheAI->pathfinder()->addObjectToPathfindMap(obj);
}

// Owner unproven; the field layout matches the landed CastleBehavior ObjectID vectors at +0xB8 and +0xC4.
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
	for (unsigned i = 0; i < vecA.size(); ++i)
		bfmeScanOne(vecA[i]);
	for (unsigned j = 0; j < vecB.size(); ++j)
		bfmeScanOne(vecB[j]);
}
