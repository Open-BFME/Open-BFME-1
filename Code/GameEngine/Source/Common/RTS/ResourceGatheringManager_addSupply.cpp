// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ResourceGatheringManager::addSupplyCenter (0x000E6870) and
// ::addSupplyWarehouse (0x000E68C0), Zero Hour's ResourceGatheringManager.cpp
// bodies unchanged.
//
// Isolated TU with a local ABI slice, because the retail codegen depends on
// _M_create_node being INLINED into the caller.  STLport wraps the node
// construction in _STLP_TRY/_STLP_UNWIND, and MSVC 7.1 refuses to inline any
// function containing a try block; with the try present the body keeps an
// out-of-line call to _M_create_node, and MSVC then sinks `push esi`/`push edi`
// into the guarded block, each immediately before that register's own first
// def.  Defining _STLP_NO_EXCEPTIONS drops the try, _M_create_node inlines,
// the guarded region collapses to one straight-line block, and the two saves
// go back to the entry block in ABI order -- which is exactly retail's shape.
// (The earlier verdict that this residue was "prologue vs shrink-wrap, binary,
// no source lever" was measured on a hand-written flat replica of the list
// splice; the real header does not behave that way.)
//
// _STLP_USE_NEWALLOC picks the plain-new allocator, so the node allocation is
// the single `push 0xc` / cdecl call that retail has, not the node-pool path.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int ObjectID;

// Only Object::getID() is reachable from these two bodies; the id lives at
// retail Object+0x74.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ResourceGatheringManager.h
class ResourceGatheringManager
{
public:
	void addSupplyCenter(Object *newCenter);
	void addSupplyWarehouse(Object *newWarehouse);

private:
	typedef _STL::list<ObjectID> objectIDList;

	void *m_slice_vtbl;					// retail this+0x00
	objectIDList m_supplyWarehouses;	// retail this+0x04
	objectIDList m_supplyCenters;		// retail this+0x08
};

// ?addSupplyCenter@ResourceGatheringManager@@QAEXPAVObject@@@Z
void ResourceGatheringManager::addSupplyCenter(Object *newCenter)
{
	if (newCenter == NULL)
		return;

	m_supplyCenters.push_back(newCenter->getID());
}

// ?addSupplyWarehouse@ResourceGatheringManager@@QAEXPAVObject@@@Z
void ResourceGatheringManager::addSupplyWarehouse(Object *newWarehouse)
{
	if (newWarehouse == NULL)
		return;

	m_supplyWarehouses.push_back(newWarehouse->getID());
}
