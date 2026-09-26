// ?getObjectGarrisonPointIndex@GarrisonContain@@UAEHW4ObjectID@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Vtable 0x010AB818 slot 26 reaches RVA 0x0021F280 through thunk 0x0003C781.
// Constructor 0x0021D820 installs that vtable.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

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

	Object *queriedObject = TheGameLogic->findObjectByID(objectID);
	if (queriedObject == 0)
		return -1;

	Int pointIndex = 0;
	GarrisonPointData *garrisonPoint = m_garrisonPointData;
	for (; pointIndex < 40; ++pointIndex, ++garrisonPoint)
	{
		ObjectContainModuleInterface *contain = queriedObject->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *hordeContain =
				contain->getHordeContainInterface();
			if (hordeContain != 0)
			{
				ContainedItemsList hordeMembers(hordeContain->getContainList());

				for (ContainedItemsList::const_iterator memberIt = hordeMembers.begin();
					memberIt != hordeMembers.end();
					++memberIt)
				{
					Object *containedObject = *memberIt;
					ObjectID containedID = containedObject->getID();
					for (Int memberPointIndex = 0; memberPointIndex < 40; ++memberPointIndex)
					{
						if (m_garrisonPointData[memberPointIndex].objectID == containedID)
						{
							return memberPointIndex;
						}
					}
				}
			}
		}
		else if (garrisonPoint->objectID == objectID)
		{
			return pointIndex;
		}
	}

	return -1;
}
