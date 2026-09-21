// ?d_002f9c60@@YAXXZ
// partial score=0.33 date=2026-09-21
// ?rva002f9c60@ScriptActions@@IAEPAVObject@@PAX0ABVAsciiString@@1@Z [retail body 0x002F9C60]
// Address-derived: constructs PartitionFilterThing (vtable 0x010CFFD0, matching
// ScriptActions_findClosestObject.cpp) and calls the landed
// ScriptActions::findClosestObject / BfmeApplierBH::bfmeAddBH.  Two ScriptEngine
// vtable slots (+0x44, +0x50) are still unproven; kept as address-derived slots.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class ThingTemplate;
class ObjectTypes;

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) {}
	virtual ~PartitionFilter(void) {}
	virtual Bool allow(Object *object) = 0;
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

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern PartitionManager *ThePartitionManager;
extern BfmeThingFactory *TheThingFactory;

class Rva002F9C60ResultA
{
public:
	virtual void slot00();
	void bfmeEstimateXQ(Coord3D *out);
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual Rva002F9C60ResultA *rva002f9c60Slot17(void);
	virtual void slot18(); virtual void slot19();
	virtual ObjectTypes *rva002f9c60Slot20(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

class BfmeTargetBH;
class AsciiStringBH;

class ScriptActions
{
protected:
	Object *findClosestObject(const Coord3D *position,
		ObjectTypes *objectTypes, Player *player);

	void bfmeAddBH(void *owner, const AsciiStringBH &name, BfmeTargetBH *target);

	// ?d_002f9c60@@YAXXZ (address-derived; called from the
	// SKIRMISH_FIRE_SPECIAL_POWER_AT_MOST_COST arm's helper chain).
	// ret 0x10 proves 4 explicit stack dwords; the used ones are the LAST
	// two (name2 at [esp+0x40]==S0+0xC, name at [esp+0x3c]==S0+0x10), so
	// param1/param2 are declared but their retail role is still unproven.
	Object *rva002f9c60(void *param1, void *param2,
		const AsciiString &name2, const AsciiString &name);
};

Object *ScriptActions::rva002f9c60(void *param1, void *param2,
	const AsciiString &name2, const AsciiString &name)
{
	AsciiString nameCopy = name;
	Object *result = 0;

	Rva002F9C60ResultA *resultA = TheScriptEngine->rva002f9c60Slot17();
	Coord3D location;
	if (resultA)
		resultA->bfmeEstimateXQ(&location);

	ObjectTypes *objectTypes = TheScriptEngine->rva002f9c60Slot20(name2);
	if (objectTypes) {
		result = findClosestObject(&location, objectTypes, 0);
	} else {
		const ThingTemplate *thisType = TheThingFactory->findTemplate(nameCopy);
		if (thisType) {
			PartitionFilterThing filter(thisType, true);
			result = ThePartitionManager->getClosestObject(&location,
				1000000.0f, 0, &filter);
			if (result) {
				bfmeAddBH(param1, *(const AsciiStringBH *)&nameCopy,
					(BfmeTargetBH *)result);
			}
		}
	}

	return result;
}
