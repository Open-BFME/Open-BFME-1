// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0021B310 (75 B). A container admission test: an object whose
// relationship to the owner is ENEMIES (0) is admitted while the contained
// list is below the data capacity at +0x17C; any other goes to the fallback.
//
// The owner is read through an inline accessor. The direct member read
// compiles to the same load but leaves the capacity reload after the list walk
// in ECX where retail has EAX: MSVC 7.1 hands out scratch registers
// round-robin, and the inlined accessor's return value is one more step
// (docs/shape_levers.md, "Scratch registers rotate").
#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
};

// The fallback is the matched 32-byte body 0x00248ED0 (BfmeConv1317.cpp),
// reached through ILT 0x00013CA5 with this container as its receiver.
class BfmeThingTLB
{
public:
	int bfmeGoTLB(int a);
};

struct Rva21B310Data
{
	char gap[0x17C];
	unsigned int capacity;
};

class Rva21B310RelationshipCapacity
{
public:
	int accepts(Object *object);
	int acceptRelated(Object *object)
	{
		return ((BfmeThingTLB *)this)->bfmeGoTLB((int)object);
	}

private:
	Object *getOwner() const { return owner; }

	unsigned long unknown;
	Rva21B310Data *data;
	Object *owner;
	char gap0C[0x9B0];
	_STL::list<Object *> objects;
};

int Rva21B310RelationshipCapacity::accepts(Object *object)
{
	if (object->getRelationship(getOwner()) == ENEMIES) {
		return objects.size() < data->capacity;
	}

	return acceptRelated(object);
}
