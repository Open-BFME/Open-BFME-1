// ?getObjectGarrisonPointIndex@GarrisonContain@@UAEHW4ObjectID@@@Z
// partial score=0.7 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Retail 0x0021F280: GarrisonContain slot 26 ObjectID lookup.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <new>

typedef int Int;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

typedef _STL::_List_node<Object *> ContainedItemsListNode;
typedef _STL::__node_alloc<true, 0> ContainedItemsNodeAllocator;

__forceinline void destroyContainedItemsList(ContainedItemsList *list)
{
	ContainedItemsListNode *sentinel =
		reinterpret_cast<ContainedItemsListNode *>(list);
	ContainedItemsListNode *node =
		reinterpret_cast<ContainedItemsListNode *>(sentinel->_M_next);
	while (node != sentinel)
	{
		ContainedItemsListNode *next =
			reinterpret_cast<ContainedItemsListNode *>(node->_M_next);
		ContainedItemsNodeAllocator::deallocate(node,
			sizeof(ContainedItemsListNode));
		node = next;
	}
	sentinel->_M_next = sentinel;
	sentinel->_M_prev = sentinel;
	ContainedItemsNodeAllocator::deallocate(sentinel,
		sizeof(ContainedItemsListNode));
}

class HordeContainInterface
{
public:
#define HORDE_SLOT(n) virtual void slot##n() = 0;
	HORDE_SLOT(00) HORDE_SLOT(01) HORDE_SLOT(02) HORDE_SLOT(03)
	HORDE_SLOT(04) HORDE_SLOT(05) HORDE_SLOT(06) HORDE_SLOT(07)
	HORDE_SLOT(08) HORDE_SLOT(09) HORDE_SLOT(10) HORDE_SLOT(11)
	HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14) HORDE_SLOT(15)
	HORDE_SLOT(16) HORDE_SLOT(17) HORDE_SLOT(18) HORDE_SLOT(19)
	HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23)
	HORDE_SLOT(24) HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27)
	HORDE_SLOT(28) HORDE_SLOT(29) HORDE_SLOT(30) HORDE_SLOT(31)
	HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34) HORDE_SLOT(35)
	HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39)
	HORDE_SLOT(40) HORDE_SLOT(41) HORDE_SLOT(42) HORDE_SLOT(43)
	HORDE_SLOT(44) HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47)
	HORDE_SLOT(48) HORDE_SLOT(49) HORDE_SLOT(50) HORDE_SLOT(51)
	HORDE_SLOT(52) HORDE_SLOT(53) HORDE_SLOT(54) HORDE_SLOT(55)
	HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58)
#undef HORDE_SLOT
	virtual const ContainedItemsList &getContainList() const = 0;
};

class ObjectContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n() = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25)
	virtual HordeContainInterface *getHordeContainInterface() = 0;
#undef CONTAIN_SLOT
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

	private:
	char m_pad000[0x74];
	ObjectID m_id;
	char m_pad078[0x184];

	public:
	ObjectContainModuleInterface *m_contain;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID objectID);
};

extern GameLogic *TheGameLogic;

struct GarrisonPointData
{
	ObjectID objectID;
	Int targetID;
	Int placeFrame;
	Int lastEffectFrame;
	void *effect;
};

class GarrisonContain
{
public:
#define GARRISON_SLOT(n) virtual void slot##n() = 0;
	GARRISON_SLOT(00) GARRISON_SLOT(01) GARRISON_SLOT(02) GARRISON_SLOT(03)
	GARRISON_SLOT(04) GARRISON_SLOT(05) GARRISON_SLOT(06) GARRISON_SLOT(07)
	GARRISON_SLOT(08) GARRISON_SLOT(09) GARRISON_SLOT(10) GARRISON_SLOT(11)
	GARRISON_SLOT(12) GARRISON_SLOT(13) GARRISON_SLOT(14) GARRISON_SLOT(15)
	GARRISON_SLOT(16) GARRISON_SLOT(17) GARRISON_SLOT(18) GARRISON_SLOT(19)
	GARRISON_SLOT(20) GARRISON_SLOT(21) GARRISON_SLOT(22) GARRISON_SLOT(23)
	GARRISON_SLOT(24) GARRISON_SLOT(25)
	virtual Int getObjectGarrisonPointIndex(ObjectID objectID);

private:
	char m_pad004[0xd4];
	GarrisonPointData m_garrisonPointData[40];
};

// ?getObjectGarrisonPointIndex@GarrisonContain@@UAEHW4ObjectID@@@Z
Int GarrisonContain::getObjectGarrisonPointIndex(ObjectID objectID)
{
	if (objectID == INVALID_ID)
		return -1;

	Object *object = TheGameLogic->findObjectByID(objectID);
	if (object == 0)
		return -1;

	GarrisonPointData *point = m_garrisonPointData;
	for (Int i = 0; i < 40; ++i, ++point)
	{
		ObjectContainModuleInterface *contain = object->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *hordeContain =
				contain->getHordeContainInterface();
			if (hordeContain != 0)
			{
				char listStorage[16];
				::new (listStorage) ContainedItemsList(
					hordeContain->getContainList());

				for (ContainedItemsList::const_iterator it =
					reinterpret_cast<ContainedItemsList *>(listStorage)->begin();
					it != reinterpret_cast<ContainedItemsList *>(listStorage)->end();
					++it)
				{
					ObjectID containedID = (*it)->getID();
					for (Int j = 0; j < 40; ++j)
					{
						if (m_garrisonPointData[j].objectID == containedID)
						{
							destroyContainedItemsList(
								reinterpret_cast<ContainedItemsList *>(listStorage));
							return j;
						}
					}
				}
				destroyContainedItemsList(
					reinterpret_cast<ContainedItemsList *>(listStorage));
			}
		}
		else if (point->objectID == objectID)
		{
			return i;
		}
	}

	return -1;
}
