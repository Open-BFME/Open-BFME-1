// cl: /DNDEBUG /MD /EHsc

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void bfmeObjectEnteringInfluence(Object *object);
	void bfmeObjectLeavingInfluence(Object *object);
};

struct ObjectListNode
{
	ObjectListNode *next;
	ObjectListNode *previous;
	Object *object;
};

struct ObjectList
{
	ObjectListNode *sentinel;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual const ObjectList *getContainedItemsList() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer);

private:
	unsigned char m_unreconstructed[0x1fc];
	ContainModuleInterface *m_contain;
};

void Object::bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer)
{
	if (!oldPlayer || !newPlayer)
		return;

	oldPlayer->bfmeObjectLeavingInfluence(this);
	newPlayer->bfmeObjectEnteringInfluence(this);

	ContainModuleInterface *contain = m_contain;
	if (contain)
	{
		const ObjectList *items = contain->getContainedItemsList();
		for (ObjectListNode *node = items->sentinel->next;
		     node != items->sentinel;
		     node = node->next)
		{
			if (node->object)
				node->object->bfmeTransferPowerInfluence(oldPlayer, newPlayer);
		}
	}
}
