// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// ScriptActions::findClosestObject, retail 0x002F5D50, 385 bytes.
//
// This helper is shared by the BFME object-type-list nearest-object actions.
// The list is walked one entry at a time; each resolved ThingTemplate gets a
// Thing filter linked to the optional player filter, and the returned object
// is reduced by squared distance from the supplied position.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;
class Player;
class ThingTemplate;

class AsciiStringVector
{
public:
	AsciiString operator[](Int index) const;

	const AsciiString *m_begin;
	const AsciiString *m_end;
	const AsciiString *m_capacity;
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes() {}

	__forceinline AsciiString getNthInList(Int index) const
	{
		return m_objectTypes[index];
	}

	__forceinline Int getListSize(void) const
	{
		return (Int)(m_objectTypes.m_end - m_objectTypes.m_begin);
	}

private:
	AsciiString m_listName;
	AsciiStringVector m_objectTypes;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}

	void sub(const Coord3D *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real lengthSqr(void) const
	{
		return x * x + y * y + z * z;
	}
};

class Object
{
public:
	virtual void slot0(void);

	unsigned char m_unreconstructed[0x34];
	Coord3D m_position;

	const Coord3D *getPosition(void) const { return &m_position; }
};

class PartitionFilter
{
public:
    PartitionFilter(void) : m_next(0) {}
    virtual ~PartitionFilter(void) {}
    virtual Bool allow(Object *object) = 0;
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: m_thingTemplate(thingTemplate), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

extern BfmeThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;

class ScriptActions
{
protected:
	// ?findClosestObject@ScriptActions@@IAEPAVObject@@PBUCoord3D@@PAVObjectTypes@@PAVPlayer@@@Z
	Object *findClosestObject(const Coord3D *position,
		ObjectTypes *objectTypes, Player *player);
};

Object *ScriptActions::findClosestObject(const Coord3D *position,
	ObjectTypes *objectTypes, Player *player)
{
    Object *bestObject = 0;
    Real bestDistance = 3.402823466e+38F;
    const Int typeCount = objectTypes->getListSize();

	for (Int typeIndex = 0; typeIndex < typeCount; typeIndex++)
	{
		const ThingTemplate *thisType = TheThingFactory->findTemplate(
			objectTypes->getNthInList(typeIndex));
		if (thisType)
		{
            PartitionFilterThing thingFilter(thisType, true);
            PartitionFilterPlayer playerFilter(player, true);
            if (player)
            {
                thingFilter.link(&playerFilter);
            }

                Object *object = ThePartitionManager->getClosestObject(
                 position, 1000000.0f, 0, &thingFilter);
            if (object)
            {
                Coord3D delta = *position;
                delta.sub(object->getPosition());
                Real distance = delta.lengthSqr();

				if (distance < bestDistance)
				{
					bestDistance = distance;
					bestObject = object;
				}
			}
		}
	}

	return bestObject;
}
