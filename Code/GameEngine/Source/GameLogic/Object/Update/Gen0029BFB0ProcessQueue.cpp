// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029BFB0: set this+0xB5, then while this+8 is non-null switch on
// node type: 1 and 3 call virtual +0x20 with +0x10, 2 calls virtual +0x10
// with +0xC, anything else drops the flag and returns.

struct Gen0029BFB0Node
{
	void *m_unused0;
	int m_type;
	void *m_unused08;
	void *m_payload0C;
	void *m_payload10;
};

class Gen0029BFB0
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(void *payload);
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20(void *payload);

	void process();

private:
	void *m_unused4;
	Gen0029BFB0Node *volatile m_head;
	unsigned char m_pad0C[0xa9];
	unsigned char m_busy;
};

// ?process@Gen0029BFB0@@QAEXXZ
void Gen0029BFB0::process()
{
	Gen0029BFB0Node *node = m_head;
	m_busy = 1;
	if (node)
	{
		for (;;)
		{
			node = m_head;
			switch (node->m_type)
			{
			case 1:
			case 3:
				slot20(node->m_payload10);
				break;
			case 2:
				slot10(node->m_payload0C);
				break;
			default:
				m_busy = 0;
				return;
			}
			if (!m_head)
				break;
		}
	}
	m_busy = 0;
}
