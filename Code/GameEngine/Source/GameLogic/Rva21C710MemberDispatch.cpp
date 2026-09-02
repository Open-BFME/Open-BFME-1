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

class Rva21C710MemberDispatch
{
public:
	void dispatch(Rva21C710Object *object, void *action);
	void dispatchNew(Rva21C710Object *object, void *action);
	void dispatchMember(Rva21C710Object *object, void *action);

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
			dispatchMember(object, 0);
			return;
		}
		node = node->next;
	}

	dispatchNew(object, action);
}
