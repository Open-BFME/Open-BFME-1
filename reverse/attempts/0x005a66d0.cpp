// ?releasePairA@Rva005A66D0EmbeddedNodeOwner@@QAEXXZ
// partial score=0.78 date=2026-09-02
// cl: /O2 /Ob0

struct Rva005A66D0Node
{
	char m_padding[0x10];
	volatile unsigned int m_value;
	volatile unsigned char m_flags;
};

void releaseRva005A66D0Node(Rva005A66D0Node *node);

class Rva005A66D0EmbeddedNodeOwner
{
public:
	void releasePairA();
	void releasePairB();

private:
	char m_padding0[0x68];
	Rva005A66D0Node m_firstA;
	char m_padding1[0x18];
	Rva005A66D0Node m_firstB;
	char m_padding2[0xA8];
	Rva005A66D0Node m_secondA;
	char m_padding3[0x18];
	Rva005A66D0Node m_secondB;
};

void Rva005A66D0EmbeddedNodeOwner::releasePairA()
{
	Rva005A66D0Node *first = &m_firstA;
	Rva005A66D0Node *second = &m_secondA;
	Rva005A66D0Node *selected;
	if (first && !(first->m_flags & 1))
	{
		if (second && !(second->m_flags & 1))
		{
			unsigned int secondValue = second->m_value;
			unsigned int firstValue = first->m_value;
			selected = firstValue <= secondValue ? second : first;
		}
		else
		{
			selected = first;
		}
	}
	else
	{
		selected = second && !(second->m_flags & 1) ? second : 0;
	}
	if (selected)
		releaseRva005A66D0Node(selected);
}

void Rva005A66D0EmbeddedNodeOwner::releasePairB()
{
	Rva005A66D0Node *first = &m_firstB;
	Rva005A66D0Node *second = &m_secondB;
	Rva005A66D0Node *selected;
	if (first && !(first->m_flags & 1))
	{
		if (second && !(second->m_flags & 1))
		{
			unsigned int secondValue = second->m_value;
			unsigned int firstValue = first->m_value;
			selected = firstValue <= secondValue ? second : first;
		}
		else
		{
			selected = first;
		}
	}
	else
	{
		selected = second && !(second->m_flags & 1) ? second : 0;
	}
	if (selected)
		releaseRva005A66D0Node(selected);
}
