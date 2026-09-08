// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0021E1C0, 123 bytes.
//
// The boundary is the GarrisonContain helper which chooses a point for an
// object relative to either another object or an explicit position.  The
// neighboring matched calcBestGarrisonPosition body and the existing
// findConditionIndex/findClosestFreeGarrisonPointIndex/putObjectAtGarrisonPoint
// bindings establish this owner and call family.  BFME's vtable lookup shows
// getObjectGarrisonPointIndex at slot +0x68; the target passes ObjectID from
// Object +0x74, while an Object target's position is the Coord3D at +0x38.

typedef int Int;
typedef bool Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	ObjectID getID() const
	{
		return *(const ObjectID *)((const unsigned char *)this + 0x74);
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
};

class GarrisonContain
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual Int getObjectGarrisonPointIndex(ObjectID objectID) = 0;

protected:
	Int findConditionIndex();
	Int findClosestFreeGarrisonPointIndex(Int conditionIndex,
		const Coord3D *targetPos);
	void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID,
		Int conditionIndex, Int pointIndex);
	void putObjectAtBestGarrisonPoint(Object *obj, Object *target,
		const Coord3D *targetPos);
};

void GarrisonContain::putObjectAtBestGarrisonPoint(Object *obj,
	Object *target, const Coord3D *targetPos)
{
	if (obj == 0 || (target == 0 && targetPos == 0))
		return;

	if (target != 0)
		targetPos = target->getPosition();

	if (getObjectGarrisonPointIndex(obj->getID()) != -1)
		return;

	Int conditionIndex = findConditionIndex();
	Int pointIndex = findClosestFreeGarrisonPointIndex(conditionIndex,
		targetPos);
	if (pointIndex == -1)
		return;

	putObjectAtGarrisonPoint(obj,
		target != 0 ? target->getID() : INVALID_OBJECT_ID,
		conditionIndex, pointIndex);
}
