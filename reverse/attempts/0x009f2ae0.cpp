// ?bfmeAppendFE@BfmeChainFE@@QAEXPAV1@@Z (identity unknown)
// partial score=0.85 date=2026-09-06
// 36/46; retail spends a 6-byte loop-align nop, a push/pop esi and mov eax,ecx.
class BfmeChainFE
{
public:
	void bfmeAppendFE(BfmeChainFE *node);

	unsigned char m_bfmeHeadFE[4];
	BfmeChainFE *m_bfmeNextFE;
};

void BfmeChainFE::bfmeAppendFE(BfmeChainFE *node)
{
	BfmeChainFE *next = m_bfmeNextFE;
	if (next != 0)
	{
		BfmeChainFE *cur;
		do
		{
			cur = next;
			next = cur->m_bfmeNextFE;
		}
		while (next != 0);

		cur->m_bfmeNextFE = node;
		return;
	}

	m_bfmeNextFE = node;
}
