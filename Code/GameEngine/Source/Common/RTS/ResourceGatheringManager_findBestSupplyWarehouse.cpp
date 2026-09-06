// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <float.h>
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;
typedef unsigned int NameKeyType;

class Object;
class ActionManager;
class AIUpdateInterface;
class DockUpdateInterface;
class Module;
class SupplyWarehouseDockUpdate;
class ResourceGatheringManager;
class SupplyTruckAIInterface;
class Gen_000E5A90;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

static NameKeyType NAMEKEY(const char *name)
{
	return TheNameKeyGenerator->nameToKey(name);
}

class SupplyTruckAIInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Real getWarehouseScanDistance() const = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual ObjectID getPreferredDockID() const = 0;
};

class AIUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12C() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
};

class Gen_000E5A90
{
public:
	Real bfmeDistanceSquared(const Gen_000E5A90 *other) const;
};

class Object : public Gen_000E5A90
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
	SupplyWarehouseDockUpdate *findUpdateModule(int name);
	DockUpdateInterface *getDockUpdateInterface();

private:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

class ActionManager
{
public:
	Bool canTransferSuppliesAt(const Object *object, const Object *destination);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern ActionManager *TheActionManager;
extern GameLogic *TheGameLogic;

class DockUpdateInterface
{
public:
	virtual Bool isClearToApproach(const Object *docker) const = 0;
};

static Real computeRelativeCost(Object *queryObject, Object *destObject, Real *pureDistanceSquared)
{
	if (queryObject == NULL || destObject == NULL)
		return FLT_MAX;

	if (!TheActionManager->canTransferSuppliesAt(queryObject, destObject))
		return FLT_MAX;

	DockUpdateInterface *dockInterface = destObject->getDockUpdateInterface();
	if (!dockInterface->isClearToApproach(queryObject))
		return FLT_MAX;

	Real distSquared = queryObject->bfmeDistanceSquared(destObject);
	if (pureDistanceSquared)
		*pureDistanceSquared = distSquared;

	return distSquared;
}

class ResourceGatheringManager
{
public:
	Object *findBestSupplyWarehouse(Object *queryObject);

private:
	typedef _STL::list<ObjectID> objectIDList;
	typedef objectIDList::iterator objectIDListIterator;

	void *m_slice_vtbl;
	objectIDList m_supplyWarehouses;
	objectIDList m_supplyCenters;
};

// ?findBestSupplyWarehouse@ResourceGatheringManager@@QAEPAVObject@@PAV2@@Z
Object *ResourceGatheringManager::findBestSupplyWarehouse(Object *queryObject)
{
	Object *bestWarehouse = NULL;
	Real maxDistanceSquared = 100000;

	if (queryObject == NULL || queryObject->getAI() == NULL)
		return NULL;

	SupplyTruckAIInterface *supplyTruckAI =
		queryObject->getAI()->getSupplyTruckAIInterface();
	if (supplyTruckAI)
	{
		ObjectID dockID = supplyTruckAI->getPreferredDockID();
		Object *dock = TheGameLogic->findObjectByID(dockID);
		if (dock)
		{
			static const NameKeyType key_warehouseUpdate =
				NAMEKEY("SupplyWarehouseDockUpdate");
			SupplyWarehouseDockUpdate *warehouseModule =
				(SupplyWarehouseDockUpdate *)dock->findUpdateModule(key_warehouseUpdate);
			if (warehouseModule &&
				computeRelativeCost(queryObject, dock, NULL) != FLT_MAX)
				return dock;
		}

		maxDistanceSquared = supplyTruckAI->getWarehouseScanDistance() *
			supplyTruckAI->getWarehouseScanDistance();
	}

	Real bestCost = FLT_MAX;
	objectIDListIterator iterator = m_supplyWarehouses.begin();
	while (iterator != m_supplyWarehouses.end())
	{
		Object *currentWarehouse =
			TheGameLogic->findObjectByID(*iterator);

		if (currentWarehouse == NULL)
		{
			iterator = m_supplyWarehouses.erase(iterator);
		}
		else
		{
			Real distanceSquared;
			Real currentCost = computeRelativeCost(queryObject,
				currentWarehouse, &distanceSquared);
			if (currentCost < bestCost && distanceSquared < maxDistanceSquared)
			{
				bestWarehouse = currentWarehouse;
				bestCost = currentCost;
			}

			iterator++;
		}
	}

	return bestWarehouse;
}
