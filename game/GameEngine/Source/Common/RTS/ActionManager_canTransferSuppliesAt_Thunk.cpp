// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME: native C4E80 offsets retained; canonical Object callees.
#include "Common/ActionManager.h"
#include "Common/NameKeyGenerator.h"
#include "GameLogic/Object.h"

class SupplyTruckAIInterface;

class BFMEAIUpdateInterface
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11c() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12c() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13c() = 0;
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() const = 0;
};

class SupplyTruckAIInterface
{
public:
	virtual Int getNumberBoxes() const = 0;
	virtual void slot004() const = 0;
	virtual void slot008() const = 0;
	virtual void slot00c() const = 0;
	virtual Bool isAvailableForSupplying() const = 0;
};

class SupplyWarehouseDockUpdate
{
public:
	Int getBoxesStored() const
	{
		return *(const Int *)((const char *)this + 0x88);
	}
};

class SupplyCenterDockUpdate
{
};

class Rva000C4E80PlayerView
{
public:
	Int getPlayerType() const
	{
		return *(const Int *)((const char *)this + 0x2c);
	}

	Int getPlayerIndex() const
	{
		return *(const Int *)((const char *)this + 0x24);
	}
};

class BFMEActionObject { public: Bool testStatus(Int status) const; };
class Rva000C4E80ObjectView
{
public:
 Bool isEffectivelyDead() const { return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0; }
 UnsignedInt getStatusWord() const { return *(const UnsignedInt *)((const char *)this + 0x90); }
 BFMEAIUpdateInterface *getAI() const { return *(BFMEAIUpdateInterface *const *)((const char *)this + 0x204); }
};

// ?canTransferSuppliesAt@ActionManager@@QAE_NPBVObject@@0@Z
Bool ActionManager::canTransferSuppliesAt(const Object *obj,
	const Object *transferDest)
{
	if (obj == NULL || transferDest == NULL)
		return FALSE;

	if (reinterpret_cast<const Rva000C4E80ObjectView *>(transferDest)->isEffectivelyDead())
		return FALSE;

	if ((reinterpret_cast<const Rva000C4E80ObjectView *>(obj)->getStatusWord() & 4) != 0 ||
		(*(const UnsignedInt *)((const char *)transferDest + 0x90) & 4) != 0)
		return FALSE;

	if (reinterpret_cast<const BFMEActionObject *>(transferDest)->testStatus(0x13))
		return FALSE;

	const BFMEAIUpdateInterface *ai = reinterpret_cast<const Rva000C4E80ObjectView *>(obj)->getAI();
	if (ai == NULL)
		return FALSE;

	const SupplyTruckAIInterface *supplyTruck =
		ai->getSupplyTruckAIInterface();
	if (supplyTruck == NULL)
		return FALSE;

	static const NameKeyType key_warehouseUpdate =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	SupplyWarehouseDockUpdate *warehouseModule =
		(SupplyWarehouseDockUpdate *)transferDest->findUpdateModule(key_warehouseUpdate);
	if (warehouseModule != NULL)
	{
		if (warehouseModule->getBoxesStored() == 0 ||
			transferDest->getRelationship(obj) == ENEMIES)
			return FALSE;
	}

	static const NameKeyType key_centerUpdate =
		TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
	SupplyCenterDockUpdate *centerModule =
		(SupplyCenterDockUpdate *)transferDest->findUpdateModule(key_centerUpdate);
	if (centerModule != NULL)
	{
		if (supplyTruck->getNumberBoxes() == 0 ||
			transferDest->getControllingPlayer() !=
			obj->getControllingPlayer())
			return FALSE;
	}

	if (warehouseModule == NULL && centerModule == NULL)
		return FALSE;

	if (!supplyTruck->isAvailableForSupplying())
		return FALSE;

	Player *objPlayer =
		obj->getControllingPlayer();
	if (objPlayer != NULL)
	{
		if (reinterpret_cast<const Rva000C4E80PlayerView *>(objPlayer)->getPlayerType() == 0 &&
			transferDest->getShroudedStatus(reinterpret_cast<const Rva000C4E80PlayerView *>(objPlayer)->getPlayerIndex()) ==
			OBJECTSHROUD_SHROUDED)
			return FALSE;
	}

	return TRUE;
}
