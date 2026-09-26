class Rva21D510Object
{
public:
	unsigned char gap[0x204];
	void *ai;
};

struct Rva21D510Node
{
	Rva21D510Node *next;
	Rva21D510Node *previous;
	Rva21D510Object *object;
};

class BfmeInnerRQ
{
public:
	void bfmeSetRQ(int object, int commandSource);
};

class Rva21D510OrderMembersIdle
{
public:
	void orderAll(int commandSource);

private:
	char m_gap0[0x99C];
	Rva21D510Node *m_objects;
};

void Rva21D510OrderMembersIdle::orderAll(int commandSource)
{
	Rva21D510Node *node = m_objects->next;

	while (node != m_objects) {
		Rva21D510Object *object = node->object;
		void *ai = object->ai;
		node = node->next;

		if (ai != 0) {
			BfmeInnerRQ *command = (BfmeInnerRQ *)((char *)ai + 0x20);
			Rva21D510Object *owner = *(Rva21D510Object **)((char *)this - 0x18);
			command->bfmeSetRQ((int)owner, commandSource);
		}
	}
}
