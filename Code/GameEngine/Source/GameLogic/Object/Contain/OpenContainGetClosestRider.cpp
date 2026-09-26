// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: OpenContain::getClosestRider, retail 0x00235520, 145 bytes.
// The retail body receives the complete module pointer, then dispatches the
// BFME contain-interface getter at slot 65 before scanning the rider list.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

typedef _STL::list<Object *> ContainedItemsList;

class BFMEOpenContainSlotShim
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
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
};

class OpenContain
{
public:
	virtual Object *getClosestRider(Object *referenceObject);
};

Object *OpenContain::getClosestRider(Object *referenceObject)
{
	Real closestDistanceSquared = 1000000.0f;
	Object *closestRider = 0;
	const BFMEOpenContainSlotShim *contain =
		(const BFMEOpenContainSlotShim *)((const char *)this + 0x20);
	const ContainedItemsList *riders = contain->getContainedItemsList();

	for (ContainedItemsList::const_iterator riderIt = riders->begin(); riderIt != riders->end(); ++riderIt)
	{
		Object *rider = *riderIt;
		if (rider != referenceObject)
		{
			Coord3D riderPos = *rider->getPosition();
			Real dx = riderPos.x - referenceObject->getPosition()->x;
			Real dy = riderPos.y - referenceObject->getPosition()->y;
			Real distanceSquared = dx * dx + dy * dy;
			if (distanceSquared < closestDistanceSquared)
			{
				closestRider = rider;
				closestDistanceSquared = distanceSquared;
			}
		}
	}

	return closestRider;
}
