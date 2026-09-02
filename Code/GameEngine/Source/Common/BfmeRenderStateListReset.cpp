// cl: /O2 /Ob0

// Open-BFME5: reset the state words in the two render-record collections.

struct BfmeReferencedRenderRecord
{
	char m_unused[0x555C];
	int m_firstState;
	int m_secondState;
};

struct BfmeInlineRenderRecord
{
	int m_firstState;
	int m_secondState;
	char m_unused[0x20];
};

class BfmeRenderStateLists
{
public:
	int resetRenderStates(int);

private:
	char m_unused0000[0x9C];
	int m_referencedCount;
	int m_unused00A0;
	BfmeReferencedRenderRecord *m_referenced[0x2006];
	int m_inlineCount;
	char m_unused80C0[0x18];
	BfmeInlineRenderRecord m_inline[1];
};

int BfmeRenderStateLists::resetRenderStates(int)
{
	int i = 0;
	for (; i < m_referencedCount; ++i)
	{
		if (m_referenced[i])
		{
			m_referenced[i]->m_firstState = 2;
			m_referenced[i]->m_secondState = 2;
		}
	}

	int j = 0;
	for (; j < m_inlineCount; ++j)
	{
		m_inline[j].m_firstState = 2;
		m_inline[j].m_secondState = 2;
	}

	return 0x800;
}
