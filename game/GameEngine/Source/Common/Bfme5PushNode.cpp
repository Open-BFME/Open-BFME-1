// A push at the head of a list whose nodes come from an allocator that can
// fail.
//
// Everything after the constructor is duplicated into the failure path with
// the null propagated into it -- the store through the node and the store of
// the head both appear twice -- because only the construction is guarded, and
// that guard is the one the new expression itself emits.

extern void * (*Rva008C5D70Alloc)(unsigned int bytes);

class BfmeRefBC
{
public:
	int m_refCount;						// +0x00
};

class BfmeNodeBC
{
public:
	void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	BfmeNodeBC(BfmeRefBC *value)
	{
		m_bfmeValue = value;

		if (value)
			++value->m_refCount;

		m_next = 0;
	}

	BfmeRefBC *m_bfmeValue;					// +0x00
	BfmeNodeBC *m_next;					// +0x04
};

class Gen_00896500
{
public:
	void bfmePush(BfmeRefBC **value);

private:
	BfmeNodeBC *m_head;					// +0x00
};

// ?bfmePush@Gen_00896500@@QAEXPAPAVBfmeRefBC@@@Z
void Gen_00896500::bfmePush(BfmeRefBC **value)
{
	BfmeNodeBC *node = new BfmeNodeBC(*value);

	node->m_next = m_head;

	m_head = node;
}
