struct Rva21ABF0Node
{
	Rva21ABF0Node *next;
	Rva21ABF0Node *previous;
	void *value;
};

class Rva21ABF0Worker
{
public:
	void visit(void *value);
};

class Rva21ABF0RingDispatch
{
public:
	void dispatchAll(void);
	void finish(void);

private:
	char m_gap[0x99C];
	Rva21ABF0Node *m_ring;
};

void Rva21ABF0RingDispatch::dispatchAll(void)
{
	Rva21ABF0Node *node = m_ring->next;

	while (node != m_ring) {
		void *value = node->value;
		node = node->next;
		((Rva21ABF0Worker *)((char *)this - 0x20))->visit(value);
	}

	finish();
}
