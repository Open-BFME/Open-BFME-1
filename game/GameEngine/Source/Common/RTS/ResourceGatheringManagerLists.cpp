// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The four bodies that maintain the two supply lists, Zero Hour's unchanged:
//
//   0x000E5F20  removeSupplyCenter
//   0x000E5F80  removeSupplyWarehouse
//   0x000E6870  addSupplyCenter
//   0x000E68C0  addSupplyWarehouse
//
// One ABI slice serves all four -- vtbl at +0x00, warehouses at +0x04, centers
// at +0x08, and the ObjectID they store read from Object+0x74 -- and it was
// written out twice, once per file, along with Object.
//
// The reason these are an isolated TU with a hand-made slice is worth keeping
// whole, because the two files had each recorded only their own half of it.
//
// From the add side: the retail codegen depends on _M_create_node being
// INLINED into the caller. STLport wraps the node construction in
// _STLP_TRY/_STLP_UNWIND, and MSVC 7.1 refuses to inline any function
// containing a try block; with the try present the body keeps an out-of-line
// call to _M_create_node, and MSVC then sinks `push esi`/`push edi` into the
// guarded block, each immediately before that register's own first def.
// Defining _STLP_NO_EXCEPTIONS drops the try, _M_create_node inlines, the
// guarded region collapses to one straight-line block, and the two saves go
// back to the entry block in ABI order -- which is exactly retail's shape.
// (The earlier verdict that this residue was "prologue vs shrink-wrap, binary,
// no source lever" was measured on a hand-written flat replica of the list
// splice; the real header does not behave that way.)
//
// From the remove side: _STLP_USE_NEWALLOC must stay undefined, so list::erase
// calls the two-arg __node_alloc deallocate (push 0xC / push node /
// 0x0082E5F0) rather than an inlined operator delete. The same define also
// inlines the erase helper.
//
// And the allocation the add side uses is the default node-pool path: retail's
// `push 0xc` is followed by a call to __node_alloc<true,0>::_M_allocate
// (0x0082E540), which is what the stock allocator emits once the ternary in
// __node_alloc::allocate folds on the constant node size. _STLP_USE_NEWALLOC
// used to be defined on the add side and looked right only because
// ??2@YAPAXI@Z is also pinned at 0x0082E540 -- so the two halves of this note
// are about the same define, and only together do they say why it is absent.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int ObjectID;

// Only Object::getID() is reachable from these bodies; the id lives at retail
// Object+0x74.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ResourceGatheringManager.h
class ResourceGatheringManager
{
public:
	void removeSupplyCenter(Object *oldCenter);
	void removeSupplyWarehouse(Object *oldWarehouse);
	void addSupplyCenter(Object *newCenter);
	void addSupplyWarehouse(Object *newWarehouse);

private:
	typedef _STL::list<ObjectID> objectIDList;

	void *m_slice_vtbl;					// retail this+0x00
	objectIDList m_supplyWarehouses;			// retail this+0x04
	objectIDList m_supplyCenters;				// retail this+0x08
};

// ?removeSupplyCenter@ResourceGatheringManager@@QAEXPAVObject@@@Z
void ResourceGatheringManager::removeSupplyCenter(Object *oldCenter)
{
	if (oldCenter == NULL)
		return;

	ObjectID targetID = oldCenter->getID();

	objectIDList::iterator iterator = m_supplyCenters.begin();
	while (iterator != m_supplyCenters.end())
	{
		if (targetID == *iterator)
		{
			iterator = m_supplyCenters.erase(iterator);
		}
		else
			iterator++;
	}
}

// ?removeSupplyWarehouse@ResourceGatheringManager@@QAEXPAVObject@@@Z
void ResourceGatheringManager::removeSupplyWarehouse(Object *oldWarehouse)
{
	if (oldWarehouse == NULL)
		return;

	ObjectID targetID = oldWarehouse->getID();

	objectIDList::iterator iterator = m_supplyWarehouses.begin();
	while (iterator != m_supplyWarehouses.end())
	{
		if (targetID == *iterator)
		{
			iterator = m_supplyWarehouses.erase(iterator);
		}
		else
			iterator++;
	}
}

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
