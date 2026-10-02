class Rva21C710Object
{
public:
	char gap[0x90];
	unsigned char status;
};

struct Rva21C710Node
{
	Rva21C710Node *next;
	Rva21C710Node *previous;
	Rva21C710Object *object;
};

class Rva21C710Owner
{
public:
	void prepare(Rva21C710Object *object);
};

class Object;
class BfmeRva49250Object;

// Retail ILT 0x0002CE44 reaches the matched member dispatcher at 0x00227B60.
class Rva00227B60ContainDispatch
{
public:
	void dispatch(Object *object, bool flag);
};

// Retail ILT 0x00012E0E reaches the matched nonmember body at 0x00249250.
class BfmeRva49250Base
{
public:
	void bfmeApplyObject(BfmeRva49250Object *object, void *action);
};

class Rva21C710MemberDispatch
{
public:
	void dispatch(Rva21C710Object *object, void *action);

private:
	char gap[0x99C];
	Rva21C710Node *members;
};

void Rva21C710MemberDispatch::dispatch(Rva21C710Object *object, void *action)
{
	if ((object->status & 0x40) != 0)
		((Rva21C710Owner *)((char *)this - 0x20))->prepare(object);

	Rva21C710Node *end = members;
	Rva21C710Node *node = end->next;

	while (node != end) {
		if (node->object == object) {
			((Rva00227B60ContainDispatch *)this)->dispatch((Object *)object, false);
			return;
		}
		node = node->next;
	}

	((BfmeRva49250Base *)this)->bfmeApplyObject(
		(BfmeRva49250Object *)object, action);
}
