// cl: /DNDEBUG /MD /EHsc
// Zero Hour TransportContain::killRidersWhoAreNotFreeToExit against BFME's
// retail list module-data and virtual-slot layout.

class Object;

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object
{
public:
	void kill(DamageType damageType = DAMAGE_UNRESISTABLE,
		DeathType deathType = DEATH_NORMAL);
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class TransportContainModuleData
{
public:
	unsigned char m_unreconstructed_000[0x1fe];
	bool m_destroyRidersWhoAreNotFreeToExit;
};

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_prev;
	Object *m_item;
};

struct ContainedItemsList
{
	ContainedItemNode *m_node;
};

#define TRANSPORT_SLOT(n) virtual void unused##n();

class TransportContain
{
public:
	TRANSPORT_SLOT(00) TRANSPORT_SLOT(01) TRANSPORT_SLOT(02) TRANSPORT_SLOT(03)
	TRANSPORT_SLOT(04) TRANSPORT_SLOT(05) TRANSPORT_SLOT(06) TRANSPORT_SLOT(07)
	TRANSPORT_SLOT(08) TRANSPORT_SLOT(09) TRANSPORT_SLOT(10) TRANSPORT_SLOT(11)
	TRANSPORT_SLOT(12) TRANSPORT_SLOT(13) TRANSPORT_SLOT(14) TRANSPORT_SLOT(15)
	TRANSPORT_SLOT(16) TRANSPORT_SLOT(17) TRANSPORT_SLOT(18) TRANSPORT_SLOT(19)
	TRANSPORT_SLOT(20) TRANSPORT_SLOT(21) TRANSPORT_SLOT(22) TRANSPORT_SLOT(23)
	TRANSPORT_SLOT(24) TRANSPORT_SLOT(25)

protected:
	virtual bool isSpecificRiderFreeToExit(Object *object);
	virtual void killRidersWhoAreNotFreeToExit();

private:
	const TransportContainModuleData *getModuleData() const { return m_moduleData; }
	ContainedItemsList &getContainList() { return m_containList; }

	TransportContainModuleData *m_moduleData;
	unsigned char m_unreconstructed_008[0x30];
	ContainedItemsList m_containList;
};

#undef TRANSPORT_SLOT

// ?killRidersWhoAreNotFreeToExit@TransportContain@@MAEXXZ
void TransportContain::killRidersWhoAreNotFreeToExit()
{
	const TransportContainModuleData *data = getModuleData();
	ContainedItemNode *node = getContainList().m_node->m_next;
	while (node != getContainList().m_node)
	{
		Object *object = node->m_item;
		node = node->m_next;

		if (!isSpecificRiderFreeToExit(object))
		{
			if (data->m_destroyRidersWhoAreNotFreeToExit)
				TheGameLogic->destroyObject(object);
			else
				object->kill();
		}
	}
}
