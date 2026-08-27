// The same push at the head of a list, with a plain value in the node instead
// of a counted reference.

extern void * (*WideAllocPtr)(unsigned int bytes);

class BfmeNodeBD
{
public:
	void *operator new(unsigned int bytes)
	{
		return WideAllocPtr(bytes);
	}

	BfmeNodeBD(int value)
	{
		m_bfmeValue = value;

		m_bfmeNext = 0;
	}

	int m_bfmeValue;					// +0x00
	BfmeNodeBD *m_bfmeNext;					// +0x04
};

class Gen_00894FB0
{
public:
	void bfmePush(int *value);

private:
	BfmeNodeBD *m_bfmeHead;					// +0x00
};

// ?bfmePush@Gen_00894FB0@@QAEXPAH@Z
void Gen_00894FB0::bfmePush(int *value)
{
	BfmeNodeBD *node = new BfmeNodeBD(*value);

	node->m_bfmeNext = m_bfmeHead;

	m_bfmeHead = node;
}
