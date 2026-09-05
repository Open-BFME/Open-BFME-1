// ?accepts@Rva21B310RelationshipCapacity@@QAEHPAVObject@@@Z
// partial score=0.99 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// 73 of 75 bytes match. The two that differ are at +0x2c and +0x2f: after the
// list-walk loop, retail reloads the data pointer into EAX and compares
// against [eax+0x17c], while this source gets ECX and [ecx+0x17c]. Both EAX
// (the loop cursor) and ECX (the list head) are dead when the loop exits, so
// the allocator is free either way and picks the other one here.
//
// Tried on 2026-09-05 against this file as the control, none moved the pair:
// a local for the capacity, the comparison reversed to capacity > count, the
// data member without volatile, a for loop, a do-while with a leading guard,
// a local for the data pointer, an explicit int cast on the result, node
// defined before end, count defined before both, and the list head read fresh
// in the loop condition. Reversing the loop condition to end != node costs two
// more bytes and moves the first difference to +0x22, so it is worse.

class Object
{
public:
	int getRelationship(const Object *other) const;
};

struct Rva21B310Data
{
	char gap[0x17C];
	unsigned int capacity;
};

struct Rva21B310Node
{
	Rva21B310Node *next;
};

class Rva21B310RelationshipCapacity
{
public:
	int accepts(Object *object);
	int acceptRelated(Object *object);

private:
	unsigned long unknown;
	Rva21B310Data * volatile data;
	Object *owner;
	char gap0C[0x9B0];
	Rva21B310Node *objects;
};

int Rva21B310RelationshipCapacity::accepts(Object *object)
{
	if (object->getRelationship(owner) == 0) {
		Rva21B310Node *end = objects;
		Rva21B310Node *node = end->next;
		unsigned int count = 0;

		while (node != end) {
			node = node->next;
			++count;
		}

		return count < data->capacity;
	}

	return acceptRelated(object);
}
