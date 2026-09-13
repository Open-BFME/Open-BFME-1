// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BFME ABI reconstruction of ActionManager::canTransferSuppliesAt.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;

#define NULL 0
#define FALSE false
#define TRUE true

enum Relationship
{
	ENEMIES = 0
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_SHROUDED = 4
};

class Module;
class SupplyTruckAIInterface;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

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

class Player
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

class Object
{
public:
	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}

	Bool testStatus(Int status) const;
	Module *findModule(Int key) const;
	Relationship getRelationship(const Object *that) const;
	Player *getControllingPlayer() const;
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	UnsignedInt getStatusWord() const
	{
		return m_status[0];
	}

	BFMEAIUpdateInterface *getAI() const
	{
		return *(BFMEAIUpdateInterface * const *)((const char *)this + 0x204);
	}

private:
	char m_beforeStatus[0x90];
	UnsignedInt m_status[2];
	char m_beforeAI[0x204 - 0x98];
	BFMEAIUpdateInterface *m_ai;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer() const;
};

class BfmeObjectShroudCall
{
public:
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeObjectCall@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?getShroudedStatus@BfmeObjectShroudCall@@QBE?AW4ObjectShroudStatus@@H@Z=?j_0002b81e@@YAXXZ")

class ActionManager
{
public:
	Bool canTransferSuppliesAt(const Object *, const Object *);
};

// ?canTransferSuppliesAt@ActionManager@@QAE_NPBVObject@@0@Z
Bool ActionManager::canTransferSuppliesAt(const Object *obj,
	const Object *transferDest)
{
	if (obj == NULL || transferDest == NULL)
		return FALSE;

	if (transferDest->isEffectivelyDead())
		return FALSE;

	if ((obj->getStatusWord() & 4) != 0 ||
		(*(const UnsignedInt *)((const char *)transferDest + 0x90) & 4) != 0)
		return FALSE;

	if (transferDest->testStatus(0x13))
		return FALSE;

	const BFMEAIUpdateInterface *ai = obj->getAI();
	if (ai == NULL)
		return FALSE;

	const SupplyTruckAIInterface *supplyTruck =
		ai->getSupplyTruckAIInterface();
	if (supplyTruck == NULL)
		return FALSE;

	static const NameKeyType key_warehouseUpdate =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	SupplyWarehouseDockUpdate *warehouseModule =
		(SupplyWarehouseDockUpdate *)transferDest->findModule(key_warehouseUpdate);
	if (warehouseModule != NULL)
	{
		if (warehouseModule->getBoxesStored() == 0 ||
			transferDest->getRelationship(obj) == ENEMIES)
			return FALSE;
	}

	static const NameKeyType key_centerUpdate =
		TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
	SupplyCenterDockUpdate *centerModule =
		(SupplyCenterDockUpdate *)transferDest->findModule(key_centerUpdate);
	if (centerModule != NULL)
	{
		if (supplyTruck->getNumberBoxes() == 0 ||
			reinterpret_cast<const BfmeObjectCall *>(transferDest)->getControllingPlayer() !=
			reinterpret_cast<const BfmeObjectCall *>(obj)->getControllingPlayer())
			return FALSE;
	}

	if (warehouseModule == NULL && centerModule == NULL)
		return FALSE;

	if (!supplyTruck->isAvailableForSupplying())
		return FALSE;

	Player *objPlayer =
		reinterpret_cast<const BfmeObjectCall *>(obj)->getControllingPlayer();
	if (objPlayer != NULL)
	{
		if (objPlayer->getPlayerType() == 0 &&
			reinterpret_cast<const BfmeObjectShroudCall *>(transferDest)->getShroudedStatus(objPlayer->getPlayerIndex()) ==
			OBJECTSHROUD_SHROUDED)
			return FALSE;
	}

	return TRUE;
}
