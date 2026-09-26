// Clean reconstruction of the linked-node traversal at retail RVA 0x00943CF0.
// The owning type and the two helper identities are not recovered; their
// address-derived declarations preserve the call boundaries and observed
// pointer flow without inventing a semantic name.

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class Gen_00943CF0
{
	void first(void *value, int *secondOutput, int *firstOutput,
		int *listAddress);
	void second(void *value, void *secondOutput, void *firstOutput,
		void *list);
	void unlink(void *value);
	void link(void *value, int address, int secondOutput, int firstOutput);

public:
	void process(Gen_00943CF0_Node **list);
	void update(void *value);
};

void Gen_00943CF0::process(Gen_00943CF0_Node **list)
{
	Gen_00943CF0_Node *node = *list;
	while (node != 0) {
		void *value = node->m_value;
		void *firstOutput;
		void *secondOutput;
		first(value, (int *)&secondOutput, (int *)&firstOutput, (int *)&list);
		second(value, secondOutput, firstOutput, list);
		node = node->m_next;
	}
}

void Gen_00943CF0::update(void *value)
{
	register int firstOutput;
	register int secondOutput;
	void *saved = value;
	{
		int firstStorage;
		int secondStorage;
		first(saved, (int *)&value, &secondStorage, &firstStorage);
		firstOutput = firstStorage;
		secondOutput = secondStorage;
	}
	int address = *(int *)((char *)saved + 0x94);
	if (address >= 0) {
		int packed = (((int)value << 10) | secondOutput) << 10 | firstOutput;
		if (packed == address)
			return;
		unlink(saved);
	}
	link(saved, (int)value, secondOutput, firstOutput);
}
