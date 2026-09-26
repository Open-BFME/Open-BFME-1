// ?second@Gen_00943CF0@@AAEXPAX000@Z
// partial score=0.9 date=2026-09-08
// Clean reconstruction of the linked-node traversal at retail RVA 0x00943CF0.
// The owning type and the two helper identities are not recovered; their
// address-derived declarations preserve the call boundaries and observed
// pointer flow without inventing a semantic name.

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *listNode;
};

class Gen_00943CF0;

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();

protected:
	bool Internal_Add(MultiListObjectClass *object, bool onlyOnce);
	friend class Gen_00943CF0;

private:
	unsigned char head[20];
};

struct Gen_00943CF0_Cell
{
	unsigned count;
	GenericMultiListClass list;
};

class Gen_00943CF0_ObjectBase
{
	virtual ~Gen_00943CF0_ObjectBase();

	unsigned references;
};

class Gen_00943CF0_Value : public Gen_00943CF0_ObjectBase,
	public MultiListObjectClass
{
	public:
	unsigned char padding[0x84];

	unsigned packed;
};

class Gen_00943CF0
{
	void first(void *value, void **secondOutput, void **firstOutput,
		void **listAddress);
	void second(void *value, void *secondOutput, void *firstOutput,
		void *list);

public:
	void process(Gen_00943CF0_Node **list);

private:
	float originX;
	float originY;
	unsigned char padding[0x10];
	Gen_00943CF0_Cell *cells;
	unsigned width;
	float scale;
	unsigned heightMask;
};

void Gen_00943CF0::process(Gen_00943CF0_Node **list)
{
	Gen_00943CF0_Node *node = *list;
	while (node != 0) {
		void *value = node->m_value;
		void *firstOutput;
		void *secondOutput;
		first(value, &secondOutput, &firstOutput, (void **)&list);
		second(value, secondOutput, firstOutput, list);
		node = node->m_next;
	}
}

void Gen_00943CF0::second(void *value, void *secondOutput, void *firstOutput,
	void *list)
{
	unsigned width = this->width;
	unsigned heightMask = this->heightMask;
	unsigned address = (unsigned)list;
	Gen_00943CF0_Cell *cell;
	width >>= 2;
	heightMask >>= 1;
	cell = (Gen_00943CF0_Cell *)this->cells;
	while (width != 0) {
		if (((unsigned)address & heightMask) != 0)
			return;

		++cell->count;
		unsigned index = (heightMask & (unsigned)secondOutput) != 0;
		index += 2 * ((heightMask & (unsigned)firstOutput) != 0);
		cell += index * width + 1;
		width >>= 2;
		heightMask >>= 1;
	}

	Gen_00943CF0_Value *object = (Gen_00943CF0_Value *)value;
	cell->list.Internal_Add(
		object != 0 ? (MultiListObjectClass *)object : 0,
		false);
	object->packed = ((unsigned)secondOutput << 20) |
			((unsigned)firstOutput << 10) | (unsigned)address;
}
