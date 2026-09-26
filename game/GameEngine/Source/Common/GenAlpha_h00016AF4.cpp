// Open-BFME: GenAlpha::h00016AF4, retail 0x007B9980, 41 bytes.
//
// Snapshot the list at this+0, null the head, then walk via the successor at
// +0x68. Each node is unlinked before delete so the destructor cannot observe
// the rest of the chain. Slot 0 is the deleting destructor (push 1).

class GenAlphaNode
{
public:
	virtual ~GenAlphaNode();

	unsigned char m_unmodelled[0x64];
	GenAlphaNode *m_next;
};

class GenAlpha
{
public:
	void h00016AF4(void);

private:
	GenAlphaNode *m_head;
};

void GenAlpha::h00016AF4(void)
{
	GenAlphaNode *cur_shadow = 0;
	GenAlphaNode *next_shadow = m_head;
	m_head = 0;

	for (cur_shadow = next_shadow; cur_shadow; cur_shadow = next_shadow)
	{
		next_shadow = cur_shadow->m_next;
		cur_shadow->m_next = 0;
		delete cur_shadow;
	}
}
