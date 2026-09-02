void *__cdecl bfmeAlloc1046(int bytes);

class Rva226790Template
{
public:
	Rva226790Template *getFinalOverride(void);

	unsigned long unknown;
	Rva226790Template *nextOverride;
	char gap[0xC4];
	unsigned char flags;
};

struct Rva226790Object
{
	unsigned long unknown;
	Rva226790Template *objectTemplate;
};

struct Rva226790Node
{
	Rva226790Node *next;
	Rva226790Node *previous;
	Rva226790Object *object;
};

class Rva226790InsertAndCount
{
public:
	void insert(Rva226790Object *object);

private:
	char gap0[0x18];
	Rva226790Node *sentinel;
	int count;
	char gap20[0x24];
	int flaggedCount;
};

void Rva226790InsertAndCount::insert(Rva226790Object *object)
{
	Rva226790Node *end = sentinel;
	Rva226790Node *node = (Rva226790Node *)bfmeAlloc1046(sizeof(Rva226790Node));
	Rva226790Object **slot = &node->object;

	if (slot != 0)
		*slot = object;

	Rva226790Node *previous = end->previous;
	node->next = end;
	node->previous = previous;
	previous->next = node;
	end->previous = node;
	++count;

	Rva226790Template *value = object->objectTemplate;
	if (value != 0 && value->nextOverride != 0)
		value = value->nextOverride->getFinalOverride();

	if ((value->flags & 2) != 0)
		++flaggedCount;
}
