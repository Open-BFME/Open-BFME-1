// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ResourceGatheringManager::removeSupplyCenter (0x000E5F20) and
// ::removeSupplyWarehouse (0x000E5F80).  Zero Hour bodies unchanged.
//
// Same ABI slice as ResourceGatheringManager_addSupply.cpp (vtbl / warehouses
// at +4 / centers at +8 / ObjectID at Object+0x74).  This TU omits
// _STLP_USE_NEWALLOC so list::erase calls the two-arg __node_alloc
// deallocate (push 0xC / push node / 0x0082E5F0) instead of inlined
// operator delete.  _STLP_NO_EXCEPTIONS inlines the erase helper.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int ObjectID;

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
	void removeSupplyCenter(Object *oldCenter);
	void removeSupplyWarehouse(Object *oldWarehouse);

private:
	typedef _STL::list<ObjectID> objectIDList;

	void *m_slice_vtbl;					// retail this+0x00
	objectIDList m_supplyWarehouses;	// retail this+0x04
	objectIDList m_supplyCenters;		// retail this+0x08
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
