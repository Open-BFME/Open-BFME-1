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
	void first(void *value, void **secondOutput, void **firstOutput,
		void **listAddress);
	void second(void *value, void *secondOutput, void *firstOutput,
		void *list);

public:
	void process(Gen_00943CF0_Node **list);
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
