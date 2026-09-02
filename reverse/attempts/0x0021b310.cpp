// ?accepts@Rva21B310RelationshipCapacity@@QAEHPAVObject@@@Z
// partial score=0.99 date=2026-09-02
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
